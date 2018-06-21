#include "common_tests_utils.h"
#include "../stack/stack.h"
#include "../common/utils.h"


int test_stack__empty_copy_enabled()
{
    printf("%s... ", __func__);

    struct stack *p = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);

    if (p == NULL) {
        stack__free(p);
        return !TEST_SUCCESS;
    }

    stack__free(p);

    return TEST_SUCCESS;
}

int test_stack__is_empty_on_empty_stack()
{
    printf("%s... ", __func__);

    struct stack *p = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);

    if (!stack__is_empty(p)) {
        stack__free(p);
        return !TEST_SUCCESS;
    }

    stack__free(p);

    return TEST_SUCCESS;
}

int test_stack__is_empty_on_non_empty_stack()
{
    printf("%s... ", __func__);

    struct stack *p = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value = 0;
    stack__push(p, &value);

    if (stack__is_empty(p)) {
        stack__free(p);
        return !TEST_SUCCESS;
    }

    stack__free(p);

    return TEST_SUCCESS;
}

int test_stack__is_copy_enabled()
{
    printf("%s... ", __func__);

    struct stack *p1 = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    if (!stack__is_copy_enabled(p1)){
        stack__free(p1);
        return !TEST_SUCCESS;
    }
    stack__free(p1);

    struct stack *p2 = stack__empty_copy_disabled(&operator_debug);
    if (stack__is_copy_enabled(p2)){
        stack__free(p2);
        return !TEST_SUCCESS;
    }
    stack__free(p2);

    return TEST_SUCCESS;
}


int test_stack__push_on_non_empty_stack_copy()
{
    printf("%s... ", __func__);

    struct stack *p = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value1 = 0;
    int value2 = 1;
    int value3 = 2;
    int value4 = 3;
    stack__push(p, &value1);
    stack__push(p, &value2);
    stack__push(p, &value3);
    stack__push(p, &value4);
    stack__push(p, &value1);

    if (stack__length(p) != 5) {
        stack__free(p);
        return !TEST_SUCCESS;
    }
    stack__free(p);
    return TEST_SUCCESS;
}

int test_stack__push_on_non_empty_stack_no_copy()
{
    printf("%s... ", __func__);

    struct stack *p = stack__empty_copy_disabled(&operator_debug);
    int value1 = 0;
    int value2 = 1;
    int value3 = 2;
    int value4 = 3;
    stack__push(p, &value1);
    stack__push(p, &value2);
    stack__push(p, &value3);
    stack__push(p, &value4);
    stack__push(p, &value1);

    if (stack__length(p) != 5) {
        stack__free(p);
        return !TEST_SUCCESS;
    }

    value1 = 69;
    value2 = 70;
    value3 = 71;
    value4 = 72;

    if ((* (int*) stack__pop(p) != 69)
    || (* (int*) stack__pop(p) != 72)
    || (* (int*) stack__pop(p) != 71)
    || (* (int*) stack__pop(p) != 70)
    || (* (int*) stack__pop(p) != 69)){
        stack__free(p);
        return !TEST_SUCCESS;
    }

    stack__free(p);
    return TEST_SUCCESS;
}

int test_stack__NULL()
{
    printf("%s... ", __func__);

    struct stack *p1 = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    stack__push(p1, NULL);

    if (!stack__is_empty(p1)) {
        stack__free(p1);
        return !TEST_SUCCESS;
    }

    struct stack *p2 = stack__empty_copy_disabled(&operator_debug);
    stack__push(p2, NULL);

    if (!stack__is_empty(p2)) {
        stack__free(p2);
        return !TEST_SUCCESS;
    }

    stack__free(p1);
    stack__free(p2);
    return TEST_SUCCESS;
}

int test_stack__push_on_multiple_elements()
{
    printf("%s... ", __func__);

    struct stack *s1 = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct stack *s2 = stack__empty_copy_disabled(&operator_debug);
    int value = 0;

    for (unsigned int i = 0; i < 500; i++) {
        stack__push(s1, &value);
        stack__push(s2, &value);
    }

    if ((stack__length(s1) < 500)
    || (stack__length(s2) < 500)) {
        stack__free(s1);
        stack__free(s2);
        return !TEST_SUCCESS;
    }

    stack__free(s1);
    stack__free(s2);

    return TEST_SUCCESS;
}

int test_stack__peek()
{
    printf("%s... ", __func__);

    struct stack *s1 = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct stack *s2 = stack__empty_copy_disabled(&operator_debug);

    if ((!stack__is_empty(s1) || stack__peek(s1) != NULL)
    || (!stack__is_empty(s2) || stack__peek(s2) != NULL)) {
        stack__free(s1);
        stack__free(s2);
        return !TEST_SUCCESS;
    }

    int value = 34;
    stack__push(s1, &value);
    stack__push(s2, &value);
    value = 69;

    int* peek_s1 = (int*) stack__peek(s1);
    int*  peek_s2 = (int*) stack__peek(s2);

    if (stack__is_empty(s1)
    || stack__is_empty(s2)
    || (*peek_s1 != 34)
    || (*peek_s2 != 69)) {
        stack__free(s1);
        stack__free(s2);
        free(peek_s1);
        return !TEST_SUCCESS;
    }

    stack__free(s1);
    stack__free(s2);
    free(peek_s1);

    return TEST_SUCCESS;
}

int test_stack__pop_on_empty_stack()
{
    printf("%s... ", __func__);

    struct stack *s1 = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct stack *s2 = stack__empty_copy_disabled(&operator_debug);
    int *unstacked_s1 = stack__pop(s1);
    int *unstacked_s2 = stack__pop(s2);

    if ((NULL != unstacked_s1)
    || (NULL != unstacked_s2)) {
        stack__free(s1);
        stack__free(s2);
        return !TEST_SUCCESS;
    }

    stack__free(s1);
    stack__free(s2);
    return TEST_SUCCESS;
}

