#ifndef __BST_H__
#define __BST_H__

struct bst;


/**
 * @brief bst the empty object with copy enabled
 * 
 * @param copy_op is a copy function for the used type.
 * The copy function must have the following prototype and use a malloc:
 * void* copy_op(void*);
 * 
 * @param delete_op is a free function for all the allocated memory used by the type
 * The delete function must have the following prototype:
 * void delete_op(void*);
 * 
 * @param compare_op is a comparison function for the used type.
 * The comparison function must have the following prototype:
 * int cmp_op(void* const x, void* const y);
 * It have to respect the following rule:
 * - x > y : 1
 * - x == y : 0
 * - x < y : -1
 *
 * @param debug_op is a function displaying bst debug information and its content
 * 
 * @return An empty struct bst* 
 */
struct bst *bst__empty_copy_enabled(void *copy_op, void *delete_op, void *compare_op, void *debug_op);


/**
 * @brief bst the empty object with copy disabled
 * 
 * @param compare_op is a comparison function for the used type.
 * The comparison function must have the following prototype:
 * int cmp_op(void* x, void* y);
 * It have to respect the following rule:
 * - x > y : 1
 * - x == y : 0
 * - x < y : -1
 *
 * @param debug_op is a function displaying bst debug information and its content
 * 
 * @return An empty struct bst* 
 */
struct bst *bst__empty_copy_disabled(void *compare_op, void *debug_op);


/**
 * @brief Verify if the element's copy is enabled for the given stack
 * @note Complexity: O(1)
 * @param s is the stack you want to check
 * @return 1 if copy is enabled, 0 if not
 */
int bst__is_copy_enabled(struct bst const *b);


/**
 * @brief Test to know if a bst is empty
 * 
 * @param s is the given bst
 * @return 1 if the bst is empty, 0 else
 */
int bst__is_empty(struct bst const *b);


/**
 * @brief Give the current amount of objects in the bst
 * 
 * @param s is the bst
 * @return The amount of objects in the bst
 */
unsigned int bst__length(struct bst const *b);


/**
 * @brief Adds a copy of an object into the given bst
 * The object won't be added if it already is in the bst.
 * 
 * @param s is the bst
 * @param e is the object you want to add
 * @return 0 for a success, 1 for a failure
 */
int bst__add(struct bst *b, void* e);


/**
 * @brief Remove an object from the given bst
 * 
 * @param s is the bst
 * @param e is the object you want to remove
 * @return 0 for a success, 1 for a failure
 */
int bst__remove(struct bst *b, void* e);


/**
 * @brief Searches an object into the given bst
 * 
 * @param s is the given bst
 * @param e is the object you're searching
 * @return 1 if the object is in the bst, 0 else
 */
int bst__is_in(struct bst const *b, void* e);


/**
 * @brief Gets the pointer stocked into the bst to the researched element
 * @attention DO NOT FREE THAT POINTER !! Or the bst__free will have a double-free issue.
 * @warning As the real pointer is retrieved, if you need to edit its content, you shouldn't use this function only
 * if it affects element comparison, as the bst is ordered at add step, this will break search feature otherwise.
 * In this case you should use bst__retrieve, then make a copy and edit it, use bst__remove, and bst__add at last
 * 
 * @param s is the given bst
 * @param e is the element you're looking for
 * @return A pointer to the data stocked by the bst without a copy.
 */
void* bst__retrieve(struct bst *b, void* e);


/**
 * @brief Realise the fusion of the two given bst
 * WARNING:The functions given in the initialisation MUST BE the same for the two bsts.
 * 
 * @return a struct bst which is the fusion of the two given bst
 */
struct bst *bst__fusion(struct bst const *bst1, struct bst const *bst2);


/**
 * @brief Free all the allocated memory in the bst.
 * 
 * @param s is the bst you want to free
 */
void bst__free(struct bst *b);


/**
 * @brief Prints the bst
 * 
 * @param s is the bst you want to print
 * @param is_compact to display a compact debug (only values)
 */
void bst__debug(struct bst const *b, int is_compact);


/**
 * @brief Modify the debug function
 * @note Complexity: O(1)
 * @param s the bst where the debug function have to be changed
 * @param debug_op the new debug function: void* (*debug_op)(void*)
 */
void bst__change_debug_function(struct bst *b, void* debug_op);


/**
 * function pointer for lambda applying
 */
typedef void (*applying_func_t)(void *object);

/**
 * @brief Applies a function with only a bst object as parameter
 * @param s the bst
 * @param f the applying function
 */
void bst__map(struct bst *b, applying_func_t f);

#endif
