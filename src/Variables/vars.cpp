#include "vars.hpp"
#include "../Operations/OperationExecutor.hpp"
#include "../Operations/IntOperations.hpp"
#include "../Operations/SumString.hpp"
#include "../Operations/FloatOperations.hpp"


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
          return operations->runOper(*this, other, "*");
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("==", getType(), other.getType());
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