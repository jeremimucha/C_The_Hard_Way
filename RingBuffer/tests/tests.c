#include "minunit.h"
#include <lcthw/ringbuffer.h>
#include <string.h>

#define RB_LEN 12

char* data1 = "Test_Data_1";
char* data2a = "2_";
char* data2b = "Test_Data";
char* data_fail =  "Test_Data_Longer_Than_RungBuffer";

int len_data1 = 12;
int len_data2a = 3;
int len_data2b = 10;
int len_data_fail = 33;


static RingBuffer* rb = NULL;


static inline void
Debug_RingBufferStats(RingBuffer* buffer)
{
    fprintf(stderr, "\nRingBuffer data: %s\n", rb->buffer);
    fprintf(stderr, "\nDebug: RingBuffer:\n\tlength = %d\n\tstart = %d\n\t end = %d\n",
        rb->length, rb->start, rb->end);
    fprintf(stderr, "\tavailable_data = %d\n\t"
        "available_space = %d\n\t", RingBuffer_available_data(rb),
        RingBuffer_available_space(rb));
}

char* test_create()
{
    rb = RingBuffer_create(RB_LEN);
    mu_assert(rb != NULL, "Failed to create RingBuffer.");

    return NULL;
}

char* test_destroy()
{
    mu_assert(rb != NULL, "RingBuffer == NULL at test_destroy entry.");
    RingBuffer_destroy(rb);

    return NULL;
}

char* test_read_write()
{
    int rc = 0;
    char buf[RB_LEN+1];

    rc = RingBuffer_write(rb, data1, len_data1);
    mu_assert(rc == len_data1, "Failed to write data1 to RingBuffer.");
    
    Debug_RingBufferStats(rb);
    
    rc = RingBuffer_read(rb, buf, 5);
    mu_assert(rc == 5, "Failed to read data from RingBuffer.");
    rc = strncmp(buf, "Test_", 5);

    buf[5] = '\0';
    mu_assert(rc == 0, "String read from buffer different than expected.");
    fprintf(stderr, "\nGot: %s, Expected: %s\n", buf, "Test_");

    rc = RingBuffer_read(rb, buf, 7);
    mu_assert(rc == 7,"Failed to read 2nd part of data1 from RingBuffer.");
    rc = strncmp(buf, "Data_1", 7);
    mu_assert(rc == 0, "String read from buffer different than expected.");
    fprintf(stderr, "Got: %s, Expected: %s\n", buf, "Data_1");

    rc = RingBuffer_write(rb, data2a, len_data2a-1);
    mu_assert(rc == len_data2a-1, "Fail on write data2a.");

    rc = RingBuffer_write(rb, data2b, len_data2b);
    mu_assert(rc == len_data2b, "Fail on write data2b.");

    Debug_RingBufferStats(rb);

    rc = RingBuffer_read(rb, buf, RB_LEN);
    mu_assert(rc == RB_LEN, "Data2 Read from RingBuffer failed.");
    fprintf(stderr, "\nGot: %s, Expected: %s\n", buf, "2_Test_Data");

    Debug_RingBufferStats(rb);

    return NULL;
}

char*  all_tests()
{
    mu_suite_start();

    mu_run_test(test_create);
    mu_run_test(test_read_write);
    mu_run_test(test_destroy);

    return NULL;
}

RUN_TESTS(all_tests);
