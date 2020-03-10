#ifndef INSTANCE_HPP
#define INSTANCE_HPP
#include <string>
#include <vector>
#include <map>
#include "../Variables/vars.hpp"
#include "../Functions/Function.hpp"
#include "Class.hpp"
#include "../Driver/driver.hpp"
#include "../Functions/NativeFunction.hpp"

class Instance{
    Class& class_;
    RefMap<std::string, Var*> properties_;
    public:

    Instance(Class& ref_class);

    Var& getProp(std::string name);

    void callMethod(std::string name, std::vector<rvalue>&& args, Driver& drv);

    Class& getClass();
};



#endif