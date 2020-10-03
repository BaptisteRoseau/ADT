#include "dequeue.h"
#include "../common/utils.h"

#define LLE_ARRAY_LENGTH 50 //Must be a multiple of 2
#define LLE_ARRAY_MIDDLE (LLE_ARRAY_LENGTH/2)

/*note: The program will run faster if you increase LLE_ARRAY_LENGTH
But, it will cost more RAM space. You have to choose you own LLE_ARRAY_LENGTH
regarding you needs (time save or RAM space save). */

////////////////////////////////////////////////////////////////////
///     DEQUEUE STRUCTURE
////////////////////////////////////////////////////////////////////

struct llelement_dequeue{
    void **lle_array;
    struct llelement_dequeue *previous;
    struct llelement_dequeue *next;
    int lle_back_length;
    int lle_front_length;
};

struct dequeue
{
    struct llelement_dequeue *back_llelement;
    struct llelement_dequeue *front_llelement;
    unsigned int length;
    void* (*operator_copy) (void*);
    void (*operator_delete)(void *);
    void (*operator_debug)(void *);
};

////////////////////////////////////////////////////////////////////
///     DEQUEUE FUNCTIONS UTILITARIES
////////////////////////////////////////////////////////////////////


// Returns a copy of the element only if the copy in enabled
void* dequeue_read_write(struct dequeue const *d, void* element)
{
    if (d->operator_copy != NULL){
        return d->operator_copy(element);
    }
    return element;
}

// Delete the element only if the copy in enabled
void dequeue_delete(struct dequeue const *d, void* element)
{
    if (d->operator_delete != NULL){
        return d->operator_delete(element);
    }
}


////////////////////////////////////////////////////////////////////
///     LLELEMENT FUNCTIONS UTILITARIES
////////////////////////////////////////////////////////////////////

struct llelement_dequeue *llelement_deq__empty() //O(1)
{
    struct llelement_dequeue *new_llelement = safe_malloc(sizeof(struct llelement_dequeue));
    new_llelement->lle_array = safe_malloc(sizeof(void*)*LLE_ARRAY_LENGTH);
    new_llelement->previous = NULL;
    new_llelement->next = NULL;
    new_llelement->lle_back_length = 0;
    new_llelement->lle_front_length = 0;
    return new_llelement;
}

int llelement_deq__is_empty(struct llelement_dequeue *l) //O(1)
{
    return (l->lle_front_length == -l->lle_back_length);
}

int llelement_deq__is_back_full(struct llelement_dequeue *l) //O(1)
{
    return (l->lle_back_length == (LLE_ARRAY_LENGTH/2));
}

int llelement_deq__is_front_full(struct llelement_dequeue *l) //O(1)
{
    return (l->lle_front_length == (LLE_ARRAY_LENGTH/2));
}

void* llelement_deq__front(struct llelement_dequeue *l) //O(1)
{
    if (llelement_deq__is_empty(l))
        return NULL;
    
    return l->lle_array[LLE_ARRAY_MIDDLE + l->lle_front_length - 1];
}

void* llelement_deq__back(struct llelement_dequeue *l) //O(1)
{
    if (llelement_deq__is_empty(l))
        return NULL;
    
    return l->lle_array[LLE_ARRAY_MIDDLE - l->lle_back_length];
}

int llelement_deq__push_front(struct llelement_dequeue *l, void* element) //O(1)
{
    if (llelement_deq__is_front_full(l))
        return !SUCCESS;

    l->lle_array[LLE_ARRAY_MIDDLE + l->lle_front_length] = element;
    l->lle_front_length += 1;
    return SUCCESS;
}

int llelement_deq__push_back(struct llelement_dequeue *l, void* element) //O(1)
{
    if (llelement_deq__is_back_full(l))
        return !SUCCESS;

    l->lle_array[LLE_ARRAY_MIDDLE - l->lle_back_length - 1] = element;
    l->lle_back_length += 1;
    return SUCCESS;
}

void* llelement_deq__pop_front(struct llelement_dequeue *l) //O(1)
{
    if (llelement_deq__is_empty(l))
        return NULL;

    void* returned = llelement_deq__front(l);
    l->lle_front_length -= 1;
    return returned;
}

