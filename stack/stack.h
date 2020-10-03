#ifndef __STACK_H__
#define __STACK_H__

#include <stddef.h>

/**
 * Implementation of a FILO Abstract Data Type
 *
 * Notes :
 * 1) You have to correctly implement copy, delete and debug operators
 * by handling NULL value, otherwise you can end up with an undefined behaviour.
 * The prototypes of these functions are :
 * void* (*copy_op)(void*)
 * void* (*delete_op)(void*)
 * void* (*debug_op)(void*)
 *
 * 2) stack_peek() and stack_pop() return a dynamically allocated pointer to the head element of
 * the stack in order to make it survive independently of the stack life cycle.
 * The user has to manually free the return pointer after usage.
 */
struct stack;


/**
 * @brief Create an empty stack
 * @note Complexity: O(1)
 * @return a newly created stack
 */
struct stack *stack__empty_copy_enabled(void* copy_op, void* delete_op, void* debug_op);


/**
 * @brief Create an empty stack
 * @note Complexity: O(1)
 * @return a newly created stack
 */
struct stack *stack__empty_copy_disabled(void* debug_op);


/**
 * @brief Verify if the element's copy is enabled for the given stack
 * @note Complexity: O(1)
 * @param s is the stack you want to check
 * @return 1 if copy is enabled, 0 if not
 */
int stack__is_copy_enabled(struct stack const *s);


/**
 * @brief Verify if the stack is empty
 * @note Complexity: O(1)
 * @param s the stack
 * @return 1 if empty
 * @return 0 otherwise
 */
int stack__is_empty(struct stack const *s);

  
/**
 * @brief Push an element in the stack
 * @note Complexity: O(1) (O(n) is stack's length is a power of 2)
 * @param s the stack
 * @param element the element to add
 * @return 0 on success, 1 otherwise
 */
int stack__push(struct stack *s, void* element);


/**
 * @brief Retrieve the element on the top of the stack without removing it

 * @note Complexity: O(1)
 * @param s the stack
 * @return an enumeration representing the element on top
 */
void* stack__peek(struct stack const *s);


/**
 * @brief Pop an element out of the stack
 * @note Complexity: O(1) (O(n) is stack's length is a power of 2)
 * @param s the stack
 * @return an enumeration representing the popped element
 */
void* stack__pop(struct stack *s);


/**
 * @brief Count the number of elements in the stack
 * @note Complexity: O(1)
 * @param s the stack
 * @return an integer corresponding to the number of elements in the stack
 */
size_t stack__length(struct stack const *s);


/**
 * @brief Randomly mixes the stack's content
 * @note Complexity: O(n)
 * @param s the stack
 * */
void stack__mix(struct stack *s);


/**
 * function pointer for lambda applying
 */
typedef void (*applying_func_t)(void *object);


/**
 * @brief Applies a function with only a stack object as parameter
 * @note Complexity: O(n) if copy enabled, O(n¹) if not 
 * @param s the stack
 * @param f the applying function
 */
void stack__map(struct stack *s, applying_func_t f);


/**
 * @brief Free all allocated memory used by the stack
 * @note Complexity: O(n)
 * @param s the stack to free
 */
void stack__free(struct stack *s);


/**
 * @brief Prints the stack's content
 * @note Complexity: O(n)
 * @param s the stack to debug
 * @param is_compact to display a compact debug (only values)
 */
void stack__debug(struct stack const *s, int is_compact);


/**
 * @brief Modify the debug function
 * @note Complexity: O(1)
 * @param s the stack where the debug function have to be changed
 * @param debug_op the new debug function: void* (*debug_op)(void*)
 */
void stack__change_debug_function(struct stack *s, void* debug_op);


/**
 * @brief Remove all NULL from the stack
 * @note Complexity: O(n²)
 * @param s is the stack you want to clean
 * @return 1 if the stack has been cleaned up, 0 else
 */
int stack__clean_NULL(struct stack *s);

#endif
