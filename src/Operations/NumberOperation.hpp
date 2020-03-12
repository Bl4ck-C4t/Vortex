#ifndef NUMBEROPER_HPP
#define NUMBEROPER_HPP
#include "Operation.hpp"
#include <string>

class NumberOperation: public Operation{
    public:
    NumberOperation(std::string op): Operation(op) {}

    bool match(rvalue lhs, rvalue rhs, std::string operation) const
    {
        return getOper() == operation && \
        ((lhs.getType() == Type::INT || lhs.getType() == Type::FLOAT) && (rhs.getType() == Type::INT || rhs.getType() == Type::FLOAT));
    }

    rvalue execute(rvalue lhs, rvalue rhs) const {
       const auto&[f1, f2] = Operation::floatCast(lhs, rhs);
       if(lhs.getType() == Type::INT && rhs.getType() == Type::INT){
            return rvalue(Type::INT, (int)calculate(f1, f2));
       }
       return rvalue(Type::FLOAT, calculate(f1, f2));
    }


    virtual float calculate(float f1, float f2) const = 0;
};

#endif