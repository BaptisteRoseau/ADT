#include "set.h"
#include "../common/utils.h"

#define BASIC_SET_SIZE 8 //must be a power of two

////////////////////////////////////////////////////////////////////
///     SET STRUCTURE
////////////////////////////////////////////////////////////////////

struct set
{
    void **array;
    unsigned int capacity;
    unsigned int size;
    void* (*operator_copy) (void* x);
    int (*operator_cmp) (void* x, void* y);
    void (*operator_delete) (void*);
    void (*operator_debug) (void*);
};

////////////////////////////////////////////////////////////////////
///     SET FUNCTIONS UTILITARIES
////////////////////////////////////////////////////////////////////


/**
 * Search an element recursively with dichotomous technique
 * @param set the set
 * @param begin the first index
 * @param end the last index
 * @param searched_e the searched element (criteria given in compare function pointer)
 * @return the index of the found value or end pointer
 */
unsigned int set_find(struct set const *set, unsigned int begin, unsigned int end, void* searched_e)
{
    if (searched_e == NULL)
        return end;

    if (begin >= end)
        return end;

    unsigned int middle_e = (begin + end)/2;

    int cmp_res = set->operator_cmp(searched_e, set->array[middle_e]);

    if (cmp_res == 0)
        return middle_e;
    if (cmp_res == 1)
        return set_find(set, middle_e + 1, end, searched_e);
    else
        return set_find(set, begin, middle_e, searched_e);
}

void set_shift_right(struct set const *set, unsigned int begin, unsigned int end)
{
    if ((end >= set->capacity - 1) || (end > set->size))
        return;
    //Shift from [begin, end] to [begin + 1, end + 1] by a right to left path
    unsigned int k = end + 1;
    while (k > begin) {
        set->array[k]=set->array[k-1];
        k--;
    }
}

void set_shift_left(struct set const *set, unsigned int begin, unsigned int end)
{
    if ((begin == 0) || (end != set->size - 1))
        return;

    //Shift from [begin, end] to [begin - 1, end - 1] by a left to right path
    unsigned int k = begin - 1;
    while (k < end) {
        set->array[k]=set->array[k+1];
        k++;
    }
}

// Returns a copy of the element only if the copy in enabled
void* set_read_write(struct set const *s, void* element)
{
    if (s->operator_copy != NULL){
        return s->operator_copy(element);
    }
    return element;
}

// Delete the element only if the copy in enabled
void set_delete(struct set const *s, void* element)
{
    if (s->operator_delete != NULL){
        return s->operator_delete(element);
    }
}

////////////////////////////////////////////////////////////////////
///     SET FUNCTIONS IMPLEMENTATION
////////////////////////////////////////////////////////////////////

struct set *set__empty_copy_enabled(void *copy_op, void *delete_op, void *compare_op, void *debug_op)
{
    struct set *set = safe_malloc(sizeof(struct set));
    set->capacity = BASIC_SET_SIZE;
    set->array = safe_malloc(sizeof(void*)*set->capacity);
    set->size = 0;
    set->operator_copy = copy_op;
    set->operator_delete = delete_op;
    set->operator_cmp = compare_op;
    set->operator_debug = debug_op;

    return set;
}

struct set *set__empty_copy_disabled(void *compare_op, void *debug_op)
{
    struct set *set = safe_malloc(sizeof(struct set));
    set->capacity = BASIC_SET_SIZE;
    set->array = safe_malloc(sizeof(void*)*set->capacity);
    set->size = 0;
    set->operator_copy = NULL;
    set->operator_delete = NULL;
    set->operator_cmp = compare_op;
    set->operator_debug = debug_op;

    return set;
}

int set__is_copy_enabled(struct set const *s)
{
    assert_not_null(s, __func__, "s parameter");
    
    return ((s->operator_copy != NULL) && (s->operator_delete != NULL));
}

int set__is_empty(struct set const *s)
{
    assert_not_null(s, __func__, "s parameter");

    return (s->size == 0);
}

int set__add(struct set *s, void* x)
{
    assert_not_null(s, __func__, "s parameter");
    assert_not_null(s->array, __func__, "s array");

    if  (x == NULL)
        return !SUCCESS;

    unsigned int pos = set_find(s, 0, s->size, x);
    if  ((pos < s->size) && (s->operator_cmp(s->array[pos], x) == 0))
        return !SUCCESS;

    //Increase memory if needed
    if (s->size == s->capacity - 1) {
        s->capacity = s->capacity * 2;
        s->array = realloc(s->array, sizeof(void *) * s->capacity);
        if (s->array == NULL)
            return !SUCCESS;
    }

    //Add x into the s
    set_shift_right(s, pos, s->size);
    s->array[pos] = set_read_write(s, x);
    s->size++;

    return SUCCESS;
}

