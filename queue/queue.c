#include "queue.h"
#include "../common/utils.h"

#define DEFAULT_QUEUE_CAPACITY 2 //Must be a power of 2

////////////////////////////////////////////////////////////////////
///     QUEUE STRUCTURE
////////////////////////////////////////////////////////////////////

struct queue
{
    void **array;
    unsigned int capacity;
    unsigned int front;
    unsigned int back;
    void* (*operator_copy) (void*);
    void (*operator_delete)(void *);
    void (*operator_debug)(void *);
};

////////////////////////////////////////////////////////////////////
///     QUEUE FUNCTIONS UTILITARIES
////////////////////////////////////////////////////////////////////


// Returns a copy of the element only if the copy in enabled
void* queue_read_write(struct queue const *q, void* element)
{
    if (q->operator_copy != NULL){
        return q->operator_copy(element);
    }
    return element;
}

// Delete the element only if the copy in enabled
void queue_delete(struct queue const *q, void* element)
{
    if (q->operator_delete != NULL){
        return q->operator_delete(element);
    }
}

// Searches a pointer into the queue's array on [0,b[ 
int queue_find(struct queue const *q, void* element, unsigned int b)
{
    // if b is a wrong index
    if (((q->back < q->front) && ((b < q->back) || (b > q->front)))
      || ((q->back > q->front) && ((b < q->back) && (b > q->front))))
        return false;
    
    for (unsigned int i = q->front; i != b; i = (i+1) % q->capacity){
        if (element == q->array[i])
            return true;
    }
    return false;
}


////////////////////////////////////////////////////////////////////
///     QUEUE FUNCTIONS IMPLEMENTATION
////////////////////////////////////////////////////////////////////

struct queue *queue__empty_copy_enabled(void* copy_op, void* delete_op, void* debug_op)
{
    struct queue *q = safe_malloc(sizeof(struct queue));

    q->array = safe_malloc(sizeof(void *) * DEFAULT_QUEUE_CAPACITY);
    for (unsigned int i = 0; i < DEFAULT_QUEUE_CAPACITY; i++)
        q->array[i] = NULL;

    q->capacity = DEFAULT_QUEUE_CAPACITY;
    q->front = 0;
    q->back = 0;
    q->operator_copy = copy_op;
    q->operator_delete = delete_op;
    q->operator_debug = debug_op;

    return q;
}

struct queue *queue__empty_copy_disabled(void* debug_op)
{
    struct queue *q = safe_malloc(sizeof(struct queue));

    q->array = safe_malloc(sizeof(void *) * DEFAULT_QUEUE_CAPACITY);
    for (unsigned int i = 0; i < DEFAULT_QUEUE_CAPACITY; i++)
        q->array[i] = NULL;

    q->capacity = DEFAULT_QUEUE_CAPACITY;
    q->front = 0;
    q->back = 0;
    q->operator_copy = NULL;
    q->operator_delete = NULL;
    q->operator_debug = debug_op;

    return q;
}

int queue__is_copy_enabled(struct queue const *q){
    return ((q->operator_copy != NULL) && (q->operator_delete != NULL));
}

int queue__is_empty(struct queue *q)
{
    assert_not_null(q, __func__, "queue parameter");

    return queue__length(q) == 0;
}

int queue__enqueue(struct queue *q, void* element)
{
    assert_not_null(q, __func__, "queue parameter");

    if (element == NULL)
        return !SUCCESS;

    // Adjust capacity if necessary
    if (queue__length(q) == q->capacity) {
        unsigned int prev_capacity = q->capacity;
        q->capacity *= 2;
        q->array = realloc(q->array, sizeof(void *) * q->capacity);
        if (q->array == NULL)
            return !SUCCESS;
        else
            for (unsigned int i = prev_capacity; i < q->capacity; i++)
                q->array[i] = NULL;

        q->back = prev_capacity;
        for (unsigned int i = 0; i < q->front; i++) {
            q->array[q->back] = q->array[i];
            q->array[0] = NULL;
            q->back++;
        }
    }

    q->array[q->back] = queue_read_write(q, element);
    q->back = (q->back + 1) % q->capacity;

    return SUCCESS;
}

