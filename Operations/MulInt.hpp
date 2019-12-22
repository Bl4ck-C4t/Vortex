#ifndef MULINT_HH
#define MULINT_HH
#include "IntOper.hpp"
enum struct Type;

class MulInt: public IntOper{
    public:
        MulInt(): IntOper(Type::INT, Type::INT) {}
        int calculate(int lhs, int rhs) const{
            return lhs * rhs;
        } 
};
#endif