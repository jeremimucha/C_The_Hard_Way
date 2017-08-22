#include <stdio.h>
#include "../debug.h"
#include <windows.h>


typedef int(*lib_function)(const char* data);
typedef int (__cdecl *MYPROC)(LPWSTR);

int main(int argc, char* argv[])
{

    int rc = 0;
    check(argc == 4, "USAGE: ex29 libex29.dll function data");

    char* lib_file = argv[1];
    char* func_to_run = argv[2];
    char* data = argv[3];
    HINSTANCE hinstLib;

    hinstLib = LoadLibrary(TEXT(lib_file));
    check(hinstLib != NULL, "Failed to open the library %s", lib_file);

    lib_function func = (lib_function)GetProcAddress(hinstLib, func_to_run);
    check(func != NULL, "Did not find %s function in the library %s",
          func_to_run, lib_file)

//    lib_function func = dlsym(lib, func_to_run);
//    check(func != NULL, "Did not find %s function in the library %s",
//          func_to_run, lib_file);

    rc = func(data);
    check(rc == 0, "Function %s return %d for data: %s", func_to_run, rc, data);
    rc = FreeLibrary(hinstLib);
    check(rc != 0, "Failed to close %s", lib_file);

    return 0;


error:
    return 1;
}
