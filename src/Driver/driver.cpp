#include "driver.hpp"
#include <iomanip>
#include <any>
#include <iostream>
#include <sstream>
#include <fstream>
#include "../Classes/Instance.hpp"

template<class T>
void shiftUp(T* arr, int elements){
    for(int i=0; i < elements-2; i++){
        arr[i] = arr[i+1];
    }
}

Driver::Driver() {
    Function f = Function("main", Type::VOID, std::vector<Var>(), "");
    FunctionCall call = FunctionCall(f);
    StdLib lib(*this);
    for(int i = 0; i < lib.classes.size(); i++) {
        Class cls = lib.classes[i];
        call.getScope().classes[cls.getName()] = cls;
    }

    callStack_.push(std::move(call));
}

int
Driver::evaluate(const char* body){
    auto bp = scan_string(body);
    auto parser = createParser();
    parser.set_debug_level (trace_parsing);

    int res = parser();
    revertBuffer(bp);
    return res;
}

int 
Driver::parse(const std::string& f){
  file = f;
  location.initialize (&file);
  scan_begin ();
  yy::parser parse (*this);
  parse.set_debug_level (trace_parsing);
  int res = parse ();
  scan_end ();
  return res;
}

void 
Driver::executeFile(std::string filename){
    std::ifstream t(filename);
    std::stringstream buffer;
    buffer << t.rdbuf();
    evaluate(buffer.str().c_str());
}


void 
Driver::interpretator(){
    std::string line;
    file = "-";
    int res;
    do{
        location = yy::location();
        location.initialize ();
        std::cout << "> ";
        std::getline(std::cin, line);
        this->scan_string(line.c_str());
        // this->parse("-");
        yy::parser parse (*this);
        parse.set_debug_level (trace_parsing);
        try{
            res = parse ();
        } catch(ParserException e){
            parse.error(location, e.getMessage());
        }

    }while(1);
}

yy::parser 
Driver::createParser(){
    location = yy::location();
    location.initialize ();
    return yy::parser(*this);

    // parse.set_debug_level (trace_parsing);
    // return yy::parser(parse);
}

void
Driver::declareFunction(Function&& f){
    auto& functions = getScope().functions;
    if(functions.contains(f.getName())){
        throw FunctionDefinedException("Function '" + f.getName() + "' Already defined");
    }
    // std::string full_name = f.getName() + " " + ""
    // rm[f.getName()];
    functions[f.getName()] = std::move(f);
}



void 
Driver::callFunction(std::string name, std::vector<rvalue> args){
    auto& functions = getScope().functions;

    if(!functions.contains(name)){
        throw FunctionNotDefined("Function '" + name + "' does not exist.");
    }
    const Function& func = functions.get(name);
    FunctionCall call = FunctionCall(func, std::move(args));
    call.setFunctionRef(getScope());
    callStack_.push(call);
    evaluate(func.getBody().c_str());
    if(getLastValue().getType() != func.getType()){
        throw IncorrectTypesException("The type returned from function '" + func.getName() + "' is incorrect", 
        func.getType(), getLastValue().getType());
    }
    callStack_.pop();
    // call
   
    // call
}

void 
Driver::runFunc(Function& func, std::vector<rvalue>&& args){
    FunctionCall call = FunctionCall(func, std::move(args));
    call.setFunctionRef(getScope());
    callStack_.push(call);
    evaluate(func.getBody().c_str());
    if(getLastValue().getType() != func.getType()){
        throw IncorrectTypesException("The type returned from function '" + func.getName() + "' is incorrect", 
        func.getType(), getLastValue().getType());
    }
    callStack_.pop();
}

int 
Driver::runConditional(std::string body){
    Function f = Function("", Type::VOID, std::vector<Var>(), "");
    FunctionCall call = FunctionCall(f, std::vector<rvalue>());
    call.setFullRef(getScope());
    callStack_.push(call);
    int res = evaluate(body.c_str());
    callStack_.pop();
    return res;

}

int
Driver::loop(std::string body){ // a = 3; loop { a = a + 2; if(a == 9) { break; } }
    Function f = Function("", Type::VOID, std::vector<Var>(), "");
    FunctionCall call = FunctionCall(f, std::vector<rvalue>());
    call.setFullRef(getScope());
    callStack_.push(call);
    int res = evaluate(body.c_str());
    callStack_.pop();
    return res;
}

rvalue 
Driver::makeVector(std::vector<rvalue>&& args){
    // std::any h = args;
    std::vector<rvalue> method_args =  {rvalue(Type::OBJECT, args)};
    Class& vec_class = callStack_.top().getScope().classes.get("vector");
    Instance vector_instance(vec_class);   
    vector_instance.callMethod("construct",std::move(method_args), *this);
    return rvalue(Type::OBJECT, vector_instance);
}
// if (true) { 20 }
// s


void 
Driver::setVariable(Var&& var){
//   std::cout << "setting variable" << std::endl;
  const rvalue& val = var.getValue();
  auto& variables = getScope().variables;
  if(var.getType() != val.getType()){
      location.end.column--;
    throw IncorrectTypesException("Value type incorrect", var.getType(), val.getType());
  }
  if(variables.contains(var.getName())){
      variables.get(var.getName()).setValue(std::move(var.getValue()));
  }
  variables[var.getName()] = std::move(var);
}

Var 
Driver::getVariable(std::string name){
    auto& variables = getScope().variables;
    if(!variables.contains(name)){
        throw yy::parser::syntax_error(location, "No variable with name '" + name + "'");
    }
    // std::cout << "getting variable" << std::endl;
    return variables.get(name);
}

void 
Driver::addLine(std::string s){
    // shiftUp<std::string>(last_lines_, 3);
    // std::cout << "Ran with " << s << std::endl; 
    last_lines_[0] = last_lines_[1];
    last_lines_[1] = last_lines_[2];
    last_lines_[2] = s;
}

std::string*
Driver::getLastLines() const{
    return (std::string*)last_lines_;
}




std::ostream& operator<<(std::ostream& o, rvalue r){
    try{
        std::string res;
        switch (r.getType())
            {
            case Type::INT:
                o << std::any_cast<int>(r.getValue());
                break;

            case Type::CHAR:
                o << std::any_cast<char>(r.getValue());
                break;

            case Type::STRING:
                o << std::any_cast<std::string>(r.getValue());
                break;

            case Type::FLOAT:
                o << std::any_cast<float>(r.getValue());
                break;

            case Type::BOOL:
                res = std::any_cast<bool>(r.getValue()) ? "true" : "false";
                o << res;
                break;
            case Type::OBJECT:
                //res = std::any_cast<bool>(r.getValue()) ? "true" : "false";
                res = "object";
                o << res;
                break;
            
            default:
                break;
            }
    }catch(std::bad_any_cast e){
        o << "Bad cast";
    }
    return o;
}

std::ostream& operator<<(std::ostream& o, Var& var){
    o  << var.getName() 
    << " : " << var.value;
    return o;
}




