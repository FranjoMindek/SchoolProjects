#include<map>
#include<vector>

// myfactory.hpp
class myfactory{
public:
    typedef void* (*pFunCreator)(const std::string&);
    typedef std::map<std::string, pFunCreator> MyMap;
public:
    static myfactory& instance();
public:
    int registerCreator(const std::string& id, pFunCreator pfn);
public:
    void* create(const std::string& id, const std::string& arg);
    std::vector<std::string> getIds();
private:
    myfactory() {}
    ~myfactory() {}
    myfactory(const myfactory&) {}
    MyMap creators_;
};
