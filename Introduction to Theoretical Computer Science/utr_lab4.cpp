#include<iostream>
#include<string.h>
#include<map>

unsigned int i = 0;
std::string input;
std::string output = "";

void readNonterminal(std::string symbol, std::map<std::string, std::string> &target);

int main(){
    getline(std::cin, input);
    std::map<std::string, std::string> transitionMap; //fiksno zadani prijelazi...
    transitionMap.insert(std::pair<std::string,std::string>("Sa", "aAB")); 
    transitionMap.insert(std::pair<std::string,std::string>("Sb", "bBA"));
    transitionMap.insert(std::pair<std::string,std::string>("Ab", "bC"));
    transitionMap.insert(std::pair<std::string,std::string>("Aa", "a"));
    transitionMap.insert(std::pair<std::string,std::string>("Bc", "ccSbc"));
    transitionMap.insert(std::pair<std::string,std::string>("B$", "$"));
    transitionMap.insert(std::pair<std::string,std::string>("C#", "AA"));
    if(i < input.size()){
       readNonterminal("S", transitionMap);
    }
    std::cout << output << std::endl;
    if(i == input.size()){
        std::cout << "DA";
        return 0;
    }
    std::cout << "NE";
    return 1;
}

void readNonterminal(std::string symbol, std::map<std::string, std::string> &target){
    output = output + symbol;
    auto value = target.find(symbol + input[i]); //nadji normalan prijelaz
    if(value == target.end()){
        value = target.find(symbol + '$'); //nadji epsilon prijelaz
    }
    if(value == target.end()){
        value = target.find(symbol + '#'); //nadji prijelaz bez terminalnih stanja
    }
    if(value == target.end()){
        std::cout << output << std::endl << "NE";
        exit(2);
    }
    for(unsigned int j = 0; j < value->second.size(); j++){
        char chr = value->second[j];
        if(chr >= 'a' && chr <= 'z'){ //terminalni znak 
            if(chr == input[i]){
                i++;
            }else{
                std::cout << output << std::endl << "NE";
                exit(3);
            }
        }else if(chr == '$'){
            continue;
        }else{
            std::string temp (1, chr);
            readNonterminal(temp, target);
        }
    }
    return;
}