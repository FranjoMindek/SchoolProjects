#include <memory>
#include <iostream>

class Printer{
public: 
    Printer(){}
    ~Printer(){}
    void print(){std::cout << "Bok!" << std::endl;}
};

void NoDeleteFunction(){
    std::unique_ptr<Printer> ptr (new Printer());
    ptr->print();
    // nema delete ptr
    // no objekt ce se svejedno obrisati
}

int main(){
    NoDeleteFunction();
    return 0;
}