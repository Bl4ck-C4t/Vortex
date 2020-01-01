#ifndef OPERATION_EXEC_HH
#define OPERATION_EXEC_HH
#include "Operation.hpp"
#include <vector>
// class NotFound {};


class OperationExecutor{
    std::vector<Operation*> operations_;
    public:
    OperationExecutor() {}

    void addOperation(Operation* oper){
        operations_.push_back(oper);
    }

    rvalue runOper(rvalue lhs, rvalue rhs, std::string oper) const{
        for(auto it = operations_.begin(); it != operations_.end(); it++ ){
            if((*it)->match(lhs, rhs, oper)){
                return (*it)->execute(lhs, rhs);
            }
        }
        // throw NotFound();
        throw IncorrectTypesException();
    }
};
#endif
