#include "common_tests_utils.h"
#include "../queue/queue.h"
#include "../common/utils.h"

//TODO: test avec et sans copie, et faire le moins de debug possible

int test_queue__empty_copy_enabled()
{
    printf("%s... ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);

    if (q == NULL) {
        queue__free(q);
        return !TEST_SUCCESS;
    }
    queue__free(q);

    return TEST_SUCCESS;
}

int test_queue__is_empty_on_empty_queue()
{
    printf("%s... ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);

    if (!queue__is_empty(q)) {
        queue__free(q);
        return !TEST_SUCCESS;
    }

    queue__free(q);

    return TEST_SUCCESS;
}

int test_queue__is_empty_on_non_empty_queue()
{
    printf("%s... ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value = 1;

    if (queue__enqueue(q, &value) != TEST_SUCCESS) {
        queue__free(q);
        return !TEST_SUCCESS;
    }

    if (queue__is_empty(q)) {
        queue__free(q);
        return !TEST_SUCCESS;
    }

    queue__free(q);

    return TEST_SUCCESS;
}

int test_queue__enqueue_on_non_empty_queue()
{
    printf("%s... ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    int value4 = 4;
    queue__enqueue(q, &value1);
//    queue__debug(q, 0);
    queue__enqueue(q, &value2);
//    queue__debug(q, 0);
    queue__enqueue(q, &value3);
//    queue__debug(q, 0);
    queue__enqueue(q, &value4);
//    queue__debug(q, 0);
    queue__enqueue(q, &value1);
//    queue__debug(q, 0);

    if (queue__length(q) != 5) {
        queue__free(q);
        return !TEST_SUCCESS;
    }
    queue__free(q);
    return TEST_SUCCESS;
}

int test_queue_NULL()
{
    printf("%s... ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    queue__enqueue(q, NULL);

    if (!queue__is_empty(q)) {
        queue__free(q);
        return !TEST_SUCCESS;
    }

    queue__free(q);
    return TEST_SUCCESS;
}

int test_queue__enqueue_on_multiple_elements()
{
    printf("%s... ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value = 1;

    for (unsigned int i = 0; i < 500; i++) {
        queue__enqueue(q, &value);
    }

    if (queue__length(q) < 500) {
        queue__free(q);
        return !TEST_SUCCESS;
    }

    queue__free(q);

    return TEST_SUCCESS;
}

int test_queue__front()
{
    printf("%s... ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);

    int* front  = queue__front(q);

    if (!queue__is_empty(q) || front != NULL) {
        free(front);
        queue__free(q);
        return !TEST_SUCCESS;
    }

    free(front);

    int value = 5;
    queue__enqueue(q, &value);

    front = queue__front(q);

    if (queue__is_empty(q) || *front != 5) {
        free(front);
        queue__free(q);
        return !TEST_SUCCESS;
    }

    free(front);
    queue__free(q);

    return TEST_SUCCESS;
}

int test_queue__back()
{
    printf("%s... ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);

    int* back = queue__back(q);

    if (!queue__is_empty(q) || back != NULL) {
        free(back);
        queue__free(q);
        return !TEST_SUCCESS;
    }

    free(back);

    int value1 = 6;
    int value2 = 7;
    queue__enqueue(q, &value1);
    queue__enqueue(q, &value2);

    back = queue__back(q);

    if (queue__is_empty(q) || *back != 7) {
        free(back);
        queue__free(q);
        return !TEST_SUCCESS;
    }

    free(back);
    queue__free(q);

    return TEST_SUCCESS;
}

int test_queue__dequeue_on_empty_queue()
{
    printf("%s... ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int *front = queue__front(q);
    queue__dequeue(q);

    if (front != NULL) {
        free(front);
        queue__free(q);
        return !TEST_SUCCESS;
    }

    free(front);
    queue__free(q);
    return TEST_SUCCESS;
}

int test_queue__dequeue_on_non_empty_queue()
{
    printf("%s... ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int c1 = 8;
    int c2 = 1;

    queue__enqueue(q, &c1);
    queue__enqueue(q, &c2);

    int *front_c1 = queue__front(q);
    queue__dequeue(q);
    int *front_c2 = queue__front(q);
    queue__dequeue(q);

    if (!queue__is_empty(q)
            || (*front_c1 != 8)
            || (*front_c2 != 1)) {
        free(front_c1);
        free(front_c2);
        queue__free(q);
        return !TEST_SUCCESS;
    }

    free(front_c1);
    free(front_c2);
    queue__free(q);

    return TEST_SUCCESS;
}

int test_queue_length()
{
    printf("%s... ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value1 = 9;
    int value2 = 10;
    queue__enqueue(q, &value1);

    if (queue__length(q) != 1) {
        queue__free(q);
        return !TEST_SUCCESS;
    }

    queue__enqueue(q, &value2);

    if (queue__length(q) != 2) {
        queue__free(q);
        return !TEST_SUCCESS;
    }

    queue__free(q);

    return TEST_SUCCESS;
}

int test_queue_debug()
{
    printf("%s: ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value1 = 11;
    int value2 = 12;
    int value3 = 13;
    int value4 = 14;

    queue__enqueue(q, &value1);
    queue__enqueue(q, &value2);
    queue__dequeue(q);

//    printf("\nExpected: (6) and (NULL 6)\n");

//    queue__debug(q, false);

    queue__enqueue(q, &value3);
    queue__enqueue(q, &value4);

//    printf("\nExpected: (6 7 8) and (NULL 6 7 8)\n");

//    queue__debug(q, false);

    queue__free(q);

//    printf("%s... ", __func__);
    return TEST_SUCCESS;
}

int test_queue__enqueue_and_dequeue_on_multiple_elements_with_debug()
{
    printf("%s: \n", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value = 1;

    for (unsigned int i = 0; i < 60; i++) {
        queue__enqueue(q, &value);
    }

//    printf("\nAdded 60 elements, expected capacity of 64 and size of 60\n");

    if (queue__length(q) < 60) {
        queue__free(q);
        return !TEST_SUCCESS;
    }

//    queue__debug(q, true);

    for (unsigned int i = 0; i < 40; i++) {
        queue__dequeue(q);
    }

//    printf("\nRemoved 40 elements, expected capacity of 32 and size of 20\n");

    if (queue__length(q) < 20) {
        queue__free(q);
        return !TEST_SUCCESS;
    }

//    queue__debug(q, true);

    for (unsigned int i = 0; i < 20; i++) {
        queue__enqueue(q, &value);
    }

//    printf("\nAdded 20 elements, expected capacity of 64 and size of 40\n");

    if (queue__length(q) < 40) {
        queue__free(q);
        return !TEST_SUCCESS;
    }

//    queue__debug(q, true);

    for (unsigned int i = 0; i < 30; i++) {
        queue__dequeue(q);
    }

//    printf("\nRemoved 30 elements, expected capacity of 16 and size of 10\n");

    if (queue__length(q) < 10) {
        queue__free(q);
        return !TEST_SUCCESS;
    }

//    queue__debug(q, true);

    queue__free(q);

//    printf("%s... ", __func__);
    return TEST_SUCCESS;
}



int test_queue__map()
{
    printf("%s ", __func__);

    struct queue *q = queue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    int value1 = 11;
    int value2 = 12;
    int value3 = 13;
    int value4 = 14;

    queue__enqueue(q, &value1);
    queue__enqueue(q, &value2);
    queue__enqueue(q, &value3);
    queue__enqueue(q, &value4);
    queue__enqueue(q, &value1);

    queue__map(q, (applying_func_t) plus_op);

    printf("Expected: (6 7 8 9 6)... Got: ");
//    queue__debug(q, true);

    queue__free(q);

    return TEST_SUCCESS;
}



int main()
{
    printf("----------- TEST QUEUE -----------\n");

    int nb_success = 0;
    int nb_tests = 0;

    print_test_result(test_queue__empty_copy_enabled(), &nb_success, &nb_tests);
    print_test_result(test_queue__is_empty_on_empty_queue(), &nb_success, &nb_tests);
    print_test_result(test_queue__is_empty_on_non_empty_queue(), &nb_success, &nb_tests);
    print_test_result(test_queue__enqueue_on_non_empty_queue(), &nb_success, &nb_tests);
    print_test_result(test_queue_NULL(), &nb_success, &nb_tests);
    print_test_result(test_queue__enqueue_on_multiple_elements(), &nb_success, &nb_tests);
    print_test_result(test_queue__front(), &nb_success, &nb_tests);
    print_test_result(test_queue__back(), &nb_success, &nb_tests);
    print_test_result(test_queue__dequeue_on_empty_queue(), &nb_success, &nb_tests);
    print_test_result(test_queue__dequeue_on_non_empty_queue(), &nb_success, &nb_tests);
    print_test_result(test_queue_length(), &nb_success, &nb_tests);
    print_test_result(test_queue_debug(), &nb_success, &nb_tests);
    print_test_result(test_queue__map(), &nb_success, &nb_tests);
    print_test_result(test_queue__enqueue_and_dequeue_on_multiple_elements_with_debug(), &nb_success, &nb_tests);

    print_test_summary(nb_success, nb_tests);

    return TEST_SUCCESS;
}
