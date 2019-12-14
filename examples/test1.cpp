
#include <iostream>
#include <ostream>
#include <any>
using namespace std;

enum struct Type { INT, STRING, CHAR, DOUBLE};

struct rvalue{
    rvalue(Type tp, any vl): type(tp), value(vl) {}

    Type getType() const {
        return type;
    }

    any getValue() const {
        return value;
    }
    private:
        Type type;
        any value;
    
};

struct Var{

    Var(Type tp, string nm, rvalue r): var_type(tp), name(nm), value(r) {}
    
    string getName() const{
        return name;
    }

    Type getType() const{
        return var_type;
    }

    any getValue() const {
        return value.getValue();
    }

    void setValue(rvalue&& n_val){
        value = move(n_val);
        var_type = n_val.getType();
    }
    private:
        rvalue value;
        string name;
        Type var_type; 
        friend ostream& operator<<(ostream& o, Var& var);

};

ostream& operator<<(ostream& o, rvalue r){
    try{
        switch (r.getType())
            {
            case Type::INT:
                o << any_cast<char>(r.getValue());
                break;
                
            case Type::CHAR:
                o << any_cast<char>(r.getValue());
                break;
            
            default:
                break;
            }
    }catch(bad_any_cast e){
        cout << "Bad cast";
    }
    return o;
}

ostream& operator<<(ostream& o, Var& var){
    o  << var.getName() 
    << " : " << var.value;
    return o;
}

int main(int argc, char const *argv[])
{
    // cout << v1 << endl;
    // cout << v1 << endl;

    Var v1(Type::INT, "var1", rvalue(Type::INT, 6));
    cout << v1 << endl;
    v1.setValue(rvalue(Type::CHAR, 'c'));
    rvalue r1 = rvalue(Type::CHAR, 'h');
    v1.setValue(move(r1));
    cout << v1 << endl;
    // cout << r1 << endl;

    // any f = 0.5;
    // bool r = f.type() == typeid(double);
    // cout << any_cast<double>(f) << endl;
    // f.emplace<string>("asd");
    // cout << any_cast<string>(f);

  
    return 0;
}
