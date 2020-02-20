#ifndef NATIVEFUNC_HPP
#define NATIVEFUNC_HPP
#include <string>
#include <vector>
#include "../Variables/vars.hpp"
#include "Function.hpp"

class NativeFunc: Function{
    public:
    NativeFunc(std::string nm, Type r_type, std::vector<Var>&& vec):
     Function(nm, r_type, std::move(vec), "") {}

     virtual void call(std::vector<Var>&& args) = 0;
};

#endif