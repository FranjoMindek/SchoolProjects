#include <stdlib.h>
#include <stdio.h>

typedef char const* (*PTRFUN)();

typedef struct Animal{
    PTRFUN *vtable;
    const char *name;
}Animal;

//trebaju inicijalizirati odgovarajuci objekt
void constructDog(Animal *memory, const char* name);
void constructCat(Animal *memory, const char* name);
//alociraju memoriju i pozivaj construct funkcije
Animal* createDog(const char *name);
Animal* createCat(const char *name);
void createDogs(const char **names, Animal** dogs, int size);
//funkcije glasanja
const char* dogGreet(void);
const char* dogMenu(void);
const char* catGreet(void);
const char* catMenu(void);
//valjda polimofrni dio ovisno o zivotinji imat ce drukcije glasanje i meni
void animalPrintGreeting(Animal *animal);
void animalPrintMenu(Animal *animal);
void testAnimals(void);
//vtables
PTRFUN catTable[] = {catGreet, catMenu};
PTRFUN dogTable[] = {dogGreet, dogMenu};

int main(){

    testAnimals(); //također i primjer zauzimanja memorije na heapu

    Animal stog; //pas koji je stvoren na stogu, memorija je alocirana na stogu
    constructDog(&stog, "Stogovko"); //i sada mozemo pozvati konstruktor za tu memoriju
    printf("Ime zivotinje stog je %s\n", stog.name);


    const char *names[] = {"Prvi", "Drugi", "Treci", "Cetvrti"};
    Animal* dogs[4];
    createDogs(names, dogs, 4);
    for(int i = 0; i<4; i++){
        animalPrintGreeting(dogs[i]);
    }
    //metode bi bile funkcije koje primaju pointer na Animal tj print animalPrintGreeting i animalPrintMenu
    //virtualne metode bi bile funckije sadrzane u virtualnim tablicama tj unutar catTable i dogTable
    //konstruktori su constructDog i constructCat tj dio gdje se radi inicijalizacija strukture u nasem slucaju
    //virtualna tablice su globalni arrayji pointera na funkcije koje vracaju tip char const* tj catTable i dogTable
    return 0;
}

Animal* createDog(const char *name){
    Animal *memory = (Animal*) malloc(sizeof(Animal));
    constructDog(memory, name);
    return memory;
}

void createDogs(const char **names, Animal** dogs, int size){
    for(int i = 0; i<size; i++){
        dogs[i] = createDog(names[i]);
    }
    return;
}

void constructDog(Animal *memory, const char *name){
    memory->name = name;
    memory->vtable = dogTable;
}

Animal* createCat(const char *name){
    Animal *memory = (Animal*) malloc(sizeof(Animal));
    constructCat(memory, name);
    return memory;
}

void constructCat(Animal *memory, const char *name){
    memory->name = name;
    memory->vtable = catTable;
}

char const* dogGreet(void){
    return "vau!";
}
char const* dogMenu(void){
    return "kuhanu govedinu";
}
char const* catGreet(void){
    return "mijau!";
}
char const* catMenu(void){
    return "konzerviranu tunjevinu";
}

void animalPrintGreeting(Animal *animal){
    printf("%s pozdravlja: %s\n", animal->name, animal->vtable[0]());
}

void animalPrintMenu(Animal *animal){
    printf("%s voli %s\n", animal->name, animal->vtable[1]());
}

void testAnimals(void){
    struct Animal* p1=createDog("Hamlet");
    struct Animal* p2=createCat("Ofelija");
    struct Animal* p3=createDog("Polonije");

    animalPrintGreeting(p1);
    animalPrintGreeting(p2);
    animalPrintGreeting(p3);

    animalPrintMenu(p1);
    animalPrintMenu(p2);
    animalPrintMenu(p3);

    free(p1); free(p2); free(p3);
}
//
// Created by mindek on 10. 03. 2022..
//

