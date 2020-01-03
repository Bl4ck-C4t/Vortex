#include <iostream>
#include <string>
#include "precompiled/parser.hh"
#include "src/Driver/driver.hh"
yy::parser::symbol_type yylex(Driver& drv);

int main(){
    Driver drv;
    while(true){
        yy::parser::symbol_type ret = yylex(drv);
        if(ret.type == 0){
            break;
        }
        std::cout << ret.type << " " << ret.value.as<std::string>() << std::endl;

    }
    return 0;
}