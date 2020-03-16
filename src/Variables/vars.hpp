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
enum struct Type { INT, STRING, CHAR, FLOAT, BOOL, VOID, FUNC, OBJECT, UNKNOWN};

std::string typeToString(Type tp);

class ParserException: public std::exception {
    std::string msg_;
    public:
        ParserException(std::string msg): msg_(msg) {}
        ParserException(): msg_("Exception is thrown") {}
        std::string getMessage() const {return msg_;}
        const char* what() const noexcept {
            return getMessage().c_str();
        }
};
class IncorrectTypesException: public ParserException {
    public:
        IncorrectTypesException(std::string msg): ParserException(msg) {}
        IncorrectTypesException(std::string msg, const Type& expected, const Type& actual):
        ParserException(msg + ":\n      expected '" + typeToString(expected) + "', got '" + typeToString(actual) + "'") {}
        IncorrectTypesException(): ParserException("No such operation with those types") {}
};

class NoSuchOperation: public ParserException{
 public:
        NoSuchOperation(std::string msg): ParserException(msg) {}
        NoSuchOperation(std::string operation, const Type& lhs, const Type& rhs):
        ParserException("No '" + operation + "' operator for " + typeToString(lhs) + " " + operation + " " + typeToString(rhs)) {}
        NoSuchOperation(): ParserException("No such operation with those types") {}
};


class ZeroDivisionException: public ParserException {
    public:
        ZeroDivisionException(std::string msg): ParserException(msg) {}
};

class rvalue{
    Type type;
    std::any value;

    public:

    static void setupOperations();
    static OperationExecutor* operations;

    rvalue(Type tp, std::any vl): type(tp), value(vl) {}
    rvalue(): type(Type::VOID), value(42) {}

    Type getType() const {
        return type;
    }

    std::any getValue() const {
        return value;
    }

    bool isStatement() const { 
        return type == Type::VOID; 
    }

    template<class T>
    T getValue() const{
        return std::any_cast<T>(value);
    }

    void setValue(std::any val){
        value = val;
    }

    void setValue(Type tp, std::any val){
        value = val;
        type = tp;
    }

    void setType(Type tp){
        type = tp;
    }

    friend std::ostream& operator<<(std::ostream& o, rvalue r);

    rvalue operator+(rvalue other);
    rvalue operator-(rvalue other);
    rvalue operator-();
    rvalue operator*(rvalue other);
    rvalue operator/(rvalue other);
    rvalue operator==(rvalue other);
    rvalue operator>(rvalue other);
    rvalue operator<(rvalue other);
    rvalue operator>=(rvalue other);
    rvalue operator<=(rvalue other);
    rvalue operator!=(rvalue other);

    rvalue pow(rvalue other);
    
    // friend rvalue operator/(rvalue other, rvalue e);
    
};

struct Var{

    Var(Type tp, std::string nm, rvalue r): var_type(tp), name(nm), value(r) {}
    Var(Type tp, std::string nm): var_type(tp), name(nm) {}
    Var(std::string nm): name(nm) {}

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

    template<class T>
    T getValue() const{
        return value.getValue<T>();
    }

    void setValue(rvalue&& n_val){
        value = std::move(n_val);
        // var_type = value.getType();
    }

    void setType(Type tp){
        var_type = tp;
    }

    void setValue(Type tp, std::any n_val){
        value.setValue(tp, std::move(n_val));
        var_type = tp;
    }

    bool operator==(const Var other) const{
        return other.getName() == name && other.getType() == var_type;
    }
    
    private:
        rvalue value;
        std::string name;
        Type var_type = Type::UNKNOWN; 
        friend std::ostream& operator<<(std::ostream& o, Var& var);

};


#endif