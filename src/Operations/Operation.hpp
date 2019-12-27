#ifndef OPERATION_HPP
#define OPERATION_HPP
#include "../Variables/vars.hpp"
#include <cmath>

class Operation{
    Type type1_;
    Type type2_;
    public:
        Operation(Type tp, Type tp2): type1_(tp), type2_(tp2) {}
        bool match(rvalue lhs, rvalue rhs) const
        {
            return lhs.getType() == type1_ && rhs.getType() == type2_;
        }
        virtual rvalue execute(rvalue lhs, rvalue rhs) const = 0;
};

#endif