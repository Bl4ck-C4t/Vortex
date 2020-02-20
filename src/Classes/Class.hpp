#ifndef CLASS_HPP
#define CLASS_HPP
#include <string>
#include <vector>
#include "../Variables/vars.hpp"
#include "../Utility/RefMap.hpp"
#include "../Functions/Function.hpp"

class Class{
    std::string name_;
    RefMap<std::string, Var> properties_;
    RefMap<std::string, Function> methods_;

    Class(std::string nm, std::vector<Var>&& vec, std::vector<Function>&& methods):
     name_(nm) {
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
     
     std::string getName(){
         return name_;
     }

};


#endif