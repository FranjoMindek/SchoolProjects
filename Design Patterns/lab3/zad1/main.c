#include "myfactory.h"

#include <stdio.h>
#include <stdlib.h>

typedef struct Vtable{
    char const* (*name)(void* this);
    char const* (*greet)();
    char const* (*menu)();
} vtable;

typedef struct Animal{
  const vtable* vtable_;
} Animal;

// parrots and tigers defined in respective dynamic libraries

// animalPrintGreeting and animalPrintMenu similar as in lab 1
void AnimalPrintGreeting(Animal* animal);
void AnimalPrintMenu(Animal* animal);

int main(int argc, char *argv[]){
  // for (int i=0; i<argc; ++i){
  //   struct Animal* p=(struct Animal*)myfactory(argv[i], "Modrobradi");
  //   if (!p){
  //     printf("Creation of plug-in object %s failed.\n", argv[i]);
  //     continue;
  //   }

  //   // animalPrintGreeting(p);
  //   // animalPrintMenu(p);
  //   free(p); 
  // }

  Animal* papiga = (Animal*) MyFactoryHeap("./parrot.so", "Papuganda");
  Animal* tigar = (Animal*) MyFactoryHeap("./tiger.so", "Tigricko");
  char test[MyFactorySize("./tiger.so")];
  // printf("%d\n", MyFactorySize("./tiger.so"));
  MyFactoryStack("./tiger.so", "Tigstack", (void*) test);
  Animal* stack = (Animal*)test;
  AnimalPrintGreeting(papiga);
  AnimalPrintMenu(papiga);
  AnimalPrintGreeting(tigar);
  AnimalPrintMenu(tigar);
  AnimalPrintGreeting(stack);
  AnimalPrintMenu(stack);
  free(papiga);
  free(tigar);

  return 0;
}

void AnimalPrintGreeting(Animal* animal) {
  printf("%s says %s\n", animal->vtable_->name(animal), animal->vtable_->greet());
}

void AnimalPrintMenu(Animal* animal) {
  printf("%s eats %s\n", animal->vtable_->name(animal), animal->vtable_->menu());
}

