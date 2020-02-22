#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#include <string>
#include <vector>
#include "../Variables/vars.hpp"
#include "../Functions/Function.hpp"
#include "Class.hpp"
#include "../Functions/NativeFunction.hpp"

class Instance{
    Class& class_;
    RefMap<std::string, Var> properties_;

    void callMethod(std::string name, std::vector<rvalue>&& args){
        RefMap<std::string, Function>& methods = class_.getMethods();
        if(!methods.contains(name)){
             throw FunctionNotDefined("Function '" + name + "' does not exist.");
        }
        Function& f = methods.get(name);
        switch (f.getType)
        {
        case FuncType::VORTEX:
            class_.getDriver().runFunc(f, std::move(args));
            break;

        case FuncType::NATIVE:
            NativeFunc& fun = (NativeFunc&)f;
            fun.call(std::move(args));
            break;
        
        default:
            throw ParserException("Unknown function type");
            break;
        }
    }
};



#endif