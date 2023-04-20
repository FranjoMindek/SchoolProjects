#include <string>

#include "animal.hpp"
#include "myfactory.hpp"

class Parrot : public Animal{
public: //javni interface
    char const* name() override {
        return this->name_.c_str();
    }
    char const* greet() override {
        return "caw caw";
    }
    char const* menu() override {
        return "seeds";
    }
private:
    Parrot(const std::string& name) : name_(name) {}
    static void* myCreator(const std::string& arg){
        return new Parrot(arg);
    }
    std::string name_;
    static int hreg;
};

int Parrot::hreg = myfactory::instance().registerCreator("parrot", myCreator);