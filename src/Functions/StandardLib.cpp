#include "StandardLib.hpp"

StdLib::StdLib(Driver& drv) {

    std::vector<Var*> props = {
        new Var(Type::OBJECT, "vec"),
        new NativeMethod("construct", Type::VOID, [](std::vector<rvalue>&& r_args, Instance& inst, Driver& drv){
            rvalue rv = r_args[0];
            Var& vec = inst.getProp("vec");
            vec.setValue(Type::OBJECT, rv.getValue<std::vector<rvalue>>());
            std::cout << "Created vector" << std::endl;
        }),
        new NativeMethod("push", Type::VOID, [](std::vector<rvalue>&& r_args, Instance& inst, Driver& drv){
            rvalue rv = r_args[0];
            Var& var_vec = inst.getProp("vec");
            auto vec = var_vec.getValue<std::vector<rvalue>>();
            vec.push_back(std::move(rv));
            for(auto it = vec.begin(); it != vec.end(); ++it){
                std::cout << *it << std::endl;
            }
            var_vec.setValue(Type::OBJECT, vec);
        })
    };
    Class vec = Class("vector",std::move(props), drv);

    classes.push_back(vec);
}