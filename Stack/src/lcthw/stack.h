#ifndef _STACK_H_
#define _STACK_H_

#include <lcthw/list.h>
#include "debug.h"

typedef List Stack;

static inline
Stack* Stack_create()
{
    return (Stack*)List_create();
}

static inline
void Stack_destroy(Stack* stack)
{
    List_destroy((List*)stack);
}

static inline
void Stack_push(Stack* stack, void* value)
{
    List_push((List*)stack, value);
}

static inline
void* Stack_pop(Stack* stack)
{
    return List_pop((List*)stack);
}

#define Stack_count(A) List_count(A)
#define Stack_peek(A) List_last(A)
#define STACK_FOREACH(S, C) LIST_FOREACH(S, last, prev, C)

#endif // _STACK_H_
