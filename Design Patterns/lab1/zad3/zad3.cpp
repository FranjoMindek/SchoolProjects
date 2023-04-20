#include <cstdio>

class CoolClass{
public:
    virtual void set(int x){x_=x;};
    virtual int get() {return x_;};
private:
    int x_;
};
class PlainOldClass{
public:
    void set(int x){x_=x;};
    int get(){return x_;};
private:
    int x_;
};

class DummyTest{
public:
    virtual void doNothing(){};
};

int main(){

    printf("CoolClass sizeof = %d\nPlainOldClass sizeof = %d\n", sizeof(CoolClass), sizeof(PlainOldClass));
    printf("DummyTest sizeof = %d\n", sizeof(DummyTest));

    // kako vidimo da je vtable pointer velik 8 btyes mozemo zakljuciti sljedecu strukturu klasa
    //
    // CoolClass
    // | 8 bytes vtable pinter | 4 bytes padding | 4 bytes int |
    // to je zato jer compiler pokusava velicinu klase zaokruziti na visekratnik najvece varijable po memoriji, tj. 8 bita
    //
    // PlainOldClass
    // | 4 bytes int |
    //
}