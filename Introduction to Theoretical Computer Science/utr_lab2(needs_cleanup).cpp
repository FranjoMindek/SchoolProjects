#include <iostream>
#include <string>
#include <map>
#include <set>

using namespace std;

template <class T> void tokenize(string s, string del = " ",  set<T> &set = nullptr)
{
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        set.insert(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    set.insert(s.substr(start, end - start));
}

int redniBrojUStrukturi(string stanje, set<string> &stanja ){
    int i = 0;
    for(auto it = stanja.begin(); it != stanja.end(); it++){
        if(stanje == *it) return i;
        i++;
    }
    return -1; //error 
}

struct prijelazInfo
{
    mutable string trenutnoStanje;
    string ulaznaRijec;
    mutable string prijelaznoStanje;
    mutable bool visited = false;
    bool trenutniPrihvatljiv = false;
    bool prijelazniPrihvatljiv = false;
};

struct stanjePrihvatljivost
{
    mutable string stanje;
    mutable bool prihvatljiv = false;
};

struct vrijednostStanje
{
    int stanje = -1;
    int vrijednost = -1;
};

inline bool operator<(const prijelazInfo& l, const prijelazInfo& r)
{
  return tie(l.trenutnoStanje, l.ulaznaRijec, l.prijelaznoStanje) <
         tie(r.trenutnoStanje, r.ulaznaRijec, r.prijelaznoStanje);
}

inline bool operator<(const stanjePrihvatljivost& l, const stanjePrihvatljivost& r)
{
  return tie(l.stanje, l.prihvatljiv) <
         tie(r.stanje, r.prihvatljiv);
}


int main(){
    string citanjeUlaza;
    string pocetnoStanje;
    set<string> dostupnaStanja;
    set<string> prihvatljivaStanja;
    set<string> rijeci;
    set<prijelazInfo> prijelazi;
    set<stanjePrihvatljivost> dostupnaStanjaSPrihvatiljivosti;
    getline(cin, citanjeUlaza);
    getline(cin, citanjeUlaza);
    tokenize(citanjeUlaza, ",", rijeci);
    getline(cin, citanjeUlaza);
    tokenize(citanjeUlaza, ",", prihvatljivaStanja);
    getline(cin, pocetnoStanje);
    //ucitavanje stanja
    while(getline(cin,citanjeUlaza)){
        prijelazInfo temp;
        int stringFindZarez = citanjeUlaza.find(",");
        int stringFindStrelica = citanjeUlaza.find("->");
        temp.trenutnoStanje = citanjeUlaza.substr(0, stringFindZarez);
        temp.ulaznaRijec = citanjeUlaza.substr(stringFindZarez+1, stringFindStrelica-stringFindZarez-1);
        temp.prijelaznoStanje = citanjeUlaza.substr(stringFindStrelica+2);
        for(auto it = prihvatljivaStanja.begin(); it != prihvatljivaStanja.end(); it++){
            if(temp.trenutnoStanje == *it) temp.trenutniPrihvatljiv=1;
        }
        for(auto it = prihvatljivaStanja.begin(); it != prihvatljivaStanja.end(); it++){
            if(temp.prijelaznoStanje == *it) temp.prijelazniPrihvatljiv=1;
        }
        prijelazi.insert(temp);
    }
    //trazenje dostupnih stanja
    dostupnaStanja.insert(pocetnoStanje);
    {
        bool imaJos = true;
        while(imaJos){
            imaJos = false;
            for(auto it = prijelazi.begin(); it != prijelazi.end(); it++){
                if((!it->visited) && dostupnaStanja.find(it->trenutnoStanje)!=dostupnaStanja.end()){
                    imaJos = true;
                    it->visited = true;
                    dostupnaStanja.insert(it->prijelaznoStanje);
                }
            }
        }
    }
    //brisanje nedostupnih stanja
    {
        auto it = prijelazi.begin();
        while(it != prijelazi.end()){
            if(dostupnaStanja.find(it->trenutnoStanje)!=dostupnaStanja.end())
                it++;
            else
                prijelazi.erase(it++);

        }
    }
    //minimizacija priprema
    int brStanja = dostupnaStanja.size();
    int brRijeci = rijeci.size();
    bool tablicaMinimizacije[brStanja][brStanja];
    for(int i = 0; i<brStanja; i++)
        for(int j = 0; j<brStanja; j++)
            tablicaMinimizacije[i][j] = 0; //ako imamo stanja p1,..,p8 tada redci = p2,..,p8 stupcu = p1,..,p7 ili obrnuto
    
    vrijednostStanje matricaStanjePrijelaziVrijednosti[brStanja][brRijeci];
    for(auto it = prijelazi.begin(); it != prijelazi.end(); it++){
        if(it->prijelazniPrihvatljiv){
            matricaStanjePrijelaziVrijednosti[redniBrojUStrukturi(it->trenutnoStanje,dostupnaStanja)][redniBrojUStrukturi(it->ulaznaRijec, rijeci)].vrijednost = 1;
        }
        else{
            matricaStanjePrijelaziVrijednosti[redniBrojUStrukturi(it->trenutnoStanje,dostupnaStanja)][redniBrojUStrukturi(it->ulaznaRijec, rijeci)].vrijednost = 0;
        }
        matricaStanjePrijelaziVrijednosti[redniBrojUStrukturi(it->trenutnoStanje,dostupnaStanja)][redniBrojUStrukturi(it->ulaznaRijec, rijeci)].stanje = redniBrojUStrukturi(it->prijelaznoStanje,dostupnaStanja);
    }   
    
    for(auto it = dostupnaStanja.begin(); it != dostupnaStanja.end(); it++){
        stanjePrihvatljivost temp;
        temp.stanje = *it;
        for(auto it2 = prihvatljivaStanja.begin(); it2 != prihvatljivaStanja.end(); it2++){
            if(*it2 == *it) temp.prihvatljiv=1;
        }
        dostupnaStanjaSPrihvatiljivosti.insert(temp);
    }
    int i = 0;
    for(auto it = dostupnaStanjaSPrihvatiljivosti.begin(); it != dostupnaStanjaSPrihvatiljivosti.end(); it++){
        auto it2 = it;
        int j = i+1;
        if(it2 != dostupnaStanjaSPrihvatiljivosti.end()) it2++;
        for(; it2 != dostupnaStanjaSPrihvatiljivosti.end(); it2++){
            if (it->prihvatljiv != it2->prihvatljiv) tablicaMinimizacije[j][i] =1;
            j++;
        }
        i++;
    }
    //tablica minimizacije done
    bool change = 1;
    while(change){
        change = 0;
        for(int i = 0; i<brStanja; i++){
            for(int j = i+1; j<brStanja; j++){
                for(int k = 0; k<brRijeci; k++){
                    if(matricaStanjePrijelaziVrijednosti[i][k].vrijednost != matricaStanjePrijelaziVrijednosti[j][k].vrijednost && tablicaMinimizacije[j][i] != 1){
                        tablicaMinimizacije[j][i] = 1;
                        change = 1;
                    }
                }
                if(tablicaMinimizacije[j][i] == 0){
                    for(int k = 0; k<brRijeci; k++){
                        if(tablicaMinimizacije[matricaStanjePrijelaziVrijednosti[j][k].stanje][matricaStanjePrijelaziVrijednosti[i][k].stanje] == 1){
                            tablicaMinimizacije[j][i] = 1;
                            change = 1;
                        }       
                    }
                }
            }
        }      
    }
    //brisanje duplikata
    for(int i = 0; i<brStanja; i++){
        for(int j = i+1; j<brStanja; j++){
            if(tablicaMinimizacije[j][i] == 0) {
                auto it1 = dostupnaStanjaSPrihvatiljivosti.begin();
                for(int k = 0; k<i; k++) it1++;
                string pretvoriU = it1->stanje;
                bool prihvatljivost = it1->prihvatljiv;
                it1 = dostupnaStanjaSPrihvatiljivosti.begin();
                for(int k = 0; k<j; k++) it1++;
                string pretvoriIz = it1->stanje;
                for(auto it = prijelazi.begin(); it != prijelazi.end(); it++){
                    if(it->trenutnoStanje == pretvoriIz) it->trenutnoStanje = pretvoriU;
                    if(it->prijelaznoStanje == pretvoriIz) it->prijelaznoStanje = pretvoriU;
                }
                for(auto it = dostupnaStanjaSPrihvatiljivosti.begin(); it != dostupnaStanjaSPrihvatiljivosti.end(); it++){
                    if(it->stanje == pretvoriIz) {it->stanje = pretvoriU; it->prihvatljiv=prihvatljivost;}
                if(pocetnoStanje == pretvoriIz) pocetnoStanje = pretvoriU;
                }
            }
        }
    }    
    //sredjivanje seta
    {
        set<prijelazInfo> tempSet;
        for(auto it = prijelazi.begin(); it != prijelazi.end(); it++){
            prijelazInfo temp;
            temp.trenutnoStanje = it->trenutnoStanje;
            temp.ulaznaRijec = it->ulaznaRijec;
            temp.prijelaznoStanje = it->prijelaznoStanje;
            temp.visited = false;
            temp.trenutniPrihvatljiv = false;
            temp.prijelazniPrihvatljiv = false;
            tempSet.insert(temp);
        }
        prijelazi=tempSet;
    }
    {
        set<stanjePrihvatljivost> tempSet;
        for(auto it = dostupnaStanjaSPrihvatiljivosti.begin(); it != dostupnaStanjaSPrihvatiljivosti.end(); it++){
            stanjePrihvatljivost temp;
            temp.stanje = it->stanje;
            temp.prihvatljiv = it->prihvatljiv;
            tempSet.insert(temp);
        }
        dostupnaStanjaSPrihvatiljivosti=tempSet; 
    }

    {
        auto it = dostupnaStanjaSPrihvatiljivosti.begin();
        std::cout << it->stanje;
        it++;
        for(; it != dostupnaStanjaSPrihvatiljivosti.end(); it++){
            std::cout << "," << it->stanje;
        }
        std::cout << endl;
    }
    {
        auto it = rijeci.begin();
        std::cout << *it++;
        for(; it != rijeci.end(); it++){
                std::cout << "," << *it;
        }
        std::cout << endl;
    }
    {   
        auto it = dostupnaStanjaSPrihvatiljivosti.begin();
        string s = "";
        if(it->prihvatljiv){
            s = s + it->stanje + ",";
            it++;
        }
        for(; it != dostupnaStanjaSPrihvatiljivosti.end(); it++){
            if(it->prihvatljiv)
                s = s + it->stanje + ",";
        }
        s = s.substr(0,s.length()-1);
        std::cout << s << endl; 
    }
    std::cout << pocetnoStanje << endl;
    for(auto it = prijelazi.begin(); it != prijelazi.end(); it++) //test strukture
        std::cout << it->trenutnoStanje << "," << it->ulaznaRijec << "->" << it->prijelaznoStanje  << endl;
    //std::cout << endl;

    return 0;
}