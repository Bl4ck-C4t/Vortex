#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#include <string>
#include <vector>
#include <map>
#include "../Variables/vars.hpp"
#include "../Functions/Function.hpp"
#include "Class.hpp"
#include "../Functions/NativeFunction.hpp"

class Instance{
    Class& class_;
    RefMap<std::string, Var> properties_;
    public:

    Instance(Class ref_class):
        class_(ref_class) {
            for(auto it = ref_class.getProps().begin(); it != ref_class.getProps().end(); it++){
                properties_[it->first] = Var(it->second);
            }
        }

    Var& getProp(std::string name){
        if(!properties_.contains(name)){
            throw ParserException("No property with name '" + name + "'");
        }
        Var& property = properties_.get(name);
        return property;
    }

    void callMethod(std::string name, std::vector<rvalue>&& args, Driver& drv){
        std::map<std::string, Var>& props = class_.getProps();
        if(props.find(name) == props.end()){
             throw FunctionNotDefined("Function '" + name + "' does not exist.");
        }
        Var& v = props[name];
        if(v.getType() != Type::FUNC){
            throw ParserException("property with name '" + name + "' is not callable.");
        }

        Function& f = (Function&)v;
        switch (f.getType)
        {
        case FuncType::VORTEX:
            class_.getDriver().runFunc(f, std::move(args));
            break;

        case FuncType::NATIVE:
            NativeMethod& fun = (NativeMethod&)f;
            fun.call(std::move(args), *this, drv);
            break;
        
        default:
            throw ParserException("Unknown function type");
            break;
        }
    }
};



#endif