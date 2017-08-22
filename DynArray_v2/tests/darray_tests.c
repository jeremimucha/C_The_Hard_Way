#include "minunit.h"
#include <DynamicArray/darray.h>

static DArray array;
static Item val1 = 1;
static Item val2 = 2;


char* test_create()
{
    array = DArray_create(100);
    mu_assert(array.contents != NULL, "DArray_create failed.");
    mu_assert(array.end == 0, "end isn't at the right spot.");
    mu_assert(array.max == 100, "wrong max length on initial size.");

    return NULL;
}

char* test_destroy()
{
    DArray_destroy(&array);

    return NULL;
}

// char* test_new()
// {
//     val1 = DArray_new(array);
//     mu_assert(val1 != NULL, "failed on make a new element.");
//     val2 = DArray_new(array);
//     mu_assert(val2 != NULL, "failed on make a new element.");

//     return NULL;
// }

char* test_set()
{
    Item* v1 = malloc(sizeof(Item*));
    Item* v2 = malloc(sizeof(Item*));
    *v1 = val1;
    *v2 = val2;
    DArray_set(&array, 0, v1);
    DArray_set(&array, 1, v2);

    return NULL;
}

char* test_get()
{
    mu_assert(*DArray_get(&array, 0) == val1, "Wrong first value.");
    mu_assert(*DArray_get(&array, 1) == val2, "Wrong second value.");

    return NULL;
}

char* test_remove()
{
    Item* val_check = DArray_remove(&array, 0);
    mu_assert(val_check != NULL, "Should not get NULL.");
    mu_assert(*val_check == val1, "Should get the first value.");
    mu_assert(DArray_get(&array, 0) == NULL, "Should be gone.");

    val_check = DArray_remove(&array, 1);
    mu_assert(val_check != NULL, "Should not get Item{0}.");
    mu_assert(*val_check == val2, "Should get the first value.");
    mu_assert(DArray_get(&array, 1) == NULL, "Should be gone.");

    return NULL;
}

char* test_expand_contract()
{
    int old_max = array.max;
    DArray_expand(&array);
    mu_assert((unsigned int)array.max == old_max + array.expand_rate,
                "Wrong size after expand.");

    DArray_contract(&array);
    mu_assert((unsigned int)array.max == array.expand_rate + 1,
        "Should stay at the expand_rate at least.");

    DArray_contract(&array);
    mu_assert((unsigned int)array.max == array.expand_rate + 1,
        "Should stay at the expand_rate at least.");

    return NULL;
}

char* test_push_pop()
{
    int i = 0;
    Item val;
    Item* val_check;
    for(i = 0; i < 1000; ++i){
        val = i * 333;
        DArray_push_(&array, val);
    }

    mu_assert(array.max == 1201, "Wrong max size.");

    for(i = 999; i >= 0; --i){
        val_check = DArray_pop(&array);
        mu_assert(*val_check == i*333, "Wrong value.");
    }

    return NULL;
}

char* all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_set);
    mu_run_test(test_get);
    mu_run_test(test_remove);
    mu_run_test(test_expand_contract);
    mu_run_test(test_push_pop);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
