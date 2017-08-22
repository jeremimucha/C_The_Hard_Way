#ifndef _QUEUE_H_
#define _QUEUE_H_

#include <lcthw/list.h>

typedef List Queue;

static inline
Queue* Queue_create()
{
    return (Queue*)List_create();
}

static inline
void Queue_destroy(Queue* queue)
{
    List_destroy((List*)queue);
}

static inline
void Queue_send(Queue* queue, void* value)
{
    List_push((List*)queue, value);
}

static inline
void* Queue_recv(Queue* queue)
{
    return List_shift((List*)queue);
}

#define Queue_peek(A) List_first(A)
#define Queue_count(A) List_count(A)
#define QUEUE_FOREACH(Q, C) LIST_FOREACH(Q, first, next, C)

#endif  // _QUEUE_H_
