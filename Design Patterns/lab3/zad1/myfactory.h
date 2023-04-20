#include <dlfcn.h>

void* MyFactoryHeap(char const* libname, char const* ctorarg);
void MyFactoryStack(char const* libname, char const* ctorarg, void* stack_memory);
int MyFactorySize(char const* libname);