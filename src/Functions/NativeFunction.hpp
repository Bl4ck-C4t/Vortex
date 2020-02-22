#ifndef NATIVEFUNC_HPP
#define NATIVEFUNC_HPP
#include <string>
#include <vector>
#include <functional>
#include "../Variables/vars.hpp"
#include "../Driver/driver.hh"
#include "Function.hpp"

class NativeFunc: Function{
    using T = std::function<void(std::vector<rvalue>&& args, Driver& drv)>;
    public:
        T body_;
    template<typename T>
    NativeFunc(std::string nm, Type r_type, const T& body):
     body_(body), Function(nm, r_type, FuncType::NATIVE) {}
};

#endif