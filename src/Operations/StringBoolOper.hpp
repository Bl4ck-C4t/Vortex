#ifndef STRINGBOOLOPER_HPP
#define STRINGBOOLOPER_HPP
#include "Operation.hpp"
#include <string>

class StringBoolOper: public Operation{
    public:
    StringBoolOper(std::string oper): Operation(oper) {}

    bool match(rvalue lhs, rvalue rhs, std::string operation) const
    {
        return getOper() == operation && \
        ((lhs.getType() == Type::STRING || lhs.getType() == Type::CHAR) || (rhs.getType() == Type::STRING || rhs.getType() == Type::CHAR));
    }

    rvalue execute(rvalue lhs, rvalue rhs) const {
        std::string f1,f2;

        if(lhs.getType() == Type::CHAR){
            f1 = std::string(1, lhs.getValue<char>());
        }
        else{
            f1 = lhs.getValue<std::string>();
        }

        if(rhs.getType() == Type::CHAR){
            f2 = std::string(1, rhs.getValue<char>());
        }
        else{
            f2 = rhs.getValue<std::string>();
        }

        return rvalue(Type::BOOL, calculate(f1, f2));
    }


    virtual bool calculate(std::string f1, std::string f2) const = 0;


};

#endif