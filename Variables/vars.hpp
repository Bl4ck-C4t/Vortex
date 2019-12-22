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

class IncorrectTypesException {
    std::string msg_;
    public:
        IncorrectTypesException(std::string msg): msg_(msg) {}
        IncorrectTypesException(): msg_("No such operation with those types") {}
        std::string getMessage() const {return msg_;}
};
class rvalue{
    Type type;
    std::any value;

    void setupOperations();
    public:
    OperationExecutor* sum_exec;

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