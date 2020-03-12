#include <iostream>
#include <string>
#include "precompiled/parser.hh"
#include "src/Driver/driver.hpp"
yy::parser::symbol_type yylex(Driver& drv);

int main(){
    Driver drv;
    while(true){
        std::cout << "Scanning: ";
        yy::parser::symbol_type ret = yylex(drv);
        switch(ret.type){
            case 0:
                exit(0);
            case 3:
                std::cout << "TYPE" << std::endl;
                break;
            case 4:
                std::cout << "SYMBOL: " << ret.value.as<std::string>() << std::endl;
                break;

            case 28:
                std::cout << "{" << std::endl;
                break;

            case 29:
                std::cout << "}" << std::endl;
                break;

            case 30:
                std::cout << ";" << std::endl;
                break;

            case 40:
                std::cout << "class" << std::endl;
                break;

            case 32:
                std::cout << "fn" << std::endl;
                break;
            
            case 24:
                std::cout << "(" << std::endl;
                break;

            case 25:
                std::cout << ")" << std::endl;
                break;
            
            case 33:
                std::cout << "->" << std::endl;
                break;

            case 23:
                std::cout << "," << std::endl;
                break;
            
            case 6:
                std::cout << "BODY" << std::endl;
                break;

            default:
                std::cout << ret.type << std::endl;

        }

    }
    return 0;
}