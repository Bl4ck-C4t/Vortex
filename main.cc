#include "driver.hh"
int main(int argc, char *argv[]){
    Driver drv;
    int res;
    for (int i = 1; i < argc; ++i)
    if (argv[i] == std::string ("-p"))
      drv.enableParserDebugMode();
    else if (argv[i] == std::string ("-s"))
      drv.enableLexerDebugMode();
    else if (!(res = drv.parse (argv[i])))
      std::cout << res << '\n';
    else
      res = 1;
  return res;
}