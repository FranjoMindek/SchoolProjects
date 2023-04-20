#include <iostream>
#include <string>
#include <vector> 
#include <map>
#include <set>
#include <list>

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

template <class T> void tokenize(string s, string del = " ",  vector<T> &vector = nullptr)
{
    int start = 0;
    int end = s.find(del);
    while (end != -1) {
        vector.push_back(s.substr(start, end - start));
        start = end + del.size();
        end = s.find(del, start);
    }
    vector.push_back(s.substr(start, end - start));
}

int main(){
    string ulazneRijeci;
    string stanja;
    string rijeci;
    string prihvatljivaStanja;
    string pocetnoStanje;
    string ucitavanje;
    getline(cin,ulazneRijeci);
    getline(cin,stanja);
    getline(cin,rijeci);
    getline(cin,prihvatljivaStanja);
    getline(cin,pocetnoStanje);
    map<string, string> mapaPrijelaza;
    map<string, string> mapaEpsilonPrijelaza;
    map<string, string> mapaEpsilonPrijelazaPocetna;
    //ucitaje sve

    while(getline(cin,ucitavanje)){
        if(ucitavanje.find("#") != -1){ //prazni prijelazi nas ne zanjimaju
            continue;
        }
        int pos;
        pos = ucitavanje.find("$");
        if(pos != -1){
            mapaEpsilonPrijelaza.insert(pair<string,string>(ucitavanje.substr(0,pos-1),ucitavanje.substr(pos+3)));
            continue;
        }
        pos = ucitavanje.find("->");
        if(pos != -1){
            mapaPrijelaza.insert(pair<string,string>(ucitavanje.substr(0,pos),ucitavanje.substr(pos+2)));
            continue;
        }
    }

    //sredi epsilon prijelaze
    mapaEpsilonPrijelazaPocetna = mapaEpsilonPrijelaza;
    for(auto it = mapaEpsilonPrijelaza.begin(); it != mapaEpsilonPrijelaza.end(); ++it){
        bool imaJos = 1;
        while(imaJos){
        imaJos = 0;
        for(auto it2 = mapaEpsilonPrijelazaPocetna.begin(); it2 != mapaEpsilonPrijelazaPocetna.end(); ++it2){
            int pos = it->second.find(it2->second);
            if(pos != -1)
                continue;
            pos = it->second.find(it2->first);

            if(pos != -1)
                if(it2->first.compare(it->second.substr(pos,it2->first.size()+1)) == 0
                || (it2->first + ",").compare(it->second.substr(pos,it2->first.size()+1)) == 0 ){
                it->second = it->second + "," + it2->second;
                imaJos = 1;
            }
        }
        }
    }

    //sredi prijelaze
    for(auto it = mapaPrijelaza.begin(); it != mapaPrijelaza.end(); ++it){
        for(auto it2 = mapaEpsilonPrijelaza.begin(); it2 != mapaEpsilonPrijelaza.end(); ++it2){
            int pos = it->second.find(it2->first);
            if(pos != -1)
                if(it2->first.compare(it->second.substr(pos,it2->first.size()+1)) == 0
                || (it2->first + ",").compare(it->second.substr(pos,it2->first.size()+1)) == 0 ){
                it->second = it->second + "," + it2->second;
            }
        }
    }

    //sredi pocetno stanje
    for(auto it2 = mapaEpsilonPrijelaza.begin(); it2 != mapaEpsilonPrijelaza.end(); ++it2){
        if(pocetnoStanje.compare(it2->first) == 0){
            pocetnoStanje = pocetnoStanje + "," + it2->second;
        }
    }
    set<string> popravakPocetnog;
    tokenize(pocetnoStanje, ",", popravakPocetnog);
    pocetnoStanje = "";
    for(auto it2 = popravakPocetnog.begin(); it2 != popravakPocetnog.end(); it2++){
        pocetnoStanje = pocetnoStanje + "," + *it2;
        }
    if(pocetnoStanje.size() > 1)
        pocetnoStanje = pocetnoStanje.substr(1);


    //sredi ulazne rijeci
    vector<string> temp;
    tokenize(ulazneRijeci, "|", temp);
    vector<string> ulazniNizovi[temp.size()];
    int cnt = 0;
    for(auto it = temp.begin(); it != temp.end(); it++){
        tokenize(*it, ",", ulazniNizovi[cnt]);
        cnt++;
    }

    //printanje
    for(int i = 0; i<temp.size(); i++){
        string trenutnoStanje = pocetnoStanje;
        set<string> stanjaTrenutnog;
        set<string> stanjaIduceg;
        int stlyeCnt = 0;
        for(auto it = ulazniNizovi[i].begin(); it != ulazniNizovi[i].end(); it++){
            cout << trenutnoStanje << "|";
            tokenize(trenutnoStanje, ",", stanjaTrenutnog);
            for(auto it2 = stanjaTrenutnog.begin(); it2 != stanjaTrenutnog.end(); it2++){
                string kljuc = *it2 + "," + *it; //stanje,rijec
                if(mapaPrijelaza.find(kljuc) != mapaPrijelaza.end()){
                    tokenize(mapaPrijelaza.at(kljuc), ",", stanjaIduceg);
                }
            }
            trenutnoStanje = "";
            for(auto it2 = stanjaIduceg.begin(); it2 != stanjaIduceg.end(); it2++){
                trenutnoStanje = trenutnoStanje + "," + *it2;
            }
            if(trenutnoStanje.size() > 1)
                trenutnoStanje = trenutnoStanje.substr(1);
            else cout << "#";
            stanjaTrenutnog.clear();
            stanjaIduceg.clear();
            stlyeCnt++;
        }
        cout << trenutnoStanje << endl;
    }

    return 0;
}
