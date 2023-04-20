#include <string>
#include <set>
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <unordered_map>

//LIT
class Literal{
public:
    std::string name;
    std::string symbol;

    Literal(std::string name, std::string symbol){
        this->name = name;
        this->symbol = symbol;
    }
    inline bool operator<(const Literal& rhs) const{ //ne razlikuje poz i neg po stringu
        return symbol < rhs.symbol;
    }

    inline bool operator==(const Literal& rhs) const{
        return name == rhs.name;
    }
};
//CLAUSE
class Clause{
public:
    std::set<Literal> literals;
    int uid;
    std::string additional_info;
    std::string name;
    void getID();
    inline bool operator<(const Clause& rhs) const{
        return literals < rhs.literals;
    }
    inline bool operator==(const Clause& rhs) const{
        return literals == rhs.literals;
    }
    friend std::ostream &operator<<(std::ostream &os, const Clause &clause) {
        os << "(" << clause.uid << ")" << clause.additional_info << clause.name;
        return os;
    }
private:
    static int UID;
};
int Clause::UID = 1;
void Clause::getID(){uid = UID++;}
//AR
class AutomatedReasoning{
public:
    std::string original_target;
    std::vector<Clause> base_clauses;
    std::vector<Clause> support_clauses;
    std::unordered_map<std::string, bool> map;

