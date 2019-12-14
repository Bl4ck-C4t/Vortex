%option noyywrap
%{
#include <iostream>
#include <string>
#include <string.h>
#include "parser.hh"
#include "location.hh"
#include "../driver.hh"
#define YY_DECL yy::parser::symbol_type yylex(Driver& drv)
#define yyterminate() return yy::parser::make_END_OF_FILE(loc)
YY_DECL;
# define YY_USER_ACTION  loc.columns (yyleng);
%}


identifier [[:alpha:]_][[:alnum:]_]*
string_v1 \'[^']*\'
string_v2 \"[^"]*\"


%%

%{
    yy::location& loc = drv.grabLocation();
    if(drv.isInterpretator()){
          std::cout << "> ";
    }
%}

\n+        loc.lines (yyleng); loc.step ();
"int" |
"char" |
"float" |
"bool" {return yy::parser::make_TYPE(yytext, loc);}

"=" {return yy::parser::make_EQUALS(loc);}

[0-9]+ {return yy::parser::make_INTEGER(atoi(yytext), loc);}

{identifier} { return yy::parser::make_SYMBOL(yytext, loc); }
{string_v1} |
{string_v2} {return yy::parser::make_STRING(yytext, loc);}
[ \s\t]+ {loc.step();} 
. {throw yy::parser::syntax_error
               (loc, "invalid character: " + std::string(yytext));}

%%

void
Driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-")
    yyin = stdin;
  else if (!(yyin = fopen (file.c_str (), "r")))
    {
      std::cerr << "cannot open " << file << ": " << strerror(errno) << '\n';
      exit (EXIT_FAILURE);
    }
}

void
Driver::scan_end ()
{
  fclose (yyin);
}

void
Driver::scan_string(const char* str){
     auto bp = yy_scan_string(str);
     yy_switch_to_buffer(bp);
}

yy::parser::symbol_type 
Driver::get_token(){
  return yylex(*this);
}