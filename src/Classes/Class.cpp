#include "Class.hpp"

Class::Class(std::string nm, std::vector<Var*>&& vec, Driver& driver):
name_(nm), drv(&driver) {
    for (int i = 0; i < vec.size(); i++)
    {
        properties_[vec[i]->getName()] = vec[i];
    }

}