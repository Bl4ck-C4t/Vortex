#ifndef FUNCTIONCALL_HH
#define FUNCTIONCALL_HH
#include "Function.hpp"
#include "../Utility/RefMap.hpp"
#include "../Variables/vars.hpp"
#include "../Classes/Class.hpp"
#include <vector>
#include <string>
struct Scope{
    RefMap<std::string, Var> variables;
    RefMap<std::string, Function> functions;
    RefMap<std::string, Class> classes;
    Scope() {}
};

class FunctionCall {
    const Function& fun;
    Scope MainScope;

    public:
    FunctionCall(const Function& f): fun(f) {}

    FunctionCall(const Function& f, std::vector<rvalue>&& args): FunctionCall(f) {

        std::vector<Var> f_args = fun.getArgs();
        if(f_args.size() != args.size()){
            throw ParserException("Function '" + f.getName() + "' expects " + std::to_string(f_args.size()) + 
            " arguments, but " + std::to_string(args.size()) + " provided.");
        }

        for(int i=0; i < f_args.size(); i++){
            Var f_arg = f_args[i];
            rvalue val = args[i];
            if(f_arg.getType() != val.getType()){
                throw IncorrectTypesException("Value passed to argument '" + f_arg.getName() + "' is incorrect", 
                val.getType(), f_arg.getType());
            }
            
            f_arg.setValue(std::move(val));
            MainScope.variables[f_arg.getName()] = std::move(f_arg);
        }
    }

    void setFunctionRef(Scope& r_scope){
        MainScope.functions.setMap(&r_scope.functions);
        // MainScope.variables.setMap(&r_scope.variables);

    }
    
    void setFullRef(Scope& r_scope){
        MainScope.functions.setMap(&r_scope.functions);
        MainScope.variables.setMap(&r_scope.variables);

    }

    Scope& getScope() {
        return MainScope;
    }

    const Function& getFunc(){
        return fun;
    }

};

#endif