#ifndef INTOPERS_HH
#define INTOPERS_HH
#include "IntOper.hpp"

class SumInt: public IntOper{
    public:
        SumInt(): IntOper(Type::INT, Type::INT) {}
        int calculate(int lhs, int rhs) const{
            return lhs + rhs;
        } 
};

class SubInt: public IntOper{
    public:
        SubInt(): IntOper(Type::INT, Type::INT) {}
        int calculate(int lhs, int rhs) const{
            return lhs - rhs;
        } 
};

class SubIntF: public Operation{
    public:
        SubIntF(): Operation(Type::INT, Type::FLOAT) {}
        rvalue execute(rvalue lhs, rvalue rhs) const{
            int l = lhs.getValue<int>();
            int r = rhs.getValue<float>();
            return rvalue(Type::INT, l - r);

        }
};

class MulInt: public IntOper{
    public:
        MulInt(): IntOper(Type::INT, Type::INT) {}
        int calculate(int lhs, int rhs) const{
            return lhs * rhs;
        } 
};


class DivInt: public IntOper{
    public:
        DivInt(): IntOper(Type::INT, Type::INT) {}
        int calculate(int lhs, int rhs) const{
            if(rhs == 0){
                throw ZeroDivisionException("Attempted zero division with ints");
            }
            return lhs / rhs;
        } 
};

class PowInt: public IntOper{
    public:
        PowInt(): IntOper(Type::INT, Type::INT) {}
        int calculate(int lhs, int rhs) const{
            return std::pow((float)lhs, (float)rhs);
        } 
};
#endif