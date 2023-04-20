#include<stdlib.h>

struct TigerVtable{
    char const* (*name)(void* this);
    char const* (*greet)();
    char const* (*menu)();
};

struct Tiger{
    const struct TigerVtable* vtable_;
    char const* name_;
};

char const* TigerName(void* this);
char const* TigerGreet();
char const* TigerMenu();

const struct TigerVtable TigerVtable = {TigerName, TigerGreet, TigerMenu};

char const* TigerName(void* this){
    struct Tiger* t_ptr = (struct Tiger*) this;
    return t_ptr->name_;
}

char const* TigerGreet(){
    return "Rawr!";
}

char const* TigerMenu(){
    return "Lots of meat!";
}

int sizeofobject(){
    return sizeof(struct Tiger);
}

void construct(struct Tiger* memory, char const* name){
    struct Tiger* t_ptr = (struct Tiger*) memory;
    t_ptr->name_ = name;
    t_ptr->vtable_ = &TigerVtable;
}

struct Tiger* create(char const* name){
    struct Tiger* memory = (struct Tiger*) malloc(sizeof(struct Tiger));
    construct(memory, name);
    return (struct Tiger*) memory;
}