void* llelement_deq__pop_back(struct llelement_dequeue *l) //O(1)
{
    if (llelement_deq__is_empty(l))
        return NULL;
    
    void* returned = llelement_deq__back(l);
    l->lle_back_length -= 1;
    return returned;
}

void llelement_deq__link_prev_next(struct llelement_dequeue *prev, struct llelement_dequeue *next) //O(1)
{
    assert_not_null(prev, __func__, "previous llelement");
    assert_not_null(next, __func__, "next llelement");

    prev->next = next;
    next->previous = prev;
}

void llelement_deq__debug_back(struct llelement_dequeue *l, applying_func_t debug_op) //O(LLE_ARRAY_LENGTH)
{
    assert_not_null(l, __func__, "llelement");
    assert_not_null(debug_op, __func__, "debug_op");
    

    unsigned int i = LLE_ARRAY_MIDDLE - l->lle_back_length;
    unsigned int j = (l->lle_front_length >= 0) ?
                        LLE_ARRAY_MIDDLE :
                        LLE_ARRAY_MIDDLE + l->lle_front_length;
    while (i < j){
        debug_op(l->lle_array[i]);
        i++;
    }
}

void llelement_deq__debug_front(struct llelement_dequeue *l, applying_func_t debug_op) //O(LLE_ARRAY_LENGTH)
{
    assert_not_null(l, __func__, "llelement");
    assert_not_null(debug_op, __func__, "debug_op");
    
    unsigned int i = (l->lle_back_length >= 0) ?
                        LLE_ARRAY_MIDDLE :
                        LLE_ARRAY_MIDDLE - l->lle_back_length;
    unsigned int j = LLE_ARRAY_MIDDLE + l->lle_front_length;
    while (i < j){
        debug_op(l->lle_array[i]);
        i++;
    }
}

void llelement_deq__map(struct llelement_dequeue *l, applying_func_t f) //O(LLE_ARRAY_LENGTH)
{
    assert_not_null(l, __func__, "llelement");
    assert_not_null(f, __func__, "applying func");
    
    unsigned int i = LLE_ARRAY_MIDDLE - l->lle_back_length;
    unsigned int j = LLE_ARRAY_MIDDLE + l->lle_front_length;
    while (i < j){
        f(l->lle_array[i]);
        i++;
    }
}

void llelement_deq__free(struct dequeue *d, struct llelement_dequeue *l) //O(LLE_ARRAY_LENGTH)
{
    assert_not_null(l, __func__, "llelement");
    assert_not_null(l, __func__, "dequeue");
    
    unsigned int i = LLE_ARRAY_MIDDLE - l->lle_back_length;
    unsigned int j = LLE_ARRAY_MIDDLE + l->lle_front_length;
    while (i < j){
        dequeue_delete(d, l->lle_array[i]);
        i++;
    }
    free(l->lle_array);
    free(l);
}


////////////////////////////////////////////////////////////////////
///     DEQUEUE FUNCTIONS IMPLEMENTATION
////////////////////////////////////////////////////////////////////

//void* (*debug_op)(void*)
struct dequeue *dequeue__empty_copy_disabled(void* debug_op) //O(1)
{
    struct dequeue *d = safe_malloc(sizeof(struct dequeue));
    struct llelement_dequeue *l = llelement_deq__empty();

    d->back_llelement = l;
    d->front_llelement = l;
    d->length = 0;
    d->operator_copy = NULL;
    d->operator_delete = NULL;
    d->operator_debug = debug_op;
    return d;
}

/*
 * void* (*copy_op)(void*)
 * void* (*delete_op)(void*)
 * void* (*debug_op)(void*)
*/
struct dequeue *dequeue__empty_copy_enabled(void* copy_op, void* delete_op, void* debug_op) //O(1)
{
    struct dequeue *d = safe_malloc(sizeof(struct dequeue));
    struct llelement_dequeue *l = llelement_deq__empty();

    d->back_llelement = l;
    d->front_llelement = l;
    d->length = 0;
    d->operator_copy = copy_op;
    d->operator_delete = delete_op;
    d->operator_debug = debug_op;
    return d;
}

int dequeue__is_copy_enabled(struct dequeue const *d) //O(1)
{
    return ((d->operator_copy != NULL) && (d->operator_delete != NULL));
}

int dequeue__is_empty(struct dequeue const *d) //O(1)
{
    return (d->length == 0);
}

