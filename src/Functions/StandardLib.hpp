#ifndef STANDARDLIB_HPP
#define STANDARDLIB_HPP
#include <string>
#include <vector>
#include <iostream>
#include "../Variables/vars.hpp"
#include "../Classes/Class.hpp"
#include "../Driver/driver.hh"
#include "../Classes/Instance.hpp"
#include "Function.hpp"
#include "NativeFunction.hpp"

struct StdLib{
    public: 
    std::vector<Class> classes;
    StdLib(Driver& drv) {

        std::vector<Var> props = {
            Var(Type::OBJECT, "vec"),
            NativeMethod("construct", Type::VOID, [](std::vector<rvalue>&& args, Instance& inst, Driver& drv){
                rvalue rv = args[0];
                std::vector<rvalue>& vec = inst.getProp("vec").getValue<std::vector<rvalue>&>();
                vec = rv.getValue<std::vector<rvalue>>();
                std::cout << "Created vector" << std::endl;
            }),
            NativeMethod("push", Type::VOID, [](std::vector<rvalue>&& args, Instance& inst, Driver& drv){
                rvalue rv = args[0];
                std::vector<rvalue>& vec = inst.getProp("vec").getValue<std::vector<rvalue>&>();
                vec.push_back(std::move(rv));
                for(auto it = vec.begin(); it != vec.end(); ++it){
                    std::cout << *it << std::endl;
                }
            })
        };
        Class vec = Class("vector",std::move(props), drv);

        classes.push_back(vec);
    }
};

#endif