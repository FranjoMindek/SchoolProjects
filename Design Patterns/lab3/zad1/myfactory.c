#include <dlfcn.h>
#include "myfactory.h"

void* MyFactoryHeap(char const* libname, char const* ctorarg){
    void* handle;
    void* (*c_ptr)(char const*);
    handle = dlopen(libname, RTLD_LOCAL | RTLD_LAZY);
    c_ptr = (void* (*)(char const*))dlsym(handle, "create");
    return (*c_ptr)(ctorarg);
}

void MyFactoryStack(char const* libname, char const* ctorarg, void* stack_memory){
    void* handle;
    void (*c_ptr)(void*, char const*);
    handle = dlopen(libname, RTLD_LOCAL | RTLD_LAZY);
    c_ptr = (void (*)(void*, char const*))dlsym(handle, "construct");
    (*c_ptr)((void*) stack_memory, ctorarg);
}

int MyFactorySize(char const* libname){
    void* handle;
    int (*soo_ptr)();
    handle = dlopen(libname, RTLD_LOCAL | RTLD_LAZY);
    soo_ptr = (int (*)())dlsym(handle, "sizeofobject");
    return(*soo_ptr)();
}