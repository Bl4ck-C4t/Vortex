#ifndef SUMSTR_HH
#define SUMSTR_HH
#include "StringOper.hpp"

class SumString: public StringOper{
    public:
        SumString(): StringOper(Type::STRING, Type::STRING) {}
        std::string calculate(std::string lhs, std::string rhs) const{
            return lhs + rhs;
        } 
};
#endif