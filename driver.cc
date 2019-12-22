#include "driver.hh"
#include <iomanip>
#include <any>

template<class T>
void shiftUp(T* arr, int elements){
    for(int i=0; i < elements-2; i++){
        arr[i] = arr[i+1];
    }
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
        res = parse ();

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
Driver::setVariable(Var&& var){
//   std::cout << "setting variable" << std::endl;
  const rvalue& val = var.getValue();
  if(var.getType() != val.getType()){
    //   int sz = std::any_cast<std::string>(val.getValue()).size();
      location.end.column--;
    throw yy::parser::syntax_error(location, "Incorrect type");
  }
  variables_[var.getName()] = std::move(var);
}

Var 
Driver::getVariable(std::string name){
    if(variables_.count(name) == 0){
        throw yy::parser::syntax_error(location, "No variable with name '" + name + "'");
    }
    // std::cout << "getting variable" << std::endl;
    return variables_[name];
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




