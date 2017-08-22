#include <time.h>
#include <DynamicArray/darray.h>
#include "debug.h"

// clock_t start, end;
// double cpu_time_used;

// start = clock();
// … /* Do the work. */
// end = clock();
// cpu_time_used = ((double) (end - start)) / CLOCKS_PER_SEC;



#define timeit(N, R, F, ...)\
{\
clock_t s__, e__;\
int i__ = 0;\
s__ = clock();\
for(i__ = 0; i__ < N; ++i__){\
(*F)(__VA_ARGS__);\
}\
e__ = clock();\
R = ((double)(e__ - s__)) / CLOCKS_PER_SEC;}


int main(void)
{
    static double time_used;
    DArray* array = DArray_create(sizeof(double), 100000);
    void* newelem = DArray_new(array);

    timeit(100000, time_used, DArray_push, array, newelem);

    printf("%s calls to DArray_push took: %fs\n", 100000, time_used);
}
