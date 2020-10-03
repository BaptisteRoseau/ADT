#include "common_tests_utils.h"
#include "../bst/bst.h"
#include "../common/utils.h"

////////////////////////////////////////////////////////////////////
///     OPERATORS FUNCTIONS IMPLEMENTATION
////////////////////////////////////////////////////////////////////

void *int__copy(const int *i)
{
    int *copy = safe_malloc(sizeof(*copy));
    *copy = *i;
    return copy;
}

void int__free(int *i)
{
    free(i);
}

int int__cmp(const int *i1, const int *i2)
{
    if (*i1 > *i2)
        return 1;
    if (*i1 < *i2)
        return -1;
    return 0;
}

void int__debug(const int *i)
{
    fflush(stdout);
    printf("%d ", *i);
}

////////////////////////////////////////////////////////////////////
///     SET FUNCTIONS TESTS
////////////////////////////////////////////////////////////////////


int main()
{
    printf("----------- TEST BST -----------\n");

    int nb_success = 0;
    int nb_tests = 0;

    //print_test_result(test_bst__empty(), &nb_success, &nb_tests);

    print_test_summary(nb_success, nb_tests);

    return TEST_SUCCESS;
}
