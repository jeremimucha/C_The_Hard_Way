#include "minunit.h"
#include <lcthw/debug.h>
#include <lcthw/bstrlib.h>
#define LEN 7

char* c_string = "C String in Static Storage.";
char bad_string[LEN] = {'b', 'a', 'd', ' ', 's', 't', 'r'};

char* test_bfromcstr_good()
{
    bstring bs = bfromcstr(c_string);
    mu_assert(strcmp(c_string, bdata(bs)) == 0,
        "bstring data isn't equal to the original string.");
    mu_assert(bdestroy(bs) != BSTR_ERR, "BSTR_ERR raised on bdestroy");

    bdestroy(bs);
    return NULL;
}

char* test_blk2bstr()
{
    bstring bs = blk2bstr(bad_string, LEN);
    mu_assert(strncmp(bad_string, bdata(bs), LEN) == 0,
        "bstring data isn't equal to the original string.");
    mu_assert(blength(bs) == LEN, "Length of bstring isn't equal to the"
        " original strings length.");

    bdestroy(bs);
    return NULL;
}

char* test_biseq()
{
    bstring bs1 = bfromcstr(c_string);
    bstring bs2 = bfromcstr(c_string);
    mu_assert(biseq(bs1, bs2) == 1,
        "biseq returned different result than strcmp.");
    
    bdestroy(bs1);
    bdestroy(bs2);
    return NULL;
}

char* test_copy()
{
    bstring bs1 = bfromcstr(c_string);
    bstring bs2 = bstrcpy(bs1);
    mu_assert(biseq(bs1, bs2) == 1, "String changed after bstrcpy.");

    bdestroy(bs1);
    bdestroy(bs2);
    return NULL;
}

char* test_binstr()
{
    bstring bs1 = bfromcstr(c_string);
    bstring bs2 = bfromcstr("Static");
    mu_assert(binstr(bs1, 0, bs2) != BSTR_ERR,
        "binstr failed to find a string. Should have succeded.");

    return NULL;
}


char* test_bassigncstr()
{
    char auto_cstr[] = "Automatic storage C String.";
    bstring bs = bfromcstr(c_string);
    bassigncstr(bs, auto_cstr);
    mu_assert(strcmp(auto_cstr, bdata(bs)) == 0,
        "bstring isn't equal to the assigned cstr.");

    return NULL;
}

char*  all_tests()
{
    mu_suite_start();

    mu_run_test(test_bfromcstr_good);
    mu_run_test(test_blk2bstr);
    mu_run_test(test_biseq);
    mu_run_test(test_copy);
    mu_run_test(test_binstr);
    mu_run_test(test_bassigncstr);

    return NULL;
}

RUN_TESTS(all_tests);
