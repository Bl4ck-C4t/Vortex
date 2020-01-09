#ifndef OPERATIONS_HPP
#define OPERATIONS_HPP
#include "NumberOperation.hpp"
#include "StringOperation.hpp"

class NumberSumOper: public NumberOperation{
    public:
    NumberSumOper(): NumberOperation("+") {}
    float calculate(float f1, float f2) const {
        return f1 + f2;
    }
};

class NumberSubOper: public NumberOperation{
    public:
    NumberSubOper(): NumberOperation("-") {}
    float calculate(float f1, float f2) const {
        return f1 - f2;
    }
};

class NumberMulOper: public NumberOperation{
    public:
    NumberMulOper(): NumberOperation("*") {}
    float calculate(float f1, float f2) const {
        return f1 * f2;
    }
};

class NumberDivOper: public NumberOperation{
    public:
    NumberDivOper(): NumberOperation("/") {}
    float calculate(float f1, float f2) const {
        if(f2 == 0.0){
            throw ZeroDivisionException("Attempted zero division");
        }
        return f1 / f2;
    }
};

class NumberPowOper: public NumberOperation{
    public:
    NumberPowOper(): NumberOperation("**") {}
    float calculate(float f1, float f2) const {
        return std::pow(f1, f2);
    }
};

class StringSum: public StringOperation{
    public:
    StringSum(): StringOperation("+") {}
    std::string calculate(std::string f1, std::string f2) const {
        return f1 + f2;
    }
};


#endif