#include <iostream>

class B{
public:
  virtual int prva()=0;
  virtual int druga(int)=0;
};

class D: public B{
public:
  virtual int prva(){return 42;}
  virtual int druga(int x){return prva()+x;}
};

typedef int (*prvaPtr)();
typedef int (*drugaPtr)(B*, int);

int main(){

    D *d = new D();


    unsigned long * vtable2 = (unsigned long*)((unsigned long*)d)[0];

    //  castamo pointer na objekt u long jer zelim dobiti brojcanu
    //  vrijednost zapisanu u prvih 8 bajtova objekta a upravo
    //  vrijednost tamo zapisana je adresa vtablice (vtable pointer)
    //  sa [0] uzmemo vrijednost zapisanu u prvih 8 bajta objekta
    //  tu adresu opet vratimo kao long pointer

    prvaPtr prva = (prvaPtr)(*(unsigned long*)(vtable2));
    drugaPtr druga = (drugaPtr)(*(unsigned long*)(vtable2 + 1));

    std::cout << prva() << std::endl << druga(d,14);

  return 0;
}