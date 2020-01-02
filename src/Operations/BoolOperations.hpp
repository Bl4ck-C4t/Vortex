#ifndef BOOLOPERATIONS_HPP
#define BOOLOPERATIONS_HPP
#include "BoolNumOper.hpp"
#include "StringBoolOper.hpp"
// #include "Operation.hpp"

class CompareNumsBool: public BoolNumOper {
    public:
    CompareNumsBool(): BoolNumOper("==") {}

    bool calculate(float f1, float f2) const{
        return f1 == f2;
    }

};

class LessThanBoolNum: public BoolNumOper {
    public:
    LessThanBoolNum(): BoolNumOper("<") {}

    bool calculate(float f1, float f2) const{
        return f1 < f2;
    }

};

class GreaterThanBoolNum: public BoolNumOper {
    public:
    GreaterThanBoolNum(): BoolNumOper(">") {}

    bool calculate(float f1, float f2) const{
        return f1 > f2;
    }

};

class CompareBooleans: public Operation{
    public:
    CompareBooleans(): Operation(Type::BOOL, Type::BOOL, "==") {}

    virtual rvalue execute(rvalue lhs, rvalue rhs) const {

        return rvalue(Type::BOOL, lhs.getValue<bool>() == rhs.getValue<bool>());
    }

};

class CompareString: public StringBoolOper{
    public:
    CompareString(): StringBoolOper("==") {}

    bool calculate(std::string f1, std::string f2) const {
        return f1 == f2;
    }

};

class GreaterThanStringBool: public StringBoolOper{
    public:
    GreaterThanStringBool(): StringBoolOper(">") {}

    bool calculate(std::string f1, std::string f2) const {
        return f1 > f2;
    }

};

class LessThenStringBool: public StringBoolOper{
    public:
    LessThenStringBool(): StringBoolOper("<") {}

    bool calculate(std::string f1, std::string f2) const {
        return f1 < f2;
    }

};



#endif