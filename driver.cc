#include "driver.hh"

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
Driver::setVariable(Var var){
  std::cout << "setting variable" << std::endl;
}

Var 
Driver::getVariable(std::string name){
    std::cout << "getting variable" << std::endl;
}


std::ostream& operator<<(std::ostream& o, rvalue r){
    try{
        switch (r.getType())
            {
            case Type::INT:
                o << std::any_cast<char>(r.getValue());
                break;
                
            case Type::CHAR:
                o << std::any_cast<char>(r.getValue());
                break;
            
            default:
                break;
            }
    }catch(std::bad_any_cast e){
        std::cout << "Bad cast";
    }
    return o;
}

std::ostream& operator<<(std::ostream& o, Var& var){
    o  << var.getName() 
    << " : " << var.value;
    return o;
}


