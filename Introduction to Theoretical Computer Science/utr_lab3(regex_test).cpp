#include<set>
#include<map>
#include<iostream>
#include<regex>
#include<stack>
#include<tuple>
#include<string.h>
using namespace std;

regex regexPrvi("([a-zA-Z0-9$]+\\,*)+"); 
regex regexDrugi("[a-zA-Z0-9$]+"); 
sregex_iterator it_end;

class Automat {
    private:
        map<string, pair<string,string>> mapaPrijelaza;
        string prihvatljivaStanja;
        string trenutnoStanje;
        string vrhStoga;
        string stog;
        string stanjeReset;
        string stogReset;
        void resetiraj(){
            this->trenutnoStanje = stanjeReset;
            this->vrhStoga = stogReset;
            this->stog = vrhStoga;
        }
        bool citaj(string znak){
            string kljuc = trenutnoStanje + znak + vrhStoga;
            map<string, pair<string,string>>::const_iterator iter = mapaPrijelaza.find(kljuc);
            if(iter != mapaPrijelaza.end()){
                trenutnoStanje = iter->second.first;
                string promjenaStoga = iter->second.second;
                stog = stog.substr(1);
                if(promjenaStoga != "$"){
                    stog = promjenaStoga + stog;
                }
                vrhStoga = stog.substr(0,1);
                return true;
            }
            else {
                cout << "fail|";
                return false;
            }
        }
    public:
        Automat(string prihvatljivaStanja, string pocStanje, string pocStog){
            this->prihvatljivaStanja = prihvatljivaStanja;
            this->trenutnoStanje = pocStanje;
            this->stanjeReset = pocStanje;
            this->vrhStoga = pocStog;
            this->stogReset = pocStog;
            this->stog = pocStog;
        }
        void unesiPrijelaz(string kljuc, pair<string, string> vrijednost){
            mapaPrijelaza.insert( pair<string, pair<string, string>>(kljuc, vrijednost) );
        }
        void rijesi(string ulaz){
            sregex_iterator itUlaza(ulaz.begin(), ulaz.end(), regexPrvi);
            while(itUlaza != it_end) {
                bool ispravan = 1;
                string niz = itUlaza->str();
                sregex_iterator it2(niz.begin(), niz.end(), regexDrugi);
                ispisiTrenutno();
                while (it2 != it_end && ispravan) {
                    {
                        bool ok = 1;
                        while(ok == 1){
                            ok = 0;
                            if(this->mapaPrijelaza.count(this->trenutnoStanje + "$" + this->vrhStoga)){
                                //cout << "naso epsilon";
                                citaj("$");
                                ispisiTrenutno();
                                ok = 1;
                            }
                        }
                    }
                    ispravan = citaj(it2->str());
                    if(!ispravan) break;
                    ispisiTrenutno();
                    ++it2;
                }
                {
                    bool ok = 1;
                    while(ok == 1){
                        ok = 0;
                        if(this->mapaPrijelaza.count(this->trenutnoStanje + "$" + this->vrhStoga) && this->prihvatljivaStanja.find(this->trenutnoStanje) == (long unsigned int)-1){
                            //cout << "naso epsilon";
                            citaj("$");
                            ispisiTrenutno();
                            ok = 1;
                        }
                    }
                }
                if(this->prihvatljivaStanja.find(this->trenutnoStanje) != (long unsigned int)-1 && ispravan)
                    cout << "1" << endl;
                else
                    cout << "0" << endl;
                resetiraj();
                ++itUlaza;
            }
        }

        void ispisiTrenutno(){
            if(this->stog=="")
                cout << this->trenutnoStanje + "#" + "$" + "|";
            else
                cout << this->trenutnoStanje + "#" + this->stog + "|";
        }

};


int main() { 
    string ulazniNiz;
    string prihvatljivaStanja;
    string pocStanje;
    string pocStog;
    string prijelaz;
    getline(cin, ulazniNiz);
    for(int i = 0; i<3; i++)
    getline(cin, prihvatljivaStanja); //nepotrebne informacije za rad
    getline(cin, prihvatljivaStanja); //kasnije budemo trazili u ovom string trenutni s regex
    getline(cin, pocStanje);
    getline(cin, pocStog);
    Automat automat = Automat(prihvatljivaStanja, pocStanje, pocStog);

    //dodavanje prijelaza u automat
    while(getline(cin, prijelaz)){
        string kljuc = "";
        pair<string, string> vrijednost;
        bool prvi = true;
        sregex_iterator itPrijelaza(prijelaz.begin(), prijelaz.end(), regexPrvi);
        while(itPrijelaza != it_end) {
            string prijelazStrana = itPrijelaza->str();
            sregex_iterator it2(prijelazStrana.begin(), prijelazStrana.end(), regexDrugi);
            if(prvi){
                kljuc += it2->str();
                it2++;
                kljuc += it2->str();
                it2++;
                kljuc += it2->str();
                prvi = !prvi;
            }
            else{
                vrijednost.first = it2->str();
                it2++;
                vrijednost.second = it2->str();
                prvi = !prvi;
            }
            ++itPrijelaza;
        }
        automat.unesiPrijelaz(kljuc, vrijednost);
    }

    //rijesi
    automat.rijesi(ulazniNiz);

    return 0; 
}