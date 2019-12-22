#include "vars.hpp"
#include "../Operations/OperationExecutor.hpp"
#include "../Operations/SumInt.hpp"
rvalue
rvalue::operator+(rvalue other){
    // if(other.getType() != this->getType()){
    //     throw IncorrectTypesException();
    // }
    try{
          return sum_exec->runOper(*this, other);
    }catch(IncorrectTypesException e){
        throw IncorrectTypesException("No '+' operator for those types");
    }
}

void 
rvalue::setupOperations() {
        sum_exec = new OperationExecutor();
        sum_exec->addOperation(new SumInt());
        // oe.addOperation(new SubInt());
        // oe.addOperation(new MulInt());
    }

rvalue
rvalue::operator-(rvalue other){
    if(other.getType() != this->getType()){
        throw IncorrectTypesException();
    }
    switch (other.getType())
            {
            case Type::INT:
                return rvalue(other.getType(), this->getValue<int>() - other.getValue<int>());
                break;
            case Type::CHAR:
                return rvalue(other.getType(), this->getValue<char>() - other.getValue<char>());
                break;
            case Type::FLOAT:
                return rvalue(other.getType(), this->getValue<float>() - other.getValue<float>());
                break;
            case Type::STRING:
                    throw IncorrectTypesException();                
                    break;

            case Type::BOOL:
                throw IncorrectTypesException();

            
            default:
                throw IncorrectTypesException();
            }
}