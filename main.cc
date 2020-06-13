#include "src/Driver/driver.hpp"
#include "precompiled/parser.hh"
#include "src/Variables/vars.hpp"
int main(int argc, char *argv[]){
    Driver drv;
    int res = 0;
    for (int i = 1; i < argc; ++i)
    if (argv[i] == std::string ("-p"))
      drv.enableParserDebugMode();
    else if (argv[i] == std::string ("-s"))
      drv.enableLexerDebugMode();
    else{
      try{
        if(argv[i][0] == '-'){
          drv.interpretator();
        }
        else{
          drv.parse(argv[i]);
        }
      }
      catch(ParserException p){
        auto par = drv.createParser();
        par.error(drv.grabLocation(), p.getMessage());
        res = 1;
      }
      // drv.parse("-");
      
    }
  return res;
}