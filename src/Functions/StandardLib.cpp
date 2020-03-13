#include "StandardLib.hpp"
#include <iostream>
#include "../Variables/vars.hpp"

StdLib::StdLib(Driver& drv) {

    std::vector<Var*> props = {
        new Var(Type::OBJECT, "vec"),
        new NativeMethod("construct", Type::VOID, [](std::vector<rvalue>&& r_args, Instance& inst, Driver& drv){
            rvalue rv = r_args[0];
            Var& vec = inst.getProp("vec");
            vec.setValue(Type::OBJECT, rv.getValue<std::vector<rvalue>>());
        }),
        new NativeMethod("push", Type::VOID, [](std::vector<rvalue>&& r_args, Instance& inst, Driver& drv){
            rvalue rv = r_args[0];
            Var& var_vec = inst.getProp("vec");
            auto vec = var_vec.getValue<std::vector<rvalue>>();
            vec.push_back(std::move(rv));
            var_vec.setValue(Type::OBJECT, vec);
        }),
        new NativeMethod("remove", Type::VOID, [](std::vector<rvalue>&& r_args, Instance& inst, Driver& drv){
            rvalue rv = r_args[0];
            Var& var_vec = inst.getProp("vec");
            auto vec = var_vec.getValue<std::vector<rvalue>>();
            vec.erase(vec.begin() + rv.getValue<int>());
            var_vec.setValue(Type::OBJECT, vec);
        }),
        new NativeMethod("atIndex", Type::OBJECT, [](std::vector<rvalue>&& r_args, Instance& inst, Driver& drv){
            int index = r_args[0].getValue<int>();
            Var& var_vec = inst.getProp("vec");
            auto vec = var_vec.getValue<std::vector<rvalue>>();
            rvalue& element = vec[index];
            drv.setLastValue(rvalue(element));
        }),
        new NativeMethod("len", Type::INT, [](std::vector<rvalue>&& r_args, Instance& inst, Driver& drv){
            Var& var_vec = inst.getProp("vec");
            auto vec = var_vec.getValue<std::vector<rvalue>>();
            drv.setLastValue(rvalue(Type::INT, (int)vec.size()));
        })
    };
    Class vec = Class("vector",std::move(props), drv);

    classes.push_back(vec);

    functions.push_back(new NativeFunc("print", Type::INT, [](std::vector<rvalue>&& r_args, Driver& drv){
            std::cout << r_args[0] << std::endl;
        }));
    functions.push_back(new NativeFunc("input", Type::INT, [](std::vector<rvalue>&& r_args, Driver& drv){
            if (r_args.size() > 0){
                if(r_args[0].getType() != Type::STRING){
                    throw ParserException("First argument of 'input' should be string not " + typeToString(r_args[0].getType()));
                }
                std::cout << r_args[0].getValue<std::string>();
            }
            std::string input;
            std::cin >> input;
            drv.setLastValue(rvalue(Type::STRING, input));
        }));
}