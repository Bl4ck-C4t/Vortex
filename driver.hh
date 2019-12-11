#ifndef DRIVER_HH
# define DRIVER_HH
#include "precompiled/parser.hh"
#include "precompiled/location.hh"


class Driver{
    std::string file;
  // Whether to generate parser debug traces.
  bool trace_parsing = false;

  // Handling the scanner.
  void scan_begin ();
  void scan_end ();
  // Whether to generate scanner debug traces.
  bool trace_scanning = false;
  // The token's location used by the scanner.
  yy::location location;

  bool interpretatorMode = false;

public:
  int parse (const std::string& f);
  yy::location& grabLocation() {
      return location;
  }

  void scan_string(const char* str);
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
  // The name of the file being parsed.
  


};
#endif