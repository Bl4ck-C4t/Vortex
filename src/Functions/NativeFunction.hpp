#ifndef NATIVEFUNC_HPP
#define NATIVEFUNC_HPP
#include <string>
#include <vector>
#include <functional>
#include "../Variables/vars.hpp"
#include "../Driver/driver.hh"
#include "../Classes/Instance.hpp"
#include "Function.hpp"

class NativeFunc: public Function{
    using T = std::function<void(std::vector<rvalue>&&, Driver&)>;
    public:
        T body_;
    template<typename T>
    NativeFunc(std::string nm, Type r_type, const T& body):
     body_(body), Function(nm, r_type, FuncType::NATIVE) {}

    virtual void call(std::vector<rvalue>&& args, Driver& drv){
         body_(std::move(args), drv);
     }
};

class NativeMethod: public NativeFunc{
    using T = std::function<void(std::vector<rvalue>&&, Instance&, Driver&)>;
    public:
        T body_;
    template<typename T>
    NativeMethod(std::string nm, Type r_type, const T& body):
     body_(body), Function(nm, r_type, FuncType::NATIVE) {}

     void call(std::vector<rvalue>&& args, Instance& inst, Driver& drv){
         body_(std::move(args), inst, drv);
     }
};

#endif