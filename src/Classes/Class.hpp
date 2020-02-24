#ifndef CLASS_HPP
#define CLASS_HPP
#include <string>
#include <vector>
#include <map>
#include "../Variables/vars.hpp"
#include "../Utility/RefMap.hpp"
#include "../Functions/Function.hpp"
#include "../Driver/driver.hh"

class Class{
    Driver& drv;
    std::string name_;
    std::map<std::string, Var> properties_;

   

     public:
     
      Class(std::string nm, std::vector<Var>&& vec, Driver& driver):
     name_(nm), drv(driver) {
         for (int i = 0; i < vec.size(); i++)
         {
             properties_[vec[i].getName()] = vec[i];
         }

     }

     std::string getName() const{
         return name_;
     }

     std::map<std::string, Var>& getProps() {
         return properties_;
     }

     Driver& getDriver() const{
         return drv;
     }



};


#endif