    void readResolution(const std::string& path, bool targetLast); //ucita bazne Clause i cilj
    void findContradiction();
    void readInputs(const std::string& path);
private:
    bool makeClause(std::string line, std::string delim, Clause& clause); //stvori novu Clause pazeci na AvA i ~AvA
    bool checkRedundant(Clause& first, Clause& second); //ako nije redudantna 0, ako je 1. manja 1, ako je 2. manja 2
    bool sortRedundancy(Clause& first); //ako nije redudantna 0, ako je 1. manja 1, ako je 2. manja 2
    bool resolve(Clause& first, Clause& second, std::vector<Clause>& new_clauses);
    bool checkFinished();
    void makeTargetCaluses(const std::string& line, const std::string& delim);
};
void AutomatedReasoning::readInputs(const std::string& path){
    std::ifstream inputs(path);
    std::string line;
    std::vector<Clause> initial_clauses = base_clauses;

    while(std::getline(inputs, line)){
        if(line[0] == '#')
            continue;
        std::transform(line.begin(), line.end(), line.begin(),
                       [](unsigned char c){ return std::tolower(c); });
        if(line.back() == '?'){
            line.erase(line.size()-2);
            base_clauses = initial_clauses;
            support_clauses.clear();
            map.clear();
            for(const auto& clause : initial_clauses){
                map[clause.name] = true;
            }
            makeTargetCaluses(line, " v ");
            findContradiction();
        }else if(line.back() == '-'){
            line.erase(line.size()-2);
            for(auto it = initial_clauses.begin(); it!=initial_clauses.end(); it++){
                if(it->name == line){
                    initial_clauses.erase(it);
                    break;
                }
            }
        }else if(line.back() == '+'){
            line.erase(line.size()-2);
            Clause clause;
            clause.getID();
            makeClause(line, " v ", clause);
            initial_clauses.emplace_back(clause);
        }
    }
    inputs.close();
}
void AutomatedReasoning::readResolution(const std::string& path, bool targetLast){
    std::ifstream resolution(path);
    std::string line;
    while(std::getline(resolution, line)){
        if(line[0] == '#')
            continue;
        std::transform(line.begin(), line.end(), line.begin(),
                       [](unsigned char c){ return std::tolower(c); });

        if(targetLast && resolution.peek() == EOF){
            makeTargetCaluses(line, " v ");
        }else{
            Clause clause;
            if(makeClause(line, " v ", clause)){
                if(sortRedundancy(clause)){ //cisto da budem siguran da se prvo dobro napravila
                    clause.getID();
                    base_clauses.push_back(clause);
                    map[clause.name] = true;
                }
            }
        }
    }
    resolution.close();
}
void AutomatedReasoning::makeTargetCaluses(const std::string& line, const std::string& delim){ //istovremeno vraca false na nevazne Clause
    original_target = line;
    int start =0;
    int end = line.find(delim);
    while(end != -1){
        Clause clause;
        std::string name = line.substr(start, end-start);
        if(name[0] == '~'){
            Literal literal {name.substr(1), name.substr(1)};
            clause.literals.insert(literal);
            clause.name = name.substr(1);
        }else{
            Literal literal {"~"+name, name};
            clause.literals.insert(literal);
            clause.name = "~"+name;
        }
        clause.getID();
        support_clauses.push_back(clause);
        map[clause.name] = true;
        start = end + delim.size();
        end = line.find(delim, start);
    }
    Clause clause;
    std::string name = line.substr(start, end-start);
    if(name[0] == '~'){
        Literal literal {name.substr(1), name.substr(1)};
        clause.literals.insert(literal);
        clause.name = name.substr(1);
    }else{
        Literal literal {"~"+name, name};
        clause.literals.insert(literal);
        clause.name = "~"+name;
    }
    clause.getID();
    support_clauses.push_back(clause);
    map[clause.name] = true;
}
bool AutomatedReasoning::makeClause(const std::string line, const std::string delim, Clause& clause){ //istovremeno vraca false na nevazne Clause
    int start =0;
    int end = line.find(delim);
    while(end != -1){
        std::string name = line.substr(start, end-start);
        if(name[0] == '~'){
            Literal literal {name, name.substr(1)};
            auto check = clause.literals.insert(literal); //provjeriti jel slucaj A v A ili A v ~A, tj. duplikat ili nevazna klauzula
            if(!check.second && check.first->name[0] != name[0]){ //postoji takav u setu i imaju razclitiu negativnsot
                return false;
            }
        }else{
            Literal literal {name, name};
            auto check = clause.literals.insert(literal); //provjeriti jel slucaj A v A ili A v ~A, tj. duplikat ili nevazna klauzula
            if(!check.second && check.first->name[0] != name[0]){ //postoji takav u setu i imaju razclitiu negativnsot
                return false;
            }
        }
        start = end + delim.size();
        end = line.find(delim, start);
    }
    std::string name = line.substr(start, end-start);
    if(name[0] == '~'){
        Literal literal {name, name.substr(1)};
        auto check = clause.literals.insert(literal); //provjeriti jel slucaj A v A ili A v ~A, tj. duplikat ili nevazna klauzula
        if(!check.second &&check.first->name[0] != name[0]){ //postoji takav u setu i imaju razclitiu negativnsot
            return false;
        }
    }else{
        Literal literal {name, name};
        auto check = clause.literals.insert(literal); //provjeriti jel slucaj A v A ili A v ~A, tj. duplikat ili nevazna klauzula
        if(!check.second && check.first->name[0] != name[0]){ //postoji takav u setu i imaju razclitiu negativnsot
            return false;
        }
    }
    clause.name = line;
    map[line] = true;
    return true;
}
bool AutomatedReasoning::checkRedundant(Clause& first, Clause& second/*, bool (*comp)(Clause&, Clause&)*/){
    auto comp = [](const Literal& lhs, const Literal& rhs){ //razlikuj poz i neg
        return lhs.name < rhs.name;
    };
    if(std::includes(first.literals.begin(), first.literals.end(),
                     second.literals.begin(), second.literals.end(), comp)){
        return true;
    }else{
        return false;
    }
}
bool AutomatedReasoning::sortRedundancy(Clause& first){
    bool value;
    int first_size = first.literals.size();
    for(auto it = base_clauses.begin(); it != base_clauses.end(); it++){
        if(it->literals != first.literals)
            if(first_size > it->literals.size()){
                value = checkRedundant(first, *it);
                if(value) { //mi smo nadskup ostojeceg Clause
                    return false;
                }
            }else{
                value = checkRedundant(*it, first);
                if(value){
                    base_clauses.erase(it);
                    return true;
                }
            }
    }
    for(auto it = support_clauses.begin(); it != support_clauses.end(); it++){
        if(it->literals != first.literals)
            if(first_size > it->literals.size()){
                value = checkRedundant(first, *it);
                if(value) { //mi smo nadskup postojeceg Clause
                    return false;
                }
            }else{
                value = checkRedundant(*it, first);
                if(value){ //mi smo podskup postojeceg Caluse
                    support_clauses.erase(it);
                    return true;
                }
            }
    }
    return true;; // for some reason eto tako
}
void AutomatedReasoning::findContradiction(){
    std::cerr << "=======Base clauses=========" << std::endl;
    for(auto& clause : base_clauses){
        std::cerr << clause << std::endl;
    }
    std::cerr << "=======Target clauses=======" << std::endl;
    for(auto& clause : support_clauses){
        std::cerr << clause << std::endl;
    }
    std::cerr << "=======New clauses==========" << std::endl;
    std::vector<Clause> new_clauses;
    bool more = true;
    while(more){

        for(auto& first : support_clauses){ //zasada izostaje base/base dio -> nije potreban jer ako je potrebno ne valjda ionako ulaz
            for(auto& second : support_clauses){
                if(!new_clauses.empty()) break;
                if(!(first == second))
                    if(resolve(first, second, new_clauses))
                        return;
            }
            for(auto& second : base_clauses){
                if(!new_clauses.empty()) break;
                if(resolve(first, second, new_clauses))
                    return;
            }
        }

//        for(auto first : base_clauses){ //zasada izostaje base/base dio -> nije potreban jer ako je potrebno ne valjda ionako ulaz
//            if(!new_clauses.empty()) break;
//            for(auto second : base_clauses){
//                if(!(first == second))
//                    if(resolve(first, second, new_clauses))
//                        return;
//            }
//        }

        if(!new_clauses.empty()){
            support_clauses.insert(support_clauses.end(),new_clauses.begin(), new_clauses.end());
            new_clauses.clear();
        }else{
            more = !more;
        }
    }
    if(checkFinished())
        return;
    std::cout<<"[CONCLUSION]: " << original_target << " is unknown" <<std::endl;
}
bool AutomatedReasoning::checkFinished(){
    for(auto& clause : support_clauses){
        if(clause.literals.size() > 1) continue;
        if(clause.name[0] == '~'){
            if(map.count(clause.name.substr(1)) > 0){
                std::cerr<<"NIL " << clause.name << " kontradikcija " << clause.name.substr(1)<<std::endl;
                std::cout<<"[CONCLUSION]: " << original_target << " is true" <<std::endl;
                return true;
            }
        }else{
            if(map.count("~" + clause.name) > 0){
                std::cerr<<"NIL " << clause.name << " kontradikcija ~" << clause.name<<std::endl;
                std::cout<<"[CONCLUSION]: " << original_target << " is true" <<std::endl;
                return true;
            }
        }
    }
    for(auto& clause : base_clauses){
        if(clause.literals.size() > 1) continue;
        if(clause.name[0] == '~'){
            if(map.count(clause.name.substr(1)) > 0){
                std::cerr<<"NIL " << clause.name << " kontradikcija " << clause.name.substr(1)<<std::endl;
                std::cout<<"[CONCLUSION]: " << original_target << " is true" <<std::endl;
                return true;
            }
        }else{
            if(map.count("~" + clause.name) > 0){
                std::cerr<<"NIL " << clause.name << " kontradikcija ~" << clause.name<<std::endl;
                std::cout<<"[CONCLUSION]: " << original_target << " is true" <<std::endl;
                return true;
            }
        }
    }
    return false;
}
bool AutomatedReasoning::resolve(Clause& first, Clause& second, std::vector<Clause>& new_clauses){
    Clause difference;
    for(auto f_literal : first.literals){
        for(auto s_literal : second.literals){
            if(f_literal.symbol == s_literal.symbol && f_literal.name != s_literal.name){
                difference.literals.insert(f_literal);
            }
        }
    }
    if(!difference.literals.empty()){
        Clause first_new;
        std::set_difference(first.literals.begin(), first.literals.end(), //comp gleda samo symbol tako da neovisno jel dodan npr c ili ~c oduzet ce ga
                            difference.literals.begin(), difference.literals.end(), //a kako c v ~c je nemoguce ne moramo se toga bojati :)
                            std::inserter(first_new.literals, first_new.literals.end()));
        std::set_difference(second.literals.begin(), second.literals.end(),
                            difference.literals.begin(), difference.literals.end(),
                            std::inserter(first_new.literals, first_new.literals.end()));
        if(!first_new.literals.empty()){
            if(sortRedundancy(first_new)){
                std::stringstream ss;
                auto itp = first_new.literals.end();
                itp--;
                for (auto it = first_new.literals.begin(); it!=first_new.literals.end(); it++){
                    if(it == itp)
                        ss << it->name;
                    else
                        ss << it->name << " v ";
                }
                first_new.name = ss.str();
                ss.str(std::string());
                ss << "(" << first.uid << "," << second.uid << ")";
                first_new.additional_info = ss.str();
                if(map.find(first_new.name) == map.end()){
                    first_new.getID();
                    new_clauses.push_back(first_new);
                    map[first_new.name] = true;
                    std::cerr << first_new << std::endl;
                    if(first_new.literals.size() == 1){
                        if(first_new.name[0] == '~'){
                            if(map.count(first_new.name.substr(1)) > 0){
                                std::cerr<<"NIL " << first_new.name << " kontradikcija " << first_new.name.substr(1)<<std::endl;
                                std::cout<<"[CONCLUSION]: " << original_target << " is true" <<std::endl;
                                return true;
                            }
                        }else{
                            if(map.count("~" + first_new.name) > 0){
                                std::cerr<<"NIL " << first_new.name << " kontradikcija ~" << first_new.name <<std::endl;
                                std::cout<<"[CONCLUSION]: " << original_target << " is true" <<std::endl;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}

int main(int argc, char* argv[]){
    AutomatedReasoning ar;

    if(argc>=2){
        std::string command = argv[1];
        if(command == "resolution"){
            std::string path = argv[2];
            ar.readResolution(path, true);
            ar.findContradiction();
        }else if(command == "cooking"){
            std::string resolution_path = argv[2];
            std::string inputs_path = argv[3];
            ar.readResolution(resolution_path, false);
            ar.readInputs(inputs_path);
        }
    }else{
        std::cout << "Not enough arguments" << std::endl;
    }

    return 0;
}
//
// Created by mindek on 03. 04. 2022..
//