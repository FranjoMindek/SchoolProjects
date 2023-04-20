#include <string>

#include "animal.hpp"
#include "myfactory.hpp"

class Tiger : public Animal{
public:
    char const* name() override {
        return this->name_.c_str();
    }
    char const* greet() override {
        return "rawr";
    }
    char const* menu() override {
        return "meat";
    }
private:
    Tiger(const std::string& name) : name_(name) {}
    static void* myCreator(const std::string& arg){
        return new Tiger(arg);
    }
    std::string name_;
    static int hreg;
};

int Tiger::hreg = myfactory::instance().registerCreator("tiger", myCreator);