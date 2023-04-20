#include <cstdio>

class Base{
public:
    Base() {
        metoda();
    }

    virtual void virtualnaMetoda() {
        printf("ja sam bazna implementacija!\n");
    }

    void metoda() {
        printf("Metoda kaze: ");
        virtualnaMetoda();
    }
};

class Derived: public Base{
public:
    Derived(): Base() {
        metoda();
    }
    virtual void virtualnaMetoda() {
        printf("ja sam izvedena implementacija!\n");
    }
};

int main(){
    Derived* pd=new Derived();
    pd->metoda();
}

/*
 * Dobijemo sljedeci ispis:
 * Metoda kaze: ja sam bazna implementacija!
 * Metoda kaze: ja sam izvedena implementacija!
 * Metoda kaze: ja sam izvedena implementacija!
 *
 *  To je zato je pri stvaranju novog objekta na gomili ide sljedeci proces:
 *  Ulazimo u konstruktor izvedene klase i iz nje se poziv konstruktor bazne klase
 *  to je zato jer prije stvaranja izvedenog objekta moraju se prvo stvoriti svi
 *  bazni objekti od kojih ona mozda nasljedljuje
 *  iz bazne klase poziva se funkcija metoda
 *  unutar funkcije metoda poziva se virtualna metoda,
 *  kako nas objekt jos uvijek nije tipa Derived jer inicijalizacija nije dovrsena
 *  poziva se virtualna metoda Base klase i dobivamo prvi ispis
 *  zavrsetkom konstruktora bazne klase nastavljamo s konstruktorom izvedene klase
 *  opet poziva funkciju metoda bazne klase no sada je konstrukcija
 *  objekta klase Derived dovrsena i pozvat ce se virtualna metoda klase Derived
 *  te dobivamo ocekviani ispis
 *  Isti ispis dobijemo kada pozivamo metodu nad inicijaliziranim objektom
 */

//konkretno preko asemblerskog koda:
//
//call Base::Base() [base object constructor]
//mov edx, OFFSET FLAT:vtable for Derived+16
//
//vidmo da se prvo unutar konstruktora klase Derived prvo poziva konstruktor klase Base
//a tek onda inicijalizira vtablica za klasu Derived, zato u pozivu virtualne metode
//iz konstruktora Base nije moguce pozvati virtualnu funkcijue klase Derived
//
//mov edx, OFFSET FLAT:vtable for Base+16
//mov rax, QWORD PTR [rbp-8]
//mov QWORD PTR [rax], rdx
//.loc 1 6 11
//mov rax, QWORD PTR [rbp-8]
//mov rdi, rax
//call Base::metoda()
//
//a prema sljedecem vidimo da ce se prvo inicijalizirati vtablica klase Base a tek onda
//ce se pozvati metoda metoda() unutar konstruktora te ce se time moci pozvati
//virtualna funkcija klase Base
//
//call Base::Base() [base object constructor]
//mov edx, OFFSET FLAT:vtable for Derived+16
//mov rax, QWORD PTR [rbp-8]
//mov QWORD PTR [rax], rdx
//.loc 1 22 11
//mov rax, QWORD PTR [rbp-8]
//mov rdi, rax
//call Base::metoda()
//
//nakon sto smo zavrsili s kontruktorom Base klase vidimo da napokon inicijaliziramo
//vtablicu klase Derived te ce se od ovoga trenutka nadalje ispravni izvoditi kod
//(tj na onaj nacin kako smo to ocekivali)