#include "Class.hpp"

Class::Class(std::string nm, std::vector<Var*>&& vec, Driver& driver):
name_(nm), drv(&driver) {
    for (int i = 0; i < vec.size(); i++)
    {
        if(vec[i]->getValue().getType() == Type::FUNC){
            std::vector<Var>& arguments = ((Function*)vec[i])->getArgs();
            arguments.insert(arguments.begin(), Var(Type::OBJECT, "this"));
        }
        properties_[vec[i]->getName()] = vec[i];
    }

}