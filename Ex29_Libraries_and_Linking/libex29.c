#include <stdio.h>
#include <ctype.h>
#include "debug.h"


int print_a_message(const char* msg)
{
    printf("A STRING: %s\n", msg);
    return 0;
}

int uppercase(const char* msg, int len)
{
    while((*msg != '\0') && len--){
        putchar(toupper(*msg));
        ++msg;
    }
    putchar('\n');
    return 0;
}

int lowercase(const char* msg, int len)
{
    while((*msg != '\0') && len--){
        putchar(tolower(*msg));
        ++msg;
    }
    putchar('\n');
    return 0;
}

int fail_on_purpose(const char* msg)
{
    return 1;
}
