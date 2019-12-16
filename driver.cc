#include "driver.hh"
#include <iomanip>
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
Driver::setVariable(Var&& var){
  std::cout << "setting variable" << std::endl;
  if(var.getType() != var.getValue().getType()){
    throw yy::parser::syntax_error(location, "Incorrect type");
  }
  variables_[var.getName()] = std::move(var);
}

Var 
Driver::getVariable(std::string name){
    if(variables_.count(name) == 0){
        throw yy::parser::syntax_error(location, "No variable with name '" + name + "'");
    }
    std::cout << "getting variable" << std::endl;
    return variables_[name];
}


std::ostream& operator<<(std::ostream& o, rvalue r){
    try{
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
                o << std::any_cast<bool>(r.getValue());
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


