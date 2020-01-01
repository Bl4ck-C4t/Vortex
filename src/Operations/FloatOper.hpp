#ifndef FLOATOPER_HH
#define FLOATOPER_HH
#include "Operation.hpp"

class FloatOper: public Operation{
    public:
        FloatOper(Type tp, Type tp2, std::string op): Operation(tp, tp2, op) {}

        rvalue execute(rvalue lhs, rvalue rhs) const{
            float l = lhs.getValue<float>();
            float r = rhs.getValue<float>();
            return rvalue(Type::FLOAT, calculate(l, r));

        }
        virtual float calculate(float lhs, float rhs) const = 0;
};
#endif