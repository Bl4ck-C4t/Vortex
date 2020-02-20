#ifndef STANDARDLIB_HPP
#define STANDARDLIB_HPP
#include <string>
#include <vector>
#include "../Variables/vars.hpp"
#include "Function.hpp"
#include "NativeFunction.hpp"

class PushList: NativeFunc{
    PushList(): NativeFunc("push", Type::VOID, {Var(Type::INT, "val")}) {
        Var(Type::INT, "val");
    }
};

#endif