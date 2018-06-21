#include <string.h>
#include "utils.h"


void assert_not_null(const void *ptr, const char *caller_fct, char *object)
{
    if (ptr == NULL) {
        const unsigned int size = strlen(caller_fct) + strlen(": NULL value on ") + strlen(object) + 1;
        char message[size];
        snprintf(message, size, "%s: NULL value on %s", caller_fct, object);
        exit_on_error(message);
    }
}

void exit_on_error(char *message)
{
    printf("[ERROR] %s. Now exiting...\n", message);
    exit(EXIT_FAILURE);
}

void *safe_malloc(unsigned int size)
{
    void *ptr = malloc(size);
    if (ptr == NULL)
        exit_on_error("Memory allocation failure");
    return ptr;
}

