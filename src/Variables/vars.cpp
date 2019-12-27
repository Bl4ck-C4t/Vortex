#include "vars.hpp"
#include "../Operations/OperationExecutor.hpp"
#include "../Operations/IntOperations.hpp"
#include "../Operations/SumString.hpp"
#include "../Operations/FloatOperations.hpp"


rvalue
rvalue::operator+(rvalue other){
    try{
          return sum_exec->runOper(*this, other);
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("+", getType(), other.getType());
    }
}

rvalue
rvalue::operator-(rvalue other){
    try{
          return sub_exec->runOper(*this, other);
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("-", getType(), other.getType());
    }
}

rvalue 
rvalue::operator-(){
    return sub_exec->runOper(rvalue(Type::INT, 0), *this);
}


rvalue
rvalue::operator*(rvalue other){
    try{
          return mul_exec->runOper(*this, other);
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("*", getType(), other.getType());
    }
}

rvalue
rvalue::operator/(rvalue other){
    try{
          return div_exec->runOper(*this, other);
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("/", getType(), other.getType());
    }
}

rvalue 
rvalue::pow(rvalue other){
    try{
          return pow_exec->runOper(*this, other);
    }catch(IncorrectTypesException e){
        throw NoSuchOperation("**", getType(), other.getType());
    }
}



void 
rvalue::setupOperations() {
        sum_exec = new OperationExecutor();
        sub_exec = new OperationExecutor();
        mul_exec = new OperationExecutor();
        div_exec = new OperationExecutor();
        pow_exec = new OperationExecutor();
        
        sum_exec->addOperation(new SumInt());
        sum_exec->addOperation(new SumString());
        sum_exec->addOperation(new FloatSum());

        sub_exec->addOperation(new SubInt());
        sub_exec->addOperation(new FloatSub());
        sub_exec->addOperation(new SubIntF());

        mul_exec->addOperation(new MulInt());
        mul_exec->addOperation(new FloatMul());

        div_exec->addOperation(new DivInt());
        div_exec->addOperation(new FloatDiv());

        pow_exec->addOperation(new PowInt());
        pow_exec->addOperation(new FloatPow());

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