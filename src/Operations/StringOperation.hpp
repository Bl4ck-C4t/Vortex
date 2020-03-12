#ifndef STRINGOPER_HPP
#define STRINGOPER_HPP
#include "Operation.hpp"

class StringOperation: public Operation{
public:
    StringOperation(std::string op): Operation(op) {}

    bool match(rvalue lhs, rvalue rhs, std::string operation) const
    {
        return getOper() == operation && \
        ((lhs.getType() == Type::CHAR || lhs.getType() == Type::STRING) && (rhs.getType() == Type::CHAR || rhs.getType() == Type::STRING));
    }

    rvalue execute(rvalue lhs, rvalue rhs) const {
       const auto&[f1, f2] = Operation::stringCast(lhs, rhs);
       return rvalue(Type::STRING, calculate(f1, f2));
    }

    virtual std::string calculate(std::string f1, std::string f2) const = 0;
};

#endif