int test_stack__pop_on_non_empty_stack_copy()
{
    printf("%s... ", __func__);

    struct stack *s = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value1 = 58;
    int value2 = 0;
    stack__push(s, &value1);
    stack__push(s, &value2);
    int *unstacked2 = stack__pop(s);
    int *unstacked1 = stack__pop(s);


    if (!stack__is_empty(s)
            || (*unstacked1 != 58)
            || (*unstacked2 != 0)) {
        stack__free(s);
        free(unstacked1);
        free(unstacked2);
        return !TEST_SUCCESS;
    }

    free(unstacked1);
    free(unstacked2);
    stack__free(s);

    return TEST_SUCCESS;
}

int test_stack__pop_on_non_empty_stack_no_copy()
{
    printf("%s... ", __func__);

    struct stack *s = stack__empty_copy_disabled(&operator_debug);
    int value1 = 58;
    int value2 = 0;
    stack__push(s, &value1);
    stack__push(s, &value2);
    value2 = 69;
    int *unstacked2 = stack__pop(s);
    int *unstacked1 = stack__pop(s);


    if (!stack__is_empty(s)
            || (*unstacked1 != 58)
            || (*unstacked2 != 69)) {
        stack__free(s);
        return !TEST_SUCCESS;
    }

    stack__free(s);

    return TEST_SUCCESS;
}

int test_stack__length()
{
    printf("%s... ", __func__);

    struct stack *s = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value1 = 69;
    int value2 = 42;
    stack__push(s, &value1);

    if (stack__length(s) != 1) {
        stack__free(s);
        return !TEST_SUCCESS;
    }

    stack__push(s, &value2);

    if (stack__length(s) != 2) {
        stack__free(s);
        return !TEST_SUCCESS;
    }

    stack__free(s);

    return TEST_SUCCESS;
}

int test_stack__debug()
{
    printf("%s... ", __func__);

    struct stack *s = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value1 = 0;
    int value2 = 1;
    int value3 = 2;
    int value4 = 3;

    stack__push(s, &value1);
    stack__push(s, &value2);
    stack__push(s, &value3);
    stack__push(s, &value4);
    stack__push(s, &value1);

    printf("Expected: { 0 1 2 3 0 }, Got: ");
    stack__debug(s, true);

    stack__free(s);

    return TEST_SUCCESS;
}

int test_stack__map_copy()
{
    printf("%s... ", __func__);

    struct stack *s = stack__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value1 = 0;
    int value2 = 1;
    int value3 = 2;
    int value4 = 3;

    stack__push(s, &value1);
    stack__push(s, &value2);
    stack__push(s, &value3);
    stack__push(s, &value4);
    stack__push(s, &value1);

    stack__map(s, (applying_func_t) plus_op);

    printf("Expected: { 1 2 3 4 1 }, Got: ");
    stack__debug(s, true);

    stack__free(s);

    return TEST_SUCCESS;
}

int test_stack__map_no_copy()
{
    printf("%s... ", __func__);

    struct stack *s = stack__empty_copy_disabled(&operator_debug);
    int value1 = 0;
    int value2 = 1;
    int value3 = 2;
    int value4 = 3;

    stack__push(s, &value1);
    stack__push(s, &value2);
    stack__push(s, &value3);
    stack__push(s, &value4);
    stack__push(s, &value1);
    stack__push(s, &value3);
    stack__push(s, &value4);

    stack__map(s, (applying_func_t) plus_op);

    printf("Expected: { 1 2 3 4 1 3 4 }, Got: ");
    stack__debug(s, true);

    if ((value1 != 1)
    || (value2 != 2)
    || (value3 != 3)
    || (value4 != 4)) {
        stack__free(s);
        return !TEST_SUCCESS; 
    }

    stack__free(s);

    return TEST_SUCCESS;
}


int main()
{
    printf("----------- TEST STACK -----------\n");

    int nb_success = 0;
    int nb_tests = 0;

    print_test_result(test_stack__empty_copy_enabled(), &nb_success, &nb_tests);
    print_test_result(test_stack__is_empty_on_empty_stack(), &nb_success, &nb_tests);
    print_test_result(test_stack__is_empty_on_non_empty_stack(), &nb_success, &nb_tests);
    print_test_result(test_stack__is_copy_enabled(), &nb_success, &nb_tests);
    print_test_result(test_stack__push_on_non_empty_stack_copy(), &nb_success, &nb_tests);
    print_test_result(test_stack__push_on_non_empty_stack_no_copy(), &nb_success, &nb_tests);
    print_test_result(test_stack__NULL(), &nb_success, &nb_tests);
    print_test_result(test_stack__push_on_multiple_elements(), &nb_success, &nb_tests);
    print_test_result(test_stack__peek(), &nb_success, &nb_tests);
    print_test_result(test_stack__pop_on_empty_stack(), &nb_success, &nb_tests);
    print_test_result(test_stack__pop_on_non_empty_stack_copy(), &nb_success, &nb_tests);
    print_test_result(test_stack__pop_on_non_empty_stack_no_copy(), &nb_success, &nb_tests);
    print_test_result(test_stack__length(), &nb_success, &nb_tests);
    print_test_result(test_stack__debug(), &nb_success, &nb_tests);
    print_test_result(test_stack__map_copy(), &nb_success, &nb_tests);
    print_test_result(test_stack__map_no_copy(), &nb_success, &nb_tests);

    print_test_summary(nb_success, nb_tests);

    return TEST_SUCCESS;
}