unsigned int dequeue__length(struct dequeue const *d)  //O(1)
{
    return d->length;
}

void* dequeue__front(struct dequeue const *d) //O(1)
{
    assert_not_null(d, __func__, "dequeue parameter");

    if (dequeue__is_empty(d))
        return NULL;

    return llelement_deq__front(d->front_llelement);
}

void* dequeue__back(struct dequeue const *d) //O(1)
{
    assert_not_null(d, __func__, "dequeue parameter");

    if (dequeue__is_empty(d))
        return NULL;

    return llelement_deq__back(d->back_llelement);
}

//note: O(number of llelements in very specific cases)
int dequeue__push_front(struct dequeue *d, void* element)  //O(1)
{
    assert_not_null(d, __func__, "dequeue parameter");

    if (element == NULL)
        return !SUCCESS;

    struct llelement_dequeue *l = d->front_llelement;
    //Finding the next free llelement
    while (llelement_deq__is_front_full(l) && (l->next != NULL))
        l = l->next;

    //Creation of a new one if every llelements's front are full
    if (llelement_deq__is_front_full(l)){
        struct llelement_dequeue *new_llelement = llelement_deq__empty();
        llelement_deq__link_prev_next(l, new_llelement);
        l = new_llelement;
        d->front_llelement = l;
    }

    //Adding the element into the right llelement
    if (llelement_deq__push_front(l, dequeue_read_write(d, element)))
        return !SUCCESS;
    d->length++;

    return SUCCESS;
}

//note: O(number of llelements in very specific cases)
int dequeue__push_back(struct dequeue *d, void* element)  //O(1)
{
    assert_not_null(d, __func__, "dequeue parameter");

    if (element == NULL)
        return !SUCCESS;

    struct llelement_dequeue *l = d->back_llelement;
    //Finding the next free llelement
    while (llelement_deq__is_back_full(l) && (l->next != NULL))
        l = l->next;

    //Creation of a new one if every llelements's back are full
    if (llelement_deq__is_back_full(l)){
        struct llelement_dequeue *new_llelement = llelement_deq__empty();
        llelement_deq__link_prev_next(l, new_llelement);
        l = new_llelement;
        d->back_llelement = l;
    }

    //Adding the element into the right llelement
    if (llelement_deq__push_back(l, dequeue_read_write(d, element)))
        return !SUCCESS;
    d->length++;

    return SUCCESS;
}

void* dequeue__pop_front(struct dequeue *d)  //O(1)
{
    assert_not_null(d, __func__, "dequeue parameter");
    assert_not_null(d->front_llelement, __func__, "dequeue's front llelement");

    if (dequeue__is_empty(d))
        return NULL;

    void* retrieved = llelement_deq__pop_front(d->front_llelement);
    if (retrieved == NULL)
        return NULL;

    d->length--;

    //Removing the empty llelement from the dequeue
    if (llelement_deq__is_empty(d->front_llelement) && !dequeue__is_empty(d)){
        struct llelement_dequeue *tmp = d->front_llelement;
        d->front_llelement = d->front_llelement->previous;
        d->front_llelement->next = NULL;
        //Correcting the other side if it's llelement was the same
        if (d->back_llelement == tmp){
            d->back_llelement = d->front_llelement;
            d->back_llelement->next = NULL;
        }
        llelement_deq__free(d, tmp);
    }
    //Reseting the first llelement if it's empty to gain space
    //(setting back_length and front_length at 0)
    else if (dequeue__is_empty(d)){
        llelement_deq__free(d, d->back_llelement);
        d->back_llelement = llelement_deq__empty();
        d->front_llelement = d->back_llelement;
    }


    return retrieved;
}

void* dequeue__pop_back(struct dequeue *d)  //O(1)
{
    assert_not_null(d, __func__, "dequeue parameter");
    assert_not_null(d->back_llelement, __func__, "dequeue's back llelement");

    if (dequeue__is_empty(d))
        return NULL;


    void* retrieved = llelement_deq__pop_back(d->back_llelement);
    if (retrieved == NULL)
        return NULL;

    d->length--;

    //Removing the empty llelement from the dequeue
    if (llelement_deq__is_empty(d->back_llelement) && !dequeue__is_empty(d)){
        struct llelement_dequeue *tmp = d->back_llelement;
        d->back_llelement = d->back_llelement->previous;
        d->back_llelement->next = NULL;
        //Correcting the other side if it's llelement was the same
        if (d->front_llelement == tmp){
            d->front_llelement = d->back_llelement;
            d->front_llelement->next = NULL;
        }
        llelement_deq__free(d, tmp);
    }
    //Reseting the first llelement if it's empty to gain space
    //(setting back_length and front_length at 0)
    else if (dequeue__is_empty(d)){
        llelement_deq__free(d, d->back_llelement);
        d->back_llelement = llelement_deq__empty();
        d->front_llelement = d->back_llelement;
    }

    return retrieved;
}

