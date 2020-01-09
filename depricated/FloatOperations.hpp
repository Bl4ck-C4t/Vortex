#ifndef FLOATOPERS_HH
#define FLOATOPERS_HH
#include "FloatOper.hpp"

class FloatSum: public FloatOper{
    public:
        FloatSum(): FloatOper(Type::FLOAT, Type::FLOAT, "+") {}
        float calculate(float lhs, float rhs) const{
            return lhs + rhs;
        } 
};

class FloatSub: public FloatOper{
    public:
        FloatSub(): FloatOper(Type::FLOAT, Type::FLOAT, "-") {}
        float calculate(float lhs, float rhs) const{
            return lhs - rhs;
        } 
};

class FloatMul: public FloatOper{
    public:
        FloatMul(): FloatOper(Type::FLOAT, Type::FLOAT, "*") {}
        float calculate(float lhs, float rhs) const{
            return lhs * rhs;
        } 
};

class FloatDiv: public FloatOper{
    public:
        FloatDiv(): FloatOper(Type::FLOAT, Type::FLOAT, "/") {}
        float calculate(float lhs, float rhs) const{
            if(rhs == 0.0){
                throw ZeroDivisionException("Attempted zero division with floats");
            }
            return lhs / rhs;
        } 
};

class FloatPow: public FloatOper{
    public:
        FloatPow(): FloatOper(Type::FLOAT, Type::FLOAT, "**") {}
        float calculate(float lhs, float rhs) const{
            return std::pow(lhs, rhs);

        } 
};
#endif