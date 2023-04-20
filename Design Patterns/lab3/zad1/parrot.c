#include<stdlib.h>

struct ParrotVtable{
    char const* (*name)(void* this);
    char const* (*greet)();
    char const* (*menu)();
};

struct Parrot{
    const struct ParrotVtable* vtable_;
    char const* name_;
};

char const* ParrotName(void* this);
char const* ParrotGreet();
char const* ParrotMenu();

const struct ParrotVtable ParrotVtable = {ParrotName, ParrotGreet, ParrotMenu};

char const* ParrotName(void* this){
    struct Parrot* p_ptr = (struct Parrot*) this;
    return p_ptr->name_;
}

char const* ParrotGreet(){
    return "Caw caw!";
}

char const* ParrotMenu(){
    return "Sunflower seeds!";
}

int sizeofobject(){
    return sizeof(struct Parrot);
}

void construct(void* memory, char const* name){
    struct Parrot* p_ptr = (struct Parrot*) memory;
    p_ptr->name_ = name;
    p_ptr->vtable_ = &ParrotVtable;
}

struct Parrot* create(char const* name){
    struct Parrot* memory = (struct Parrot*) malloc(sizeof(struct Parrot));
    construct(memory, name);
    return (struct Parrot*) memory;
}