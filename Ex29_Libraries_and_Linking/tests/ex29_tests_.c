#include <stdio.h>
#include <dlfcn.h>
#include "../src/debug.h"


typedef int (*lib_function)(const char* data);

int main(int argc, char* argv[])
{
    int rc = 0;
    // check(argc == 4, "USAGE: ex29 libex29.so function data");

    char* lib_file = "../build/libex29.so";
    char* functions[] = {"print_a_message","lowercase", "uppercase", "fail_on_purpose", NULL};
    char* data = "TEST Input.";
    char** func_to_run;


    void* lib = dlopen(lib_file, RTLD_NOW);
    check(lib != NULL, "Failed to open the library %s: %s", lib_file, dlerror());

    lib_function func = 0;
    for(func_to_run = functions; *func_to_run != NULL; ++func_to_run){

        func = dlsym(lib, *func_to_run);
        check(func != NULL, "Did not find %s function in the library %s: %s", *func_to_run,
                lib_file, dlerror());

        rc = func(data);
        check(rc == 0, "Function %s return %d for data: %s", *func_to_run,
                rc, data);
    }

    rc = dlclose(lib);
    check(rc == 0, "Failed to close %s", lib_file);

    return 0;

error:
    return 1;
}
