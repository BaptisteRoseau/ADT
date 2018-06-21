#ifndef __UTILS_H__
#define __UTILS_H__

#include <stdio.h>
#include <stdlib.h>

#ifndef SUCCESS
#define SUCCESS 0
#endif
#ifndef true
#define true 1
#endif
#ifndef false
#define false 0
#endif

/**
 * @brief Checks that a pointer isn't null, quit otherwise
 */
void assert_not_null(const void *ptr, const char *caller_fct, char *object);


/**
 * @brief an error message and exits the application
 * @param message the error message to print
 */
void exit_on_error(char* message);


/**
 * @brief Perform a safe malloc interrupting program on memory allocation failure
 * @param size the size to allocate
 * @return a general pointer
 */
void* safe_malloc(unsigned int size);

#endif
