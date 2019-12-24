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

class FunctionNotDefined: public ParserException{
    public:
    FunctionNotDefined(std::string msg): ParserException(msg) {}
    FunctionNotDefined(): ParserException("Function not defined") {}
};

class Function: public Var{
    Type ret_type_;
    std::vector<Var> arg_list_;

   public:
    Function(std::string nm, Type r_type, std::vector<Var>&& vec, std::string body):
     ret_type_(r_type), arg_list_(std::move(vec)), Var(Type::FUNC, nm, rvalue(Type::STRING, body)) {}

    Function() {}

    std::string getBody() const {
        return getValue().getValue<std::string>();
    }

    std::vector<Var> getArgs() const{
        return arg_list_;
    }

    bool operator==(Function other){
        return other.getName() == getName() && other.ret_type_ == ret_type_ && other.arg_list_ == arg_list_;
    }

    // Function& operator=(const Function&& other){
    //     ret_type_ = other.ret_type_;
    //     arg_list_ = std::move(other.arg_list_);
    // }
};




#endif