int set__remove(struct set *s, void* x)
{
    assert_not_null(s, __func__, "s parameter");
    assert_not_null(s->array, __func__, "s array");

    if  (x == NULL)
        return !SUCCESS;

    unsigned int pos = set_find(s, 0, s->size, x);
    if  ((s->size == 0)
            || (pos >= s->size)
            || ((pos < s->size) && (s->operator_cmp(s->array[pos], x) != 0)))
        return !SUCCESS;

    //Remove the element
    set_delete(s, s->array[pos]);
    set_shift_left(s, pos + 1, s->size - 1);
    s->size--;

    //Remove some allocated memory if needed
    if (s->size < s->capacity / 4) {
        s->capacity = s->capacity / 4;
        s->array = realloc(s->array, sizeof(void*)*s->capacity);
        if (s->array == NULL)
            return !SUCCESS;
    }

    return SUCCESS;
}

void* set__retrieve(struct set *s, void* x)
{
    assert_not_null(s, __func__, "s parameter");
    assert_not_null(s->array, __func__, "s array");

    if  (x == NULL || s->size == 0)
        return NULL;

    unsigned int pos = set_find(s, 0, s->size, x);
    if (pos >= s->size || (pos < s->size && s->operator_cmp(s->array[pos], x) != 0))
        return NULL;

    return s->array[pos];
}

int set__is_in(struct set const *s, void* x)
{
    assert_not_null(s, __func__, "s parameter");
    assert_not_null(s->array, __func__, "s array");

    unsigned int pos = set_find(s, 0, s->size, x);
    return pos < s->size && s->operator_cmp(s->array[pos], x) == 0;
}

unsigned int set__length(struct set const * s)
{
    assert_not_null(s, __func__, "s parameter");
    assert_not_null(s->array, __func__, "s array");

    return s->size;
}

void* set__get_umpteenth(struct set const *s, unsigned int i)
{
    assert_not_null(s, __func__, "s parameter");
    assert_not_null(s->array, __func__, "s array");
    if (i >= set__length(s))
        return NULL;
    return set_read_write(s, s->array[i]);
}

struct set *set__fusion(struct set const *set1, struct set const *set2)
{
    assert_not_null(set1, __func__, "set1 parameter");
    assert_not_null(set1->array, __func__, "set1 array");
    assert_not_null(set2, __func__, "set2 parameter");
    assert_not_null(set2->array, __func__, "set2 array");

    if (((void*) set1->operator_copy   != (void*) set2->operator_copy)
            || ((void*)  set1->operator_cmp    != (void*) set2->operator_cmp)
            || ((void*)  set1->operator_delete != (void*) set2->operator_delete)
            || ((void*)  set1->operator_debug  != (void*) set2->operator_debug)){
        printf("Set's operator functions unmatching in set__fusion.\n");
        return NULL;
    }

    struct set *merged_set;
    if (set__is_copy_enabled(set1) && set__is_copy_enabled(set2))
        merged_set = set__empty_copy_enabled(set1->operator_copy, set1->operator_delete, set1->operator_cmp, set1->operator_debug);
    else
        merged_set = set__empty_copy_disabled(set1->operator_cmp, set1->operator_debug);

    unsigned int i = 0;
    unsigned int size = set__length(set1);
    while (i < size){
        set__add(merged_set, set1->array[i]);
        i++;
    }

    i = 0;
    size = set__length(set2);
    while (i < size){
        set__add(merged_set, set2->array[i]);
        i++;
    }

    return merged_set;
}

void set__free(struct set *s)
{
    if (s == NULL)
        return;

    for (unsigned int i = 0; i < s->size; i++)
        set_delete(s, s->array[i]);
    free(s->array);
    free(s);
}

void set__debug(const struct set *s, int is_compact)
{
    setvbuf (stdout, NULL, _IONBF, 0);
    if (s == NULL || s->array == NULL)
        printf("Set (NULL)\n");
    else {
        if (!is_compact) {
            printf("Set (capacity: %u, size: %u, content: {\n", s->capacity, s->size);
            unsigned int i = 0;
            while (i < s->size) {
                s->operator_debug(s->array[i]);
                i++;
            }
            printf("})\n");
        } else {
            printf("{ ");
            unsigned int i = 0;
            while (i < s->size) {
                s->operator_debug(s->array[i]);
                i++;
            }
            printf("} ");
        }
    }
}

void set__change_debug_function(struct set *s, void* debug_op)
{
    if (debug_op == NULL)
        return;
    s->operator_debug = debug_op;
}

void set__map(struct set *s, applying_func_t f)
{
    if (s == NULL) return;

    for (unsigned int i = 0; i < s->size; i++)
        if (s->array[i] != NULL)
            f(s->array[i]);
}
