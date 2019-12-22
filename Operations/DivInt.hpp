#ifndef DIVINT_HH
#define DIVINT_HH
#include "IntOper.hpp"


class ZeroDivisionException {};
class DivInt: public IntOper{
    public:
        DivInt(): IntOper(Type::INT, Type::INT) {}
        int calculate(int lhs, int rhs) const{
            if(rhs == 0){
                throw ZeroDivisionException();
            }
            return lhs / rhs;
        } 
};
#endif