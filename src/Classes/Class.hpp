#ifndef CLASS_HPP
#define CLASS_HPP
#include <string>
#include <vector>
#include "../Variables/vars.hpp"
#include "../Utility/RefMap.hpp"
#include "../Functions/Function.hpp"
#include "../Driver/driver.hh"

class Class{
    Driver& drv;
    std::string name_;
    RefMap<std::string, Var> properties_;
    RefMap<std::string, Function> methods_;

    Class(std::string nm, std::vector<Var>&& vec, std::vector<Function>&& methods, Driver& driver):
     name_(nm), drv(driver) {
         for (int i = 0; i < vec.size(); i++)
         {
             properties_[vec[i].getName()] = vec[i];
         }

         for (int i = 0; i < methods.size(); i++)
         {
             methods_[methods[i].getName()] = methods[i];
         }

     }

     public:
     
     std::string getName() const{
         return name_;
     }

     RefMap<std::string, Var>& getProps() {
         return properties_;
     }

     RefMap<std::string, Function>& getMethods() {
         return methods_;
     }

     Driver& getDriver() const{
         return drv;
     }



};


#endif