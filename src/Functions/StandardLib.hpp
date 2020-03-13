#ifndef STANDARDLIB_HPP
#define STANDARDLIB_HPP
#include <string>
#include <vector>
#include <iostream>
#include "../Variables/vars.hpp"
#include "../Classes/Class.hpp"
#include "../Classes/Instance.hpp"
#include "Function.hpp"
#include "NativeFunction.hpp"

class WrongTypeException : public ParserException{
 public:
        WrongTypeException(const Type& lhs, const Type& rhs):
        ParserException("Expected type '" + typeToString(rhs) + "' got '" + typeToString(lhs) + "'") {}
};
class Driver;
class StdLib{
    public: 
    std::vector<Class> classes;
    std::vector<NativeFunc*> functions;
    StdLib(Driver& drv);
};

#endif