#ifndef VARS_HH
# define VARS_HH
#include <iostream>
#include <ostream>
#include <any>
#include <exception>
// #include "../Operations/OperationExecutor.hpp"
// #include "../Operations/SumInt.hpp"
// #include "../Operations/SubInt.hpp"
// #include "../Operations/MulInt.hpp"
class OperationExecutor;
enum struct Type { INT, STRING, CHAR, FLOAT, BOOL};

class ParserException {
    std::string msg_;
    public:
        ParserException(std::string msg): msg_(msg) {}
        ParserException(): msg_("Exception is thrown") {}
        std::string getMessage() const {return msg_;}
};
class IncorrectTypesException: public ParserException {
    public:
        IncorrectTypesException(std::string msg): ParserException(msg) {}
        IncorrectTypesException(): ParserException("No such operation with those types") {}
};
class ZeroDivisionException: public ParserException {
    public:
        ZeroDivisionException(std::string msg): ParserException(msg) {}
};

class rvalue{
    Type type;
    std::any value;

    void setupOperations();
    public:
    OperationExecutor* sum_exec;
    OperationExecutor* sub_exec;
    OperationExecutor* mul_exec;
    OperationExecutor* div_exec;


    rvalue(Type tp, std::any vl): type(tp), value(vl) {setupOperations();}
    rvalue() {setupOperations();}

    Type getType() const {
        return type;
    }

    std::any getValue() const {
        return value;
    }

    template<class T>
    T getValue() const{
        return std::any_cast<T>(value);
    }

    friend std::ostream& operator<<(std::ostream& o, rvalue r);

    rvalue operator+(rvalue other);
    rvalue operator-(rvalue other);
    rvalue operator*(rvalue other);
    rvalue operator/(rvalue other);
    
    // friend rvalue operator/(rvalue other, rvalue e);
    
};

struct Var{

    Var(Type tp, std::string nm, rvalue r): var_type(tp), name(nm), value(r) {}
    Var() {}

    std::string getName() const{
        return name;
    }

    Type getType() const{
        return var_type;
    }

    rvalue getValue() const {
        return value;
    }

    void setValue(rvalue&& n_val){
        value = std::move(n_val);
        var_type = n_val.getType();
    }
    private:
        rvalue value;
        std::string name;
        Type var_type; 
        friend std::ostream& operator<<(std::ostream& o, Var& var);

};
#endif