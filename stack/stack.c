#include "stack.h"
#include "../common/utils.h"

#define DEFAULT_STACK_CAPACITY 2


int my_random(int min, int max){ //min included, max excluded
  return min + (rand() % (max -  min));
}

////////////////////////////////////////////////////////////////////
///     STACK STRUCTURE
////////////////////////////////////////////////////////////////////

struct stack
{
    void* *array;
    size_t capacity;
    size_t head;
    void* (*operator_copy) (void*);
    void (*operator_delete) (void*);
    void (*operator_debug) (void*);
};

////////////////////////////////////////////////////////////////////
///     STACK FUNCTIONS UTILITARIES
////////////////////////////////////////////////////////////////////


// Returns a copy of the element only if the copy in enabled
void* stack_read_write(struct stack const *s, void* element)
{
    if (s->operator_copy != NULL){
        return s->operator_copy(element);
    }
    return element;
}

// Delete the element only if the copy in enabled
void stack_delete(struct stack const *s, void* element)
{
    if (s->operator_delete != NULL){
        return s->operator_delete(element);
    }
}

// Searches a pointer into the stack's array on [0,b[
int stack_find(struct stack const *s, void* element, unsigned int b)
{
    if (b > s->head)
        return false;
    
    for (unsigned int i = 0; i < b; i++){
        if (element == s->array[i])
            return true;
    }
    return false;
}

void stack_shift_left(struct stack const *s, size_t begin, size_t end)
{
    if ((begin == 0) || (end != s->head - 1))
        return;

    //Shift from [begin, end] to [begin - 1, end - 1] by a left to right path
    size_t k = begin - 1;
    while (k < end) {
        s->array[k]=s->array[k+1];
        k++;
    }
}

////////////////////////////////////////////////////////////////////
///     STACK FUNCTIONS IMPLEMENTATION
////////////////////////////////////////////////////////////////////

struct stack *stack__empty_copy_enabled(void* copy_op, void* delete_op, void* debug_op)
{
    struct stack *s = safe_malloc(sizeof(struct stack));

    s->capacity = DEFAULT_STACK_CAPACITY;
    s->head = 0;
    s->array = safe_malloc(sizeof(void*) * (s->capacity));
    s->operator_copy = copy_op;
    s->operator_delete = delete_op;
    s->operator_debug = debug_op;

    return s;
}

struct stack *stack__empty_copy_disabled(void* debug_op)
{
    struct stack *s = safe_malloc(sizeof(struct stack));

    s->capacity = DEFAULT_STACK_CAPACITY;
    s->head = 0;
    s->array = safe_malloc(sizeof(void*) * (s->capacity));
    s->operator_copy = NULL;
    s->operator_delete = NULL;
    s->operator_debug = debug_op;

    return s;
}

int stack__is_copy_enabled(struct stack const *s)
{
    return ((s->operator_copy != NULL) && (s->operator_delete != NULL));
}

int stack__is_empty(struct stack const *s)
{
    assert_not_null(s, __func__, "stack parameter");
    return (s->head == 0);
}

int stack__push(struct stack *s, void* element)
{
    assert_not_null(s, __func__, "stack parameter");
    assert_not_null(s->array, __func__, "stack array");

    if (element == NULL)
        return !SUCCESS;

    /* Adjust capacity if necessary */
    if (s->head == s->capacity){
        s->capacity = s->capacity * 2;
        s->array = realloc(s->array, sizeof(void*) * s->capacity);
        if (s->array == NULL)
            return !SUCCESS;
    }

    s->array[s->head] = stack_read_write(s, element);
    s->head++;

    return SUCCESS;
}

void* stack__peek(struct stack const *s)
{
    assert_not_null(s, __func__, "stack parameter");
    assert_not_null(s->array, __func__, "stack array");

    if (stack__is_empty(s))
        return NULL;

    return stack_read_write(s, s->array[s->head-1]);
}

void* stack__pop(struct stack *s)
{
    assert_not_null(s, __func__, "stack parameter");
    assert_not_null(s->array, __func__, "stack array");

    if (stack__is_empty(s))
        return NULL;

    // Adjust capacity if necessary
    if ((s->head <= s->capacity / 4) && (s->capacity > DEFAULT_STACK_CAPACITY)) {
        s->capacity = s->capacity / 2;
        s->array = realloc(s->array, sizeof(void*) * s->capacity);
        if (s->array == NULL)
            return NULL;
    }

    s->head--;
    void* returned = stack_read_write(s, s->array[s->head]);
    stack_delete(s, s->array[s->head]);
    s->array[s->head] = NULL;
    return returned;
}

size_t stack__length(struct stack const *s)
{
    assert_not_null(s, __func__, "stack parameter");
    return s->head;
}

void stack__mix(struct stack *s)
{
    assert_not_null(s, __func__, "stack parameter");
    assert_not_null(s->array, __func__, "stack array");

    size_t a;
    size_t b;
    void* tmp;  
    for (size_t i = 0; i < s->head; i++){
        a = (size_t) my_random(0, (int) s->head);
        b = (size_t) my_random(0, (int) s->head);
        tmp = s->array[a];
        s->array[a] = s->array[b];
        s->array[b] = tmp;
    }
}

void stack__free(struct stack *s)
{
    if (s == NULL || s->array == NULL)
        return;

    for (size_t i = 0; i < s->head; i++){
        if (s->array[i] != NULL)
            stack_delete(s, s->array[i]);
    }
    free(s->array);
    free(s);
}

void stack__debug(struct stack const *s, int is_compact)
{
    setvbuf (stdout, NULL, _IONBF, 0);
    if (s == NULL || s->array == NULL)
        printf("Queue (NULL)\n");
    else {
        if (!is_compact)
            printf("Stack (capacity: %zu, size: %zu, content: \n\t", s->capacity, stack__length(s));
        printf("{ ");
        for (size_t i = 0; i < s->head; i++)
            s->operator_debug(s->array[i]);
        printf("} ");
        if (!is_compact)
            printf("\n)\n");
    }
}

void stack__change_debug_function(struct stack *s, void* debug_op)
{
    if (debug_op == NULL)
        return;
    s->operator_debug = debug_op;
}

void stack__map(struct stack *s, applying_func_t f)
{
    if (s == NULL) return;

    if (stack__is_copy_enabled(s)) {
        for (size_t i = 0; i < s->head; i++){
            if (s->array[i] != NULL)
                f(s->array[i]);
        }
    }

    /* If the same element is more than 1 time in the stack,
    this is necessary in order to prevent multiple application of f on this element.
    */
    else{
        for (size_t i = 0; i < s->head; i++){
            if ((s->array[i] != NULL) && (!stack_find(s, s->array[i], i)))
                f(s->array[i]);
        }
    }
}

int stack__clean_NULL(struct stack *s) //Not tested
{
    int modification = true;
    while (modification == true) {
        modification = false;
        for (unsigned int i = 0; i < s->head; i++){
            if (s->array[i] == NULL){
                stack_shift_left(s, i + 1, s->head);
                s->head--;
                i--;
                modification = true;
            }
        }
    }

    return SUCCESS;
}