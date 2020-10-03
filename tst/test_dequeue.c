#include "common_tests_utils.h"
#include "../dequeue/dequeue.h"
#include "../common/utils.h"

/*
int test_dequeue__()
{
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}*/

////////////////////////////////////////////////////////////////////
///     FONCTIONAL TESTS
////////////////////////////////////////////////////////////////////

int test_dequeue__empty()
{
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__push_front()
{
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value1_backup = value1;

    dequeue__push_front(d_cpy, &value1);
    dequeue__push_front(d_no_cpy, &value1);
    value1 += 1;

    if (dequeue__is_empty(d_cpy)
    || (dequeue__is_empty(d_no_cpy))
    || (dequeue__length(d_cpy) != 1)
    || (dequeue__length(d_no_cpy) != 1)
    || (* (int*) dequeue__front(d_cpy) != value1_backup)
    || (* (int*) dequeue__front(d_no_cpy) != value1)){
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__push_front_a_lot()
{
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value1_backup = value1;

    for (unsigned int i = 0; i < 500; i++){
        dequeue__push_front(d_cpy, &value1);
        dequeue__push_front(d_no_cpy, &value1);
    }
    value1 += 1;

    if (dequeue__is_empty(d_cpy)
    || (dequeue__is_empty(d_no_cpy))
    || (dequeue__length(d_cpy) != 500)
    || (dequeue__length(d_no_cpy) != 500)    
    || (* (int*) dequeue__front(d_cpy) != value1_backup)
    || (* (int*) dequeue__front(d_no_cpy) != value1)){
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__push_back()
{
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value1_backup = value1;

    dequeue__push_back(d_cpy, &value1);
    dequeue__push_back(d_no_cpy, &value1);
    value1 += 1;

    if (dequeue__is_empty(d_cpy)
    || (dequeue__is_empty(d_no_cpy))
    || (dequeue__length(d_cpy) != 1)
    || (dequeue__length(d_no_cpy) != 1)
    || (* (int*) dequeue__back(d_cpy) != value1_backup)
    || (* (int*) dequeue__back(d_no_cpy) != value1)){
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__push_back_a_lot()
{
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value1_backup = value1;

    for (unsigned int i = 0; i < 500; i++){
        dequeue__push_back(d_cpy, &value1);
        dequeue__push_back(d_no_cpy, &value1);
    }
    value1 += 1;

    if (dequeue__is_empty(d_cpy)
    || (dequeue__is_empty(d_no_cpy))
    || (dequeue__length(d_cpy) != 500)
    || (dequeue__length(d_no_cpy) != 500)
    || (* (int*) dequeue__back(d_cpy) != value1_backup)
    || (* (int*) dequeue__back(d_no_cpy) != value1)){
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__push_front_and_back_a_lot()
{
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value1_backup = value1;
    int value2 = 3;
    int value2_backup = value2;

    for (unsigned int i = 0; i < 500; i++){
        dequeue__push_back(d_cpy, &value1);
        dequeue__push_back(d_no_cpy, &value1);
        dequeue__push_front(d_cpy, &value2);
        dequeue__push_front(d_no_cpy, &value2);
    }
    value1 += 1;
    value2 += 1;
    

    if (dequeue__is_empty(d_cpy)
    || (dequeue__is_empty(d_no_cpy))
    || (dequeue__length(d_cpy) != 1000)
    || (dequeue__length(d_no_cpy) != 1000)
    || (* (int*) dequeue__back(d_cpy) != value1_backup)
    || (* (int*) dequeue__back(d_no_cpy) != value1)
    || (* (int*) dequeue__front(d_cpy) != value2_backup)
    || (* (int*) dequeue__front(d_no_cpy) != value2)){
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }


    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__pop_front()
{
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value1_backup = value1;

    dequeue__push_front(d_cpy, &value1);
    dequeue__push_front(d_no_cpy, &value1);
    value1 += 1;

    int *retrieved_cpy = (int*) dequeue__pop_front(d_cpy);
    int *retrieved_no_cpy = (int*) dequeue__pop_front(d_no_cpy);

    if (!dequeue__is_empty(d_cpy)
    || (!dequeue__is_empty(d_no_cpy))
    || (dequeue__length(d_cpy) != 0)
    || (dequeue__length(d_no_cpy) != 0)
    || (*retrieved_cpy != value1_backup)
    || (*retrieved_no_cpy != value1)){
        free(retrieved_cpy);
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    free(retrieved_cpy);
    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__pop_front_a_lot()
{
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value1_backup = value1;

    for (unsigned int i = 0; i < 500; i++){
        dequeue__push_front(d_cpy, &value1);
        dequeue__push_front(d_no_cpy, &value1);
    }
    value1 += 1;

    int *tmp_cpy;
    int *tmp_no_cpy;
    for (unsigned int i = 0; i < 500; i++){
        tmp_cpy = (int*) dequeue__pop_front(d_cpy);
        if ((tmp_cpy != NULL) && (*tmp_cpy != value1_backup)){
            if (tmp_cpy != NULL)
                free(tmp_cpy);
            dequeue__free(d_cpy);
            dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
        }
        free(tmp_cpy);

        tmp_no_cpy = dequeue__pop_front(d_no_cpy);
        if ((tmp_no_cpy != NULL) && (*tmp_no_cpy != value1)){
            dequeue__free(d_cpy);
            dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
        }
    }

    if (!dequeue__is_empty(d_cpy)
    || (!dequeue__is_empty(d_no_cpy))
    || (dequeue__length(d_cpy) != 0)
    || (dequeue__length(d_no_cpy) != 0)){
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__pop_back()
{    
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value1_backup = value1;

    dequeue__push_back(d_cpy, &value1);
    dequeue__push_back(d_no_cpy, &value1);
    value1 += 1;

    int *retrieved_cpy = (int*) dequeue__pop_back(d_cpy);
    int *retrieved_no_cpy = (int*) dequeue__pop_back(d_no_cpy);

    if (!dequeue__is_empty(d_cpy)
    || (!dequeue__is_empty(d_no_cpy))
    || (dequeue__length(d_cpy) != 0)
    || (dequeue__length(d_no_cpy) != 0)
    || (*retrieved_cpy != value1_backup)
    || (*retrieved_no_cpy != value1)){
        free(retrieved_cpy);
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    free(retrieved_cpy);
    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__pop_back_a_lot()
{    
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value1_backup = value1;

    for (unsigned int i = 0; i < 500; i++){
        dequeue__push_back(d_cpy, &value1);
        dequeue__push_back(d_no_cpy, &value1);
    }
    value1 += 1;

    int *tmp_cpy;
    int *tmp_no_cpy;
    for (unsigned int i = 0; i < 500; i++){
        tmp_cpy = (int*) dequeue__pop_back(d_cpy);
        if ((tmp_cpy != NULL) && (*tmp_cpy != value1_backup)){
            if (tmp_cpy != NULL)
                free(tmp_cpy);
            dequeue__free(d_cpy);
            dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
        }
        free(tmp_cpy);

        tmp_no_cpy = dequeue__pop_back(d_no_cpy);
        if ((tmp_no_cpy != NULL) && (*tmp_no_cpy != value1)){
            dequeue__free(d_cpy);
            dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
        }
    }

    if (!dequeue__is_empty(d_cpy)
    || (!dequeue__is_empty(d_no_cpy))
    || (dequeue__length(d_cpy) != 0)
    || (dequeue__length(d_no_cpy) != 0)){
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__push_front_pop_back()
{
        printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    int value1_backup = value1;
    int value2_backup = value2;
    int value3_backup = value3;

    dequeue__push_front(d_cpy, &value1);
    dequeue__push_front(d_cpy, &value2);
    dequeue__push_front(d_cpy, &value3);
    dequeue__push_front(d_no_cpy, &value1);
    dequeue__push_front(d_no_cpy, &value2);
    dequeue__push_front(d_no_cpy, &value3);
    value1 += 1;
    value2 += 1;
    value3 += 1;

    int *retrieved_cpy_1 = (int*) dequeue__pop_back(d_cpy);
    int *retrieved_cpy_2 = (int*) dequeue__pop_back(d_cpy);
    int *retrieved_cpy_3 = (int*) dequeue__pop_back(d_cpy);
    int *retrieved_no_cpy_1 = (int*) dequeue__pop_back(d_no_cpy);
    int *retrieved_no_cpy_2 = (int*) dequeue__pop_back(d_no_cpy);
    int *retrieved_no_cpy_3 = (int*) dequeue__pop_back(d_no_cpy);

    if (!dequeue__is_empty(d_cpy)
    || (!dequeue__is_empty(d_no_cpy))
    || (dequeue__length(d_cpy) != 0)
    || (dequeue__length(d_no_cpy) != 0)
    || (*retrieved_cpy_1 != value1_backup)
    || (*retrieved_cpy_2 != value2_backup)
    || (*retrieved_cpy_3 != value3_backup)
    || (*retrieved_no_cpy_1 != value1)
    || (*retrieved_no_cpy_2 != value2)
    || (*retrieved_no_cpy_3 != value3)){
        free(retrieved_cpy_1);
        free(retrieved_cpy_2);
        free(retrieved_cpy_3);
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    free(retrieved_cpy_1);
    free(retrieved_cpy_2);
    free(retrieved_cpy_3);
    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__push_back_pop_front()
{
        printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    int value1_backup = value1;
    int value2_backup = value2;
    int value3_backup = value3;

    dequeue__push_back(d_cpy, &value1);
    dequeue__push_back(d_cpy, &value2);
    dequeue__push_back(d_cpy, &value3);
    dequeue__push_back(d_no_cpy, &value1);
    dequeue__push_back(d_no_cpy, &value2);
    dequeue__push_back(d_no_cpy, &value3);
    value1 += 1;
    value2 += 1;
    value3 += 1;

    int *retrieved_cpy_1 = (int*) dequeue__pop_front(d_cpy);
    int *retrieved_cpy_2 = (int*) dequeue__pop_front(d_cpy);
    int *retrieved_cpy_3 = (int*) dequeue__pop_front(d_cpy);
    int *retrieved_no_cpy_1 = (int*) dequeue__pop_front(d_no_cpy);
    int *retrieved_no_cpy_2 = (int*) dequeue__pop_front(d_no_cpy);
    int *retrieved_no_cpy_3 = (int*) dequeue__pop_front(d_no_cpy);

    if (!dequeue__is_empty(d_cpy)
    || (!dequeue__is_empty(d_no_cpy))
    || (dequeue__length(d_cpy) != 0)
    || (dequeue__length(d_no_cpy) != 0)
    || (*retrieved_cpy_1 != value1_backup)
    || (*retrieved_cpy_2 != value2_backup)
    || (*retrieved_cpy_3 != value3_backup)
    || (*retrieved_no_cpy_1 != value1)
    || (*retrieved_no_cpy_2 != value2)
    || (*retrieved_no_cpy_3 != value3)){
        free(retrieved_cpy_1);
        free(retrieved_cpy_2);
        free(retrieved_cpy_3);
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    free(retrieved_cpy_1);
    free(retrieved_cpy_2);
    free(retrieved_cpy_3);
    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__fulfill_front()
{
    printf("%s... ", __func__);
    //It only works with LLE_ARRAY_LENGTH 8 in dequeue.c
    //A new llelement shouldn't be created

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;

    dequeue__push_front(d_cpy, &value1);
    dequeue__push_front(d_cpy, &value2);
    dequeue__push_front(d_cpy, &value3);
    dequeue__push_front(d_cpy, &value3);

    dequeue__remove_back(d_cpy);
    dequeue__remove_back(d_cpy);
    dequeue__remove_back(d_cpy);
    dequeue__remove_back(d_cpy);
    dequeue__push_front(d_cpy, &value2);
    dequeue__push_back(d_cpy, &value3);

    if ((* (int*) dequeue__front(d_cpy) != value2)
    ||  (* (int*) dequeue__back(d_cpy) != value3)){
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}

int test_dequeue__debug()
{
    printf("%s... ", __func__);

    struct dequeue *d_cpy = dequeue__empty_copy_enabled(&operator_copy, &operator_delete, &operator_debug);
    struct dequeue *d_no_cpy = dequeue__empty_copy_disabled(&operator_debug);

    int value1 = 1;
    int value2 = 2;
    int value3 = 3;
    int value4 = 4;
    int value5 = 5;

    printf("Expected: { 1 2 3 } { 3 } { 3 4 5 } { 2 3 4 } Got: ");

    dequeue__push_front(d_cpy, &value1);
    dequeue__push_front(d_cpy, &value2);
    dequeue__push_front(d_cpy, &value3);
    dequeue__debug(d_cpy, 1);
    dequeue__remove_back(d_cpy);
    dequeue__remove_back(d_cpy);
    dequeue__debug(d_cpy, 1);
    dequeue__push_front(d_cpy, &value4);
    dequeue__push_front(d_cpy, &value5);
    dequeue__debug(d_cpy, 1);
    dequeue__remove_front(d_cpy);
    dequeue__push_back(d_cpy, &value2);
    dequeue__debug(d_cpy, 1);

    if ((* (int*) dequeue__front(d_cpy) != value4)
    ||  (* (int*) dequeue__back(d_cpy) != value2)){
        dequeue__free(d_cpy);
        dequeue__free(d_no_cpy);
        return !TEST_SUCCESS;
    }

    dequeue__free(d_cpy);
    dequeue__free(d_no_cpy);

    return TEST_SUCCESS;
}




int main()
{
    printf("----------- TEST DEQUEUE -----------\n");

    int nb_success = 0;
    int nb_tests = 0;

    print_test_result(test_dequeue__empty(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__push_front(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__push_front_a_lot(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__push_back(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__push_back_a_lot(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__push_front_and_back_a_lot(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__pop_front(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__pop_front_a_lot(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__pop_back(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__pop_back_a_lot(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__push_front_pop_back(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__push_back_pop_front(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__fulfill_front(), &nb_success, &nb_tests);
    print_test_result(test_dequeue__debug(), &nb_success, &nb_tests);

    print_test_summary(nb_success, nb_tests);

    return TEST_SUCCESS;
}
