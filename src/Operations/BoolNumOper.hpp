#ifndef BOOLNUMOPER_HH
#define BOOLNUMOPER_HH
#include "Operation.hpp"
#include <string>

class BoolNumOper: public Operation{
    public:
    BoolNumOper(std::string oper): Operation(oper) {}

    bool match(rvalue lhs, rvalue rhs, std::string operation) const
    {
        return getOper() == operation && \
        ((lhs.getType() == Type::INT || lhs.getType() == Type::FLOAT) || (rhs.getType() == Type::INT || rhs.getType() == Type::FLOAT));
    }

    rvalue execute(rvalue lhs, rvalue rhs) const {
        float f1,f2;

        if(lhs.getType() == Type::INT){
            f1 = (float)lhs.getValue<int>();
        }
        else{
            f1 = lhs.getValue<float>();
        }

        if(rhs.getType() == Type::INT){
            f2 = (float)rhs.getValue<int>();
        }
        else{
            f2 = rhs.getValue<float>();
        }

        return rvalue(Type::BOOL, calculate(f1, f2));
    }


    virtual bool calculate(float f1, float f2) const = 0;


};

#endif