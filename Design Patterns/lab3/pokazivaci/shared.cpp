#include <memory>
#include <iostream>

class Printer{
public: 
    Printer(){}
    ~Printer(){}
    void print(){std::cout << "Bok!" << std::endl;}
};

void NoDeleteFunction(std::shared_ptr<Printer> p){
    std::shared_ptr<Printer> p1 (new Printer());
    p = p1;
    p1->print();
}

int main(){
    std::weak_ptr<Printer> wp;
    {
        std::shared_ptr<Printer> p0;
        NoDeleteFunction(p0);
        wp = p0;
        p0->print();    
    }
    std::shared_ptr<Printer> p2 = wp.lock();
    if (p2)
        std::cout << "Jos postoji";
    else 
        std::cout << "Ipak ne postoji";
    std::cout << std::endl;

    return 0;
}