int dequeue__remove_front(struct dequeue *d)  //O(1)
{
    assert_not_null(d, __func__, "dequeue parameter");

    if (dequeue__is_empty(d))
        return !SUCCESS;

    void* retrieved = dequeue__pop_front(d);
    if (retrieved == NULL)
        return !SUCCESS;
    
    dequeue_delete(d, retrieved);

    return SUCCESS;
}

int dequeue__remove_back(struct dequeue *d)  //O(1)
{
    assert_not_null(d, __func__, "dequeue parameter");

    if (dequeue__is_empty(d))
        return !SUCCESS;

    void* retrieved = dequeue__pop_back(d);
    if (retrieved == NULL)
        return !SUCCESS;
    
    dequeue_delete(d, retrieved);

    return SUCCESS;
}


void dequeue__free(struct dequeue *d)  //O(dequeue->length)
{
    assert_not_null(d, __func__, "dequeue parameter");
    assert_not_null(d->front_llelement, __func__, "dequeue's front llelement");

    struct llelement_dequeue *l = d->front_llelement;
    struct llelement_dequeue *previous = l->previous;
    struct llelement_dequeue *next = l->next;
    struct llelement_dequeue *tmp;
    //Freeing the previous llelements
    while (previous != NULL){
        tmp = previous->previous;
        llelement_deq__free(d, previous);
        previous = tmp;
    }
    //Freeing the next llelements
    while (next != NULL){
        tmp = next->next;
        llelement_deq__free(d, next);
        next = tmp;
    }
    llelement_deq__free(d, l);
    free(d);
}

void dequeue__debug(struct dequeue const *d, int is_compact) //O(dequeue->length)
{
    if (d == NULL || d->front_llelement == NULL || d->back_llelement == NULL)
        printf("Queue (NULL)\n");
    else if (!is_compact){
        printf("Dequeue (size: %u, content: \n\t{ ", dequeue__length(d));
        //Retrieving the first llelement
        struct llelement_dequeue *l = d->front_llelement;
        while (l->previous != NULL)
            l = l->previous;
        //Printing all the llelements
        while (l != NULL){
            printf("{ ");
            for (unsigned int i = 0; i < LLE_ARRAY_LENGTH; i++)
                d->operator_debug(l->lle_array[i]);
            printf("} <--> ");
            l = l->next;
        }
        printf("NULL }\n)\n");
        }
    else{
        printf("{ ");
        //Printing the back's elements
        struct llelement_dequeue *l = d->back_llelement;
        struct llelement_dequeue *l_backup = l;
        while (l != NULL){
            llelement_deq__debug_back(l, (applying_func_t) d->operator_debug);
            l_backup = l;
            l = l->previous;
        }
        l = l_backup;
        //Printing the front's elements
        while (l != NULL){
            llelement_deq__debug_front(l, (applying_func_t) d->operator_debug);
            l = l->next;
        }
        printf("} ");
    }
}

void dequeue__change_debug_function(struct dequeue *d, void* debug_op) //O(1)
{
    if (debug_op == NULL)
        return;
    d->operator_debug = debug_op;
}

void dequeue__map(struct dequeue *d, applying_func_t f) //O(dequeue->length)
{
    assert_not_null(d, __func__, "dequeue parameter");
    assert_not_null(d, __func__, "dequeue'front");
    assert_not_null(d, __func__, "dequeue's back");

    //Retrieving the first llelement
    struct llelement_dequeue *l = d->front_llelement;
    while (l->previous != NULL)
        l = l->previous;
    //Apllying f on all the llelements
    while (l != NULL){
        llelement_deq__map(l, f);
        l = l->next;
    }
}

 //TODO
void dequeue__mix(struct dequeue *d); //O(dequeue->length)

