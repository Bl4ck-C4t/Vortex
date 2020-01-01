#ifndef INTOPER_HH
#define INTOPER_HH
#include "Operation.hpp"

class IntOper: public Operation{
    public:
        IntOper(Type tp, Type tp2, std::string oper): Operation(tp, tp2, oper) {}

        rvalue execute(rvalue lhs, rvalue rhs) const{
            int l = lhs.getValue<int>();
            int r = rhs.getValue<int>();
            return rvalue(Type::INT, calculate(l, r));

        }
        virtual int calculate(int lhs, int rhs) const = 0;
};
#endif