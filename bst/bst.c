#include "bst.h"
#include "../common/utils.h"


////////////////////////////////////////////////////////////////////
///     BINARY SEARCH TREE STRUCTURE
////////////////////////////////////////////////////////////////////

struct llelement_bst{
    void* value;
    unsigned int amount;
    struct llelement_bst *rigth_son;
    struct llelement_bst *left_son;
    struct llelement_bst *father;
};

struct bst
{
    unsigned int length;
    struct llelement_bst *root;
    void* (*operator_copy) (void*);
    void (*operator_delete)(void *);
    void (*operator_debug)(void *);
    int (*operator_compare)(void *, void*);
};

////////////////////////////////////////////////////////////////////
///     BINARY SEARCH TREE FUNCTIONS UTILITARIES
////////////////////////////////////////////////////////////////////


// Returns a copy of the element only if the copy in enabled
void* bst_read_write(struct bst const *b, void* element)
{
    if (b->operator_copy != NULL){
        return b->operator_copy(element);
    }
    return element;
}

// Delete the element only if the copy in enabled
void bst_delete(struct bst const *b, void* element)
{
    if (b->operator_delete != NULL){
        return b->operator_delete(element);
    }
}

// Searches a pointer into the bst's array on [0,b[ 
int bst_find(struct bst const *b, void* element)
{
    (void) b;
    (void) element;
    return false;
}

////////////////////////////////////////////////////////////////////
///     LLELEMENT BST FUNCTIONS IMPLEMENTATION
////////////////////////////////////////////////////////////////////

struct llelement_bst *llelement_bst__empty()
{
    struct llelement_bst *l =safe_malloc(sizeof(struct llelement_bst));

    l->value = NULL;
    l->amount = 0;
    l->rigth_son = NULL;
    l->left_son = NULL;
    l->father = NULL;

    return l;
}

void *llelement_bst__free(struct bst *b, struct llelement_bst *l)
{
    bst_delete(b, l->value);
    free(l);

}

////////////////////////////////////////////////////////////////////
///     BINARY SEARCH TREE FUNCTIONS IMPLEMENTATION
////////////////////////////////////////////////////////////////////



struct bst *bst__empty_copy_enabled(void *copy_op, void *delete_op, void *compare_op, void *debug_op)
{
    struct bst *b = safe_malloc(sizeof(struct bst));
    struct llelement_bst *l = llelement_bst__empty();

    b->root = l;
    b->length = 0;
    b->operator_copy = copy_op;
    b->operator_delete = delete_op;
    b->operator_debug = debug_op;
    b->operator_compare = compare_op;
    return b;
}


struct bst *bst__empty_copy_disabled(void *compare_op, void *debug_op)
{
    struct bst *b = safe_malloc(sizeof(struct bst));
    struct llelement_bst *l = llelement_bst__empty();

    b->root = l;
    b->length = 0;
    b->operator_copy = NULL;
    b->operator_delete = NULL;
    b->operator_debug = debug_op;
    b->operator_compare = compare_op;
    return b;
}

int bst__is_copy_enabled(struct bst const *b)
{
    return ((b->operator_copy != NULL) && (b->operator_delete != NULL));
}


int bst__is_empty(struct bst const *b)
{
    return ((b->length == 0) && (b->root->value == NULL));
}

unsigned int bst__length(struct bst const *b)
{
    return b->length;
}

int bst__add(struct bst *b, void* e);


int bst__remove(struct bst *b, void* e);


int bst__is_in(struct bst const *b, void* e);

void* bst__retrieve(struct bst *b, void* e);

struct bst *bst__fusion(struct bst const *bst1, struct bst const *bst2);


void bst__free(struct bst *b);


void bst__debug(struct bst const *b, int is_compact);

void bst__change_debug_function(struct bst *b, void* debug_op)
{
    if (debug_op == NULL)
        return;
    b->operator_debug = debug_op;
}

typedef void (*applying_func_t)(void *object);

void bst__map(struct bst *b, applying_func_t f);


