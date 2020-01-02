#ifndef BOOLNUMOPER_HPP
#define BOOLNUMOPER_HPP
#include "BoolNumOper.hpp"
class CompareNumsBool: public BoolNumOper {
    public:
    CompareNumsBool(): BoolNumOper("==") {}

    bool calculate(float f1, float f2) const{
        return f1 == f2;
    }

};

#endif