#ifndef FUNCTION_HPP
#define FUNCTION_HPP
#include <string>
#include <vector>
#include "../../Variables/vars.hpp"

class FunctionDefinedException: public ParserException{
    public:
    FunctionDefinedException(std::string msg): ParserException(msg) {}
    FunctionDefinedException(): ParserException("Function already defined") {}
};

class Function{
   std::string name_;
    Type ret_type_;
    std::string body_;
    std::vector<Var> arg_list_;

   public:
    Function(std::string nm, Type r_type, std::vector<Var>&& vec, std::string body):
    name_(nm), ret_type_(r_type), arg_list_(std::move(vec)), body_(body) {}

    Function() {}

    std::string getName() const {
        return name_;
    }
};




#endif