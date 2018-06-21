#ifndef __DEdequeue_H__
#define __DEdequeue_H__

#include <stddef.h>

/**
 * Implementation of a dequeue Abstract Data Type
 *
 * Notes :
 * 1) You have to correctly implement copy, delete and debug operators
 * by handling NULL value, otherwise you can end up with an undefined behaviour.
 * The prototypes of these functions are :
 * void* (*copy_op)(void*)
 * void* (*delete_op)(void*)
 * void* (*debug_op)(void*)
 *
 * 2) dequeue__front() and dequeue_back() return a dynamically allocated pointer to an element of
 * the dequeue in order to make it survive independently of the dequeue's life cycle.
 * The user has to manually free the returned pointer after usage.
 */
struct dedequeue;

//TODO: Documentation


/**
 * @brief Create an empty dequeue
 * @note Complexity: O(1)
 * @param debug_op debug operator for printing an element
 * @return a newly created dequeue without copy
 */
struct dequeue *dequeue__empty_copy_disabled(void* debug_op);


/**
 * @brief Create an empty dequeue
 * @note Complexity: O(1)
 * @param copy_op copy operator, creating a dynamically allocated copy of an element
 * @param delete_op delete operator, freeing an element
 * @param debug_op debug operator for printing an element
 * @return a newly created dequeue with copy
 */
struct dequeue *dequeue__empty_copy_enabled(void* copy_op, void* delete_op, void* debug_op);


/**
 * @brief Verify if the element's copy is enabled for the given dequeue
 * @note Complexity: O(1)
 * @param d is the dequeue you want to check
 * @return 1 if copy is enabled, 0 if not
 */
int dequeue__is_copy_enabled(struct dequeue const *d);


/**
 * @brief Verify if the dequeue is empty
 * @note Complexity: O(1)
 * @param d the dequeue
 * @return 1 if empty, 0 otherwise
 */
int dequeue__is_empty(struct dequeue const *d);


/**
 * @brief Retrieve a copy of the front element
 * @details The element must be manually freed by user afterward
 * @note Complexity: O(1)
 * @param d the dequeue
 * @return (a copy of) the front element pointer
 */
void* dequeue__front(struct dequeue const *d);


/**
 * @brief Retrieve a copy of the back element
 * @details The element must be manually freed by user afterward
 * @note Complexity: O(1)
 * @param d the dequeue
 * @return (a copy of) of the back element pointer
 */
void* dequeue__back(struct dequeue const *d);


/**
 * @brief Push an element at the front of the dequeue
 * @note Complexity: O(1)
 * @param d the dequeue
 * @param element the element to add at the front
 * @return 0 on success, 1 otherwise
 */
int dequeue__push_front(struct dequeue *d, void* element);


/**
 * @brief Push an element at the back of the dequeue
 * @note Complexity: O(1)
 * @param d the dequeue
 * @param element the element to add at the back
 * @return 0 on success, 1 otherwise
 */
int dequeue__push_back(struct dequeue *d, void* element);


/**
 * @brief Delete the element at the front of the dequeue and returns it
 * @note Complexity: O(1)
 * @param d the dequeue
 * @return A pointor to (a copy of) the front element
 */
void* dequeue__pop_front(struct dequeue *d);


/**
 * @brief Delete the element at the back of the dequeue and returns it
 * @note Complexity: O(1)
 * @param d the dequeue
 * @return A pointor to (a copy of) the back element
 */
void* dequeue__pop_back(struct dequeue *d);


/**
 * @brief Delete the element at the front of the dequeue without returning it
 * @note Complexity: O(1)
 * @param d the dequeue
 * @return 0 on success, 1 otherwise
 */
int dequeue__remove_front(struct dequeue *d);


/**
 * @brief Delete the element at the back of the dequeue without returning it
 * @note Complexity: O(1)
 * @param d the dequeue
 * @return 0 on success, 1 otherwise
 */
int dequeue__remove_back(struct dequeue *d);


/**
 * @brief Count the total number of elements in the dequeue
 * @note Complexity: O(1)
 * @param d the dequeue
 * @return an integer corresponding to the number of elements in the dequeue
 */
unsigned int dequeue__length(struct dequeue const *d);


/**
 * @brief Free all allocated memory used by the dequeue
 * @note Complexity: O(number of elements in the dequeue)
 * @param d the dequeue to free
 */
void dequeue__free(struct dequeue *d);


/**
 * @brief Prints the dequeue's content
 * @note Complexity: O(number of elements in the dequeue)
 * @param d the dequeue to debug
 * @param is_compact to display a compact debug (only values)
 */
void dequeue__debug(struct dequeue const *d, int is_compact);

/**
 * @brief Modify the debug function
 * @note Complexity: O(1)
 * @param d the dequeue where the debug function have to be changed
 * @param debug_op the new debug function: void* (*debug_op)(void*)
 */
void dequeue__change_debug_function(struct dequeue *d, void* debug_op);


/**
 * function pointer for lambda applying
 */
typedef void (*applying_func_t)(void *object);

/**
 * @brief Applies a function with only a dequeue object as parameter
 * @note Complexity: O(number of elements in the dequeue)
 * @param d the dequeue
 * @param f the applying function
 */
void dequeue__map(struct dequeue *d, applying_func_t f);


/**
 * @brief Randomly changes the order of the dequeue's content
 * @note Complexity: O(number of elements in the dequeue)
 * @param d the dequeue
 */
void dequeue__mix(struct dequeue *d);

#endif
