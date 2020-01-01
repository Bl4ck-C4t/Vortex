#ifndef OPERATION_HPP
#define OPERATION_HPP
#include "../Variables/vars.hpp"
#include <cmath>
#include <string>

class Operation{
    Type type1_;
    Type type2_;
    std::string oper_;
    public:
        Operation(Type tp, Type tp2, std::string op): type1_(tp), type2_(tp2), oper_(op) {}
        bool match(rvalue lhs, rvalue rhs, std::string operation) const
        {
            return lhs.getType() == type1_ && rhs.getType() == type2_ && oper_ == operation;
        }
        virtual rvalue execute(rvalue lhs, rvalue rhs) const = 0;
};

#endif