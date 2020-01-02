#include "vars.hpp"
#include "../Operations/OperationExecutor.hpp"
#include "../Operations/IntOperations.hpp"
#include "../Operations/SumString.hpp"
#include "../Operations/FloatOperations.hpp"
#include "../Operations/BoolOperations.hpp"


rvalue
rvalue::operator+(rvalue other){
    try{
          return operations->runOper(*this, other, "+");
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("+", getType(), other.getType());
    }
}

rvalue
rvalue::operator-(rvalue other){
    try{
          return operations->runOper(*this, other, "-");
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("-", getType(), other.getType());
    }
}

rvalue 
rvalue::operator-(){
    return operations->runOper(rvalue(Type::INT, 0), *this, "-");
}


rvalue
rvalue::operator*(rvalue other){
    try{
          return operations->runOper(*this, other, "*");
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("*", getType(), other.getType());
    }
}

rvalue
rvalue::operator/(rvalue other){
    try{
          return operations->runOper(*this, other, "/");
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("/", getType(), other.getType());
    }
}

rvalue 
rvalue::pow(rvalue other){
    try{
          return operations->runOper(*this, other, "**");
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("**", getType(), other.getType());
    }
}

rvalue 
rvalue::operator==(rvalue other){
    try{
          return operations->runOper(*this, other, "==");
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("==", getType(), other.getType());
    }
}

rvalue
rvalue::operator>(rvalue other){
    try{
          return operations->runOper(*this, other, ">");
    }catch(IncorrectTypesException e){
        throw NoSuchOperation(">", getType(), other.getType());
    }
}

rvalue
rvalue::operator<(rvalue other){
    try{
          return operations->runOper(*this, other, "<");
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("<", getType(), other.getType());
    }
}

rvalue
rvalue::operator>=(rvalue other){
    try{
          bool res1 = operations->runOper(*this, other, ">").getValue<bool>();
          bool res2 = operations->runOper(*this, other, "==").getValue<bool>();

          return rvalue(Type::BOOL, res1 || res2);

    }catch(IncorrectTypesException e){
        throw NoSuchOperation(">=", getType(), other.getType());
    }
}

rvalue
rvalue::operator<=(rvalue other){
    try{
          bool res1 = operations->runOper(*this, other, "<").getValue<bool>();
          bool res2 = operations->runOper(*this, other, "==").getValue<bool>();

          return rvalue(Type::BOOL, res1 || res2);    
        }
        catch(IncorrectTypesException e){
            throw NoSuchOperation("<=", getType(), other.getType());
        }
}

rvalue
rvalue::operator!=(rvalue other){
    try{
          rvalue res = operations->runOper(*this, other, "==");
          if(res.getValue<bool>()){
                return rvalue(Type::BOOL, false);
          }
          else{
                return rvalue(Type::BOOL, true);
          }
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("!=", getType(), other.getType());
    }
}






void 
rvalue::setupOperations() {
        
        operations = new OperationExecutor();
        
        operations->addOperation(new SumInt());
        operations->addOperation(new SumString());
        operations->addOperation(new FloatSum());

        operations->addOperation(new SubInt());
        operations->addOperation(new FloatSub());
        operations->addOperation(new SubIntF());

        operations->addOperation(new MulInt());
        operations->addOperation(new FloatMul());

        operations->addOperation(new DivInt());
        operations->addOperation(new FloatDiv());

        operations->addOperation(new PowInt());
        operations->addOperation(new FloatPow());

        operations->addOperation(new CompareNumsBool());
        operations->addOperation(new GreaterThanBoolNum());
        operations->addOperation(new LessThanBoolNum());

        operations->addOperation(new CompareBooleans());

        operations->addOperation(new CompareString());
        operations->addOperation(new GreaterThanStringBool());
        operations->addOperation(new LessThenStringBool());


        

}

std::string typeToString(Type tp){
    switch (tp)
    {
    case Type::INT:
        return "int";
    case Type::STRING:
        return "string";
    case Type::CHAR:
        return "char";
    case Type::FLOAT:
        return "float";
    case Type::BOOL:
        return "bool";
    case Type::VOID:
        return "void";
    case Type::FUNC:
        return "<function>";
    
    default:
        return "<unknown>";
    }
}