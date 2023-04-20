#include <iostream>
#include <string>
#include <fstream>
#include <list>
#include <vector>
#include <chrono>
#include <ctime>
#include <thread>

class Izvor{
public:
    virtual long dohvatiBroj() const =0;
};

class Akcija{
public:
    virtual void azuriraj() =0;
};

class SlijedBrojeva{
private:
    Izvor* izvor;  
    std::list<Akcija*> akcije;

    void obavijest();
public:
    std::vector<long> brojevi;

    SlijedBrojeva(Izvor* izv);
    ~SlijedBrojeva();

    void noviIzvor(Izvor* izv);
    void kreni();
    void prijavi(Akcija* akcija);
    void odjavi(Akcija* akcija);
};

class TipkovnickiIzvor : public Izvor{
    long dohvatiBroj() const override{
        long broj;
        std::cin >> broj;
        if(!std::cin){
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(),'\n');
            return -1;
        }
        return broj;
    }
};

class DatotecniIzvor : public Izvor{
private:
    std::ifstream* datoteka;
public:
    DatotecniIzvor(const char * put){
        datoteka = new std::ifstream(put);
    }
    ~DatotecniIzvor(){
        delete datoteka;
    }
    long dohvatiBroj() const override{
        long broj;
        *datoteka >> broj;
        if(broj == -1)
            datoteka->close();
        return broj;
    }
};

class IspisiSumu : public Akcija{
private:
    SlijedBrojeva& slijedBrojeva;
public:
    IspisiSumu(SlijedBrojeva& slijed) : slijedBrojeva(slijed){
        this->slijedBrojeva.prijavi(this);
    }
    void azuriraj() override{
        long sum = 0;
        for(auto& broj : slijedBrojeva.brojevi){
            sum += broj;
        }
        std::cout << "Suma brojeva je " << sum << std::endl;
    }
    void prestaniSlusati(){
        slijedBrojeva.odjavi(this);
    }
};

class IspisiProsjek : public Akcija{
private:
    SlijedBrojeva& slijedBrojeva;
public:
    IspisiProsjek(SlijedBrojeva& slijed) : slijedBrojeva(slijed){
        this->slijedBrojeva.prijavi(this);
    }
    void azuriraj() override{
        long sum = 0;
        for(auto& broj : slijedBrojeva.brojevi){
            sum += broj;
        }
        std::cout << "Prosjek brojeva je " << 1.0*sum/slijedBrojeva.brojevi.size() << std::endl;
    }
    void prestaniSlusati(){
        slijedBrojeva.odjavi(this);
    }
};

class IspisiMedijan : public Akcija{
private:
    SlijedBrojeva& slijedBrojeva;
public:
    IspisiMedijan(SlijedBrojeva& slijed) : slijedBrojeva(slijed){
        this->slijedBrojeva.prijavi(this);
    }
    void azuriraj() override{
        float medijan = 0;
        long size = slijedBrojeva.brojevi.size();
        if(size%2 == 0){
            medijan = (float)(slijedBrojeva.brojevi.at(size/2) + (float)slijedBrojeva.brojevi.at(size/2 -1))/2;
        }else{
            medijan = slijedBrojeva.brojevi.at((size-1)/2);
        }
        std::cout << "Medijan brojeva je " << medijan << std::endl;
    }
    void prestaniSlusati(){
        slijedBrojeva.odjavi(this);
    }
};

class ZapisiBrojeve : public Akcija{
private:
    SlijedBrojeva& slijedBrojeva;
public:
    ZapisiBrojeve(SlijedBrojeva& slijed) : slijedBrojeva(slijed){
        this->slijedBrojeva.prijavi(this);
        std::ofstream clear("brojevi.txt", std::ofstream::trunc);
        clear.close();
    }
    ~ZapisiBrojeve(){}
    void azuriraj() override{
        std::ofstream datoteka("brojevi.txt", std::ofstream::app);
        time_t ttime = time(0);
        datoteka << std::ctime(&ttime);
        for(auto broj : slijedBrojeva.brojevi){
            datoteka << broj << " ";
        }
        datoteka << "\n\n";
        datoteka.close();
    }
    void prestaniSlusati(){
        slijedBrojeva.odjavi(this);
    }
};

SlijedBrojeva::SlijedBrojeva(Izvor* izv) : izvor(izv){}
SlijedBrojeva::~SlijedBrojeva(){ 
    delete izvor;
}
void SlijedBrojeva::noviIzvor(Izvor* izv){
    delete izvor;
    izvor = izv;
}
void SlijedBrojeva::kreni(){
    while(1){
        long broj = izvor->dohvatiBroj();
        if (broj == -1)
            break;
        brojevi.push_back(broj);
        std::cout << "=======================" << std::endl;
        obavijest();
        std::cout << "=======================\n" << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}
void SlijedBrojeva::obavijest(){
    for(auto akcija : akcije){
        akcija->azuriraj();
    }
}
void SlijedBrojeva::prijavi(Akcija* akcija){
    akcije.push_back(akcija);
}
void SlijedBrojeva::odjavi(Akcija* akcija){
    akcije.remove(akcija);
}


int main(){
    SlijedBrojeva* slijedBrojeva = new SlijedBrojeva(new TipkovnickiIzvor());
    IspisiSumu* suma = new IspisiSumu(*slijedBrojeva);
    IspisiMedijan* medijan = new IspisiMedijan(*slijedBrojeva);
    IspisiProsjek* prosjek = new IspisiProsjek(*slijedBrojeva);
    ZapisiBrojeve* zapisi = new ZapisiBrojeve(*slijedBrojeva);
    slijedBrojeva->kreni();
    suma->prestaniSlusati();
    slijedBrojeva->kreni();
    slijedBrojeva->noviIzvor(new DatotecniIzvor("izvor.txt"));
    slijedBrojeva->prijavi(suma);
    slijedBrojeva->kreni();
    
    delete slijedBrojeva;
    delete suma;
    delete medijan;
    delete prosjek;
    delete zapisi;

    return 0;
}