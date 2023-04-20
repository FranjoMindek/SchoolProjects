class Base{
public:
    //if in doubt, google "pure virtual"
    virtual void set(int x)=0;
    virtual int get()=0;
};

class CoolClass: public Base{
public:
    virtual void set(int x){x_=x;};
    virtual int get(){return x_;};
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
int main(){
    PlainOldClass poc;
    Base* pb=new CoolClass;
    poc.set(42);
    pb->set(42);
}
/*  analiza strojnog koda preko https://godbolt.org/

    1. i 2.
    Alociranje memorije za poc je samo pomak na pokazivacu stoga
    dok je alociranje memorije za pb napravljeno pomocu potprograma new
    koja se onda ostvaruje na gomili

    mov edi, 16
    call operator new(unsigned long)

    konkretno u strojnom kodu vidimo da se memorija na gomili alocira pomocu potprograma new

    3. Poc nema poziv konstruktora, nismo zadali eksplicitni konstruktor, a niti ima
    virtualne funkcije da kompajler sam napravi implicitni konstruktor

    4. Poziva se potprogram konstruktor klase CoolClass
    to se desava u sljedecem strojnom kod:

    mov rbx, rax
    mov rdi, rbx
    call CoolClass::CoolClass() [complete object constructor]
    mov QWORD PTR [rbp-24], rbx

    dalje je dan strojni kod konstruktora:

    .loc 1 8 7
    .cfi_startproc
    push rbp
    .cfi_def_cfa_offset 16
    .cfi_offset 6, -16
    mov rbp, rsp
    .cfi_def_cfa_register 6
    sub rsp, 16
    mov QWORD PTR [rbp-8], rdi
    .loc 1 8 7
    mov rax, QWORD PTR [rbp-8]
    mov rdi, rax
    call Base::Base() [base object constructor]
    mov edx, OFFSET FLAT:vtable for CoolClass+16
    mov rax, QWORD PTR [rbp-8]
    mov QWORD PTR [rax], rdx
    nop
    leave
    .cfi_def_cfa 7, 8
    ret

    unutar konstruktora vidimo da se prvih 8 bajtova objekta ostavlja za pokazivac na vtablicu
    zatim se poziva konstruktor Base klase i tek nakon sto je on dovrsen
    postavlja se pokzivac vtablicu te od sada nadalje izvrsavao bi
    se dio konstruktora koji bismo mi sami napisali kada bi ga zadali

    5. Pozic CoolClass ici ce preko virtualne tablice dok ce poziv
    PlainOldClass biti preko obicne tablice metoda (jer svi objekti jedne klase dijele jednu tablicu)
    Kako su virtualne funkcije dinamicki polimorfizam i njihov poziv se odredjuje tek na runtine
    ne mogu biti inline jer komapjler ne zna tip objekta za vrijeme kompajliranja

   6. Dan je sljedeci kod za definicju vtablice CoolClass klase:
    vtable for CoolClass:
      .quad 0
      .quad typeinfo for CoolClass
      .quad CoolClass::set(int)
      .quad CoolClass::get()

    te incijalizaciju:
      .weak vtable for CoolClass
      .section .rodata.vtable for CoolClass,"aG",@progbits,vtable for CoolClass,comdat
      .align 8
      .type vtable for CoolClass, @object
      .size vtable for CoolClass, 32
 */