#include "StandardLib.hpp"

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
        new NativeMethod("atIndex", Type::VOID, [](std::vector<rvalue>&& r_args, Instance& inst, Driver& drv){
            int index = r_args[0].getValue<int>();
            Var& var_vec = inst.getProp("vec");
            auto vec = var_vec.getValue<std::vector<rvalue>>();
            rvalue& element = vec[index];
            drv.setLastValue(rvalue(element));
        })
    };
    Class vec = Class("vector",std::move(props), drv);

    classes.push_back(vec);
}