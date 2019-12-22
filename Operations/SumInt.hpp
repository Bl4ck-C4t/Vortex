#ifndef SUMINT_HH
#define SUMINT_HH
#include "IntOper.hpp"

class SumInt: public IntOper{
    public:
        SumInt(): IntOper(Type::INT, Type::INT) {}
        int calculate(int lhs, int rhs) const{
            return lhs + rhs;
        } 
};
#endif