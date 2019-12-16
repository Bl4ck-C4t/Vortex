#ifndef VARS_HH
# define VARS_HH
#include <iostream>
#include <ostream>
#include <any>

enum struct Type { INT, STRING, CHAR, FLOAT, BOOL};

struct rvalue{
    rvalue(Type tp, std::any vl): type(tp), value(vl) {}
    rvalue() {}

    Type getType() const {
        return type;
    }

    std::any getValue() const {
        return value;
    }
    friend std::ostream& operator<<(std::ostream& o, rvalue r);
    private:
        Type type;
        std::any value;
    
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