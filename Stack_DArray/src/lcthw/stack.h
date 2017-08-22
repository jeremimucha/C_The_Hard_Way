#ifndef _STACK_H_
#define _STACK_H_

#include <lcthw/darray.h>
#include "debug.h"

#define INIT_MAX 10
typedef DArray Stack;

typedef struct darray_item
{
    void* value;
} DArray_item;

static inline
Stack* Stack_create()
{
    return (Stack*)DArray_create(sizeof(void*), INIT_MAX);
}

static inline
void Stack_destroy(Stack* stack)
{
    DArray_clear_destroy((DArray*)stack);
}

static inline
void Stack_push(Stack* stack, void* value)
{
    DArray_push((DArray*)stack, value);
}

static inline
void* Stack_pop(Stack* stack)
{
    return DArray_pop((DArray*)stack);
}

#define Stack_count(A) DArray_count(A)
#define Stack_peek(A) DArray_last(A)
#define STACK_FOREACH(S, C) int _bla = 0;\
DArray_item _ccc = {.value = NULL};\
DArray_item* C = &_ccc;\
for(_bla = 0, C->value = S->contents[0];\
_bla < S->end;\
++_bla, C->value = S->contents[_bla])

#endif // _STACK_H_

