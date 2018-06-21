#include "common_tests_utils.h"


////////////////////////////////////////////////////////////////////
///     PRINT FUNCTIONS FOR TEST SUMMARY
////////////////////////////////////////////////////////////////////

void print_test_result(int result, int *nb_success, int *nb_tests)
{
    if (result == TEST_SUCCESS) {
        printf("\x1B[32mSUCCESS\x1B[0m\n");
        (*nb_success)++;
    } else {

        printf("\x1B[31mFAILED\x1B[0m\n");
    }

    (*nb_tests)++;
}

void print_test_summary(int nb_success, int nb_tests)
{
    if (nb_success == nb_tests)
        printf("TESTS SUMMARY: \t\x1B[32m%d\x1B[0m/%d\n", nb_success, nb_tests);
    else
        printf("TESTS SUMMARY: \t\x1B[31m%d\x1B[0m/%d\n", nb_success, nb_tests);
}


////////////////////////////////////////////////////////////////////
///     OPERATOR FUNCTIONS FOR INT
////////////////////////////////////////////////////////////////////

void* operator_copy(const int *p_value)
{
    if (p_value == NULL)
        return NULL;

    int *new_int = malloc(sizeof(int));
    if (new_int == NULL) return NULL;
    *new_int = *p_value;
    return new_int;
}

void operator_delete(int *p_value)
{
    free(p_value);
}

int operator_compare(const int *v1, const int *v2)
{
    if (v1 == NULL || v2 == NULL) {
        printf("NULL value compared");
        exit(EXIT_FAILURE);
    }

    if (v1 < v2)
        return -1;
    else if (v1 == v2)
        return 0;
    else
        return 1;
}

void operator_debug(const int *p_value)
{
    //setvbuf (stdout, NULL, _IONBF, 0);
    if (p_value == NULL)
        printf("NULL ");
    else
        printf("%d ", *p_value);
}

void plus_op(int *v)
{
    *v += 1;
}
