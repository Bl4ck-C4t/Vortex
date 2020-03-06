#include "Instance.hpp"

Instance::Instance(Class ref_class):
class_(ref_class) {
    for(auto it = ref_class.getProps().begin(); it != ref_class.getProps().end(); it++){
        if(it->second->getValue().getType() != Type::FUNC){
            properties_[(std::string)it->first] = new Var(*(it->second));        
        }
    }
}

Var& 
Instance::getProp(std::string name){
    if(!properties_.contains(name)){
        throw ParserException("No property with name '" + name + "'");
    }
    Var& property = *(properties_.get(name));
    return property;
}

void 
Instance::callMethod(std::string name, std::vector<rvalue>&& args, Driver& drv){
    std::map<std::string, Var*>& props = class_.getProps();
    if(props.find(name) == props.end()){
            throw FunctionNotDefined("Function '" + name + "' does not exist.");
    }
    Var& v = *(props[name]);
    if(v.getType() != Type::FUNC){
        throw ParserException("property with name '" + name + "' is not callable.");
    }

    Function& f = (Function&)v;
    switch (f.getFuncType())
    {
    case FuncType::VORTEX:
        class_.getDriver().runFunc(f, std::move(args));
        break;

    case FuncType::NATIVE:
        {
        NativeMethod& fun = (NativeMethod&)f;
        fun.call(std::move(args), *this, drv);
        }
        break;
    
    default:
        throw ParserException("Unknown function type");
        break;
    }
}