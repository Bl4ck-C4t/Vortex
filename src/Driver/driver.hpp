#ifndef DRIVER_HH
# define DRIVER_HH
#include "../../precompiled/parser.hh"
#include "../../precompiled/location.hh"
#include "../Variables/vars.hpp"
#include "../Functions/Function.hpp"
#include "../Utility/RefMap.hpp"
#include "../Functions/FunctionCall.hpp"
#include "../Functions/StandardLib.hpp"
#include "../Classes/Class.hpp"
#include "../Classes/Instance.hpp"
#include <map>
#include <stack>


typedef struct yy_buffer_state *YY_BUFFER_STATE;
class Driver{
    std::string file;
  // Whether to generate parser debug traces.

    std::stack<FunctionCall> callStack_;

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  // Whether to generate scanner debug traces.

  std::string last_lines_[3] = {"", "", ""};
  rvalue last_returned_;

  yy::location location;

  bool trace_scanning = false;
  // The token's location used by the scanner.
  bool trace_parsing = false;

  bool interpretatorMode = false;
  bool returnLast_ = true;

public:
  Driver();


  int parse (const std::string& f);

  void executeFile(std::string filename);

  yy::parser createParser();

  void addLine(std::string s);

  void interpretator();

  std::string* getLastLines() const;

  void setVariable(Var&& var);

  void declareFunction(Function* f);

  void declareClass(Class&& cls);

  rvalue makeInstance(std::string className, std::vector<rvalue>&& args);

  rvalue makeVector(std::vector<rvalue>&& args);

  void callFunction(std::string name, std::vector<rvalue> args);

  void runFunc(Function& func, std::vector<rvalue>&& args);

  Var getVariable(std::string name);

  int runConditional(std::string body);

  int loop(std::string body);

  int evaluate(const char* body);

  Scope& getScope(){
      callStack_.top().getScope();
  }

  yy::location& grabLocation() {
      return location;
  }

  YY_BUFFER_STATE scan_string(const char* str);
  void revertBuffer(YY_BUFFER_STATE bp);
  yy::parser::symbol_type get_token();

  void enableParserDebugMode(){
      trace_parsing = true;
  }

  void disableParserDebugMode(){
      trace_parsing = false;
  }

  void enableLexerDebugMode(){
      trace_scanning = true;
  }

  void disableLexerDebugMode(){
      trace_scanning = false;
  }

  void enableInterpretatorMode(){
      interpretatorMode = true;
  }

  void disableInterpretatorMode(){
      interpretatorMode = false;
  }

  bool isInterpretator() const{
      return interpretatorMode;
  }

  void enableReturnPrint(){
      returnLast_ = true;
  }

  void disableReturnPrint(){
      returnLast_ = false;
  }

  bool isPrintingLastValue() const{
      return returnLast_;
  }

  rvalue getLastValue() const{
      return last_returned_;
  }

  void setLastValue(rvalue&& r){
      last_returned_ = r;
  }

  std::stack<FunctionCall>& getStack() { return callStack_; }
  // The name of the file being parsed.
  


};
#endif