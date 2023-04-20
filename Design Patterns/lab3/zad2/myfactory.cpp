#include "myfactory.hpp"

myfactory& myfactory::instance(){
    static myfactory theFactory;
    return theFactory;
}

int myfactory::registerCreator(const std::string& id, pFunCreator pfn) {
    creators_.emplace(std::make_pair(id, pfn));
    return 0;
}

void* myfactory::create(const std::string& id, const std::string& arg) {
    pFunCreator creator = this->creators_.at(id);
    return (*creator)(arg);
}

std::vector<std::string> myfactory::getIds() {
    std::vector<std::string> vector;
    for(auto it : creators_){
        vector.emplace_back(it.first);
    }
    return vector;
}

