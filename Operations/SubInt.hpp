#ifndef SUBINT_HH
#define SUBINT_HH
#include "IntOper.hpp"

class SubInt: public IntOper{
    public:
        SubInt(): IntOper(Type::INT, Type::INT) {}
        int calculate(int lhs, int rhs) const{
            return lhs - rhs;
        } 
};
#endif