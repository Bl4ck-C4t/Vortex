#ifndef CLASS_HPP
#define CLASS_HPP
#include <string>
#include <vector>
#include <map>
#include "../Variables/vars.hpp"
#include "../Utility/RefMap.hpp"
#include "../Functions/Function.hpp"

class Driver;
class NoSuchClassException: public ParserException{
    public:
    NoSuchClassException(std::string className): ParserException("Class '" + className + "' doesn't exist") {}
};
class Class{
    Driver* drv = nullptr;
    std::string name_;
    std::map<std::string, Var*> properties_;

     public:
     
      Class(std::string nm, std::vector<Var*>&& vec, Driver& driver);

     Class() {}

     void extendWithClasses(std::vector<Class>&& classes);

     std::string getName() const{
         return name_;
     }

     std::map<std::string, Var*>& getProps() {
         return properties_;
     }

     Driver& getDriver() const{
         return *drv;
     }



};


#endif