int queue__dequeue(struct queue *q)
{
    assert_not_null(q, __func__, "queue parameter");

    if (queue__is_empty(q))
        return !SUCCESS;

    queue_delete(q, q->array[q->front]);
    q->array[q->front] = NULL;
    q->front = (q->front + 1) %q->capacity;

    //note: in order to avoid overwriting datas, a new array must be created
    if (queue__length(q) < q->capacity / 2 && q->capacity >  DEFAULT_QUEUE_CAPACITY) {
        unsigned int new_pos = 0;
        void **new_array = safe_malloc(sizeof(void *) * q->capacity / 2);
        for (unsigned int i = q->front; i != q->back; i = (i+1) % q->capacity) {
            new_array[new_pos] = q->array[i];
            new_pos++;
        }
        q->front = 0;
        q->back = new_pos % q->capacity;
        
        for (unsigned int i = new_pos; i < q->capacity / 2; i++)
            new_array[i] = NULL;

        free(q->array);
        q->array = new_array;
        q->capacity /= 2;
    }

    return SUCCESS;
}

void* queue__front(struct queue *q)
{
    assert_not_null(q, __func__, "queue parameter");

    if (queue__is_empty(q))
        return NULL;

    if (q->array[q->front] == NULL)
        return NULL;

    return queue_read_write(q, q->array[q->front]);
}

void* queue__back(struct queue *q)
{
    assert_not_null(q, __func__, "queue parameter");

    if (queue__is_empty(q))
        return NULL;

    if (q->back == 0)
        return queue_read_write(q, q->array[q->capacity - 1]);
    else
        return queue_read_write(q, q->array[q->back-1]);
}

unsigned int queue__length(struct queue *q)
{
    assert_not_null(q, __func__, "queue parameter");

    if (q->back > q->front || q->array[q->front] == NULL)
        return q->back - q->front;
    else
        return q->back + q->capacity - q->front;
}

void queue__free(struct queue *q)
{
    if (q == NULL)
        return;

    for (unsigned int i = 0; i < q->capacity; i++)
        if (q->array[i] != NULL)
            queue_delete(q, q->array[i]);

    free(q->array);
    free(q);
}

void queue__debug(struct queue *q, int is_compact)
{
    setvbuf (stdout, NULL, _IONBF, 0);
    if (q == NULL || q->array == NULL)
        printf("Queue (NULL)\n");
    else {
        if (!is_compact) {
            printf("Queue (capacity: %u, size: %u, content: \n", q->capacity, queue__length(q));
            printf("\t in queue order: { \n");
            for (unsigned int i = q->front; i != q->back; i = (i+1) % q->capacity) {
                q->operator_debug(q->array[i]);
            }
            printf("}\n\t in array order: { \n");
            for (unsigned int i = 0; i < q->capacity; i++) {
                q->operator_debug(q->array[i]);
            }
            printf("}\n)\n");
        } else {
            printf("{ ");
            for (unsigned int i = q->front; i != q->back; i = (i+1) % q->capacity) {
                q->operator_debug(q->array[i]);
            }
            printf("}");
        }
    }
}

void queue__map1(struct queue *q, applying_func_t f)
{
    if (q == NULL) return;

    for (unsigned int i = q->front; i != q->back; i = (i+1) % q->capacity) {
        if (q->array[i] != NULL)
            f(q->array[i]);
    }
}

void queue__map(struct queue *q, applying_func_t f)
{
    if (q == NULL) return;

    if (queue__is_copy_enabled(q)) {
        for (unsigned int i = q->front; i != q->back; i = (i+1) % q->capacity){
            if (q->array[i] != NULL)
                f(q->array[i]);
        }
    }

    /* If the same element is more than 1 time in the queue,
    this is necessary in order to prevent multiple application of f on this element.
    */
    else{
        for (unsigned int i = q->front; i != q->back; i = (i+1) % q->capacity){
            if ((q->array[i] != NULL) && (!queue_find(q, q->array[i], i)))
                f(q->array[i]);
        }
    }
}