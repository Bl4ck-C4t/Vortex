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

void 
Class::extendWithClasses(std::vector<Class>&& classes){
    for(auto it = classes.begin(); it != classes.end(); ++it){        
            for(auto it2 = it->getProps().begin(); it2 != it->getProps().end(); ++it2){
                if(properties_.find(it2->first) == properties_.end()){
                    properties_[it2->first] = it2->second;
                }

            }
    }
    base_classes_ = new std::vector<Class>(std::move(classes));
    // *base_classes_ = std::move(classes);
}

Class::~Class(){
    // delete base_classes_;
    for (auto it = properties_.begin(); it != properties_.end(); ++it) {
        // delete properties_[it->first];
    }
}