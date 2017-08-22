#include <lcthw/bstrlib.h>
#include <lcthw/hashmap.h>
#include <lcthw/hashmap_algos.h>
#include <lcthw/darray.h>
#include "minunit.h"
#include <lcthw/debug.h>


struct tagbstring test1 = bsStatic("test data 1");
struct tagbstring test2 = bsStatic("test data 2");
struct tagbstring test3 = bsStatic("xest data 3");


char* test_fnv1a()
{
    uint32_t hash = Hashmap_fnv1a_hash(&test1);
    mu_assert(hash != 0, "Bad hash.");

    hash = Hashmap_fnv1a_hash(&test2);
    mu_assert(hash != 0, "Bad hash.");

    hash = Hashmap_fnv1a_hash(&test3);
    mu_assert(hash != 0, "Bad hash");

    return NULL;
}

char* test_adler32()
{
    uint32_t hash = Hashmap_adler32_hash(&test1);
    mu_assert(hash != 0, "Bad hash");

    hash = Hashmap_adler32_hash(&test2);
    mu_assert(hash != 0, "Bad hash");

    hash = Hashmap_adler32_hash(&test3);
    mu_assert(hash != 0, "Bad hash");

    return NULL;    
}

char* test_djb()
{
    uint32_t hash = Hashmap_djb_hash(&test1);
    mu_assert(hash != 0, "Bad hash");

    hash = Hashmap_djb_hash(&test2);
    mu_assert(hash != 0, "Bad hash");

    hash = Hashmap_djb_hash(&test3);
    mu_assert(hash != 0, "Bad hash");

    return NULL;
}

// #define BUCKETS 100
// #define BUFFER_LEN 20
// #define NUM_KEYS BUCKETS * 1000
// enum {ALGO_FNV1A, ALGO_ADLER32, ALGO_DJB};

// int get_keys(DArray* keys, int num_keys)
// {
//     int i = 0;
//     FILE* urand = fopen
// }

char* all_tests()
{
    mu_suite_start();

    mu_run_test(test_fnv1a);
    mu_run_test(test_adler32);
    mu_run_test(test_djb);

    return NULL;
}

RUN_TESTS(all_tests);
