#ifndef IFHPP
#define IFHPP
#include "../Functions/FunctionCall.hpp"
#include "../Driver/driver.hh"

class Conditional: public FunctionCall{
    public:
    Conditional(): FunctionCall(Function("", Type::VOID, std::vector<Var>(), ""), std::vector<rvalue>()) {}

    int perform(Driver& drv){
        setFullRef(getScope());
        auto& callStack_ = drv.getStack();
        callStack_.push(*this);
        // int res = drv.evaluate(body.c_str();
        int res = drv.evaluate(getFunc().getBody().c_str());
        callStack_.pop();
        return res;
    }
};


#endif