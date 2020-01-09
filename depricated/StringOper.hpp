#ifndef STROPER_HH
#define STROPER_HH
#include "Operation.hpp"

class StringOper: public Operation{
    public:
        StringOper(Type tp, Type tp2, std::string oper): Operation(tp, tp2, oper) {}

        rvalue execute(rvalue lhs, rvalue rhs) const{
            std::string l = lhs.getValue<std::string>();
            std::string r = rhs.getValue<std::string>();
            return rvalue(Type::STRING, calculate(l, r));

        }
        virtual std::string calculate(std::string lhs, std::string rhs) const = 0;
};
#endif