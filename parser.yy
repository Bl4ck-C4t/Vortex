%require "3.4"
%language "c++"

%define api.value.type variant
%define api.token.constructor
%locations
%defines
%define parse.trace
%define parse.error verbose
%define api.token.prefix {TOK_}

%{
#include "../driver.hh"
%}


%code requires {
  #include <string>
  #include <any>
  #include "../Variables/vars.hpp"
  class Driver;
}

// The parsing context.
%param { Driver& drv }

%token END_OF_FILE 0
%token <Type> TYPE;
%token <std::string> SYMBOL STRING;
%token <int> INTEGER;
%token <float> FLOAT;
%token <char> CHAR;
%token <bool> BOOL;
%token
  EQUALS "="
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
  SEMICOL ";"
  ;


%code {
  yy::parser::symbol_type yylex(Driver& drv);

}


%%
%start result;
result:
  | result exp  { drv.setLastValue(std::move($2)); std::cout << drv.getLastValue() << '\n'; }
;

%type <rvalue> decl;
decl: TYPE SYMBOL "=" exp {drv.setVariable(Var($1, $2, $exp)); $$=std::move($exp);}
| SYMBOL "=" exp {drv.setVariable(Var($exp.getType(), $1, $exp)); $$=std::move($exp);}
;

%left "+" "-";
%left "*" "/";
%type <rvalue> exp;
exp: INTEGER {$$=rvalue(Type::INT, $1);}
| STRING {$$=rvalue(Type::STRING, $1);}
| FLOAT {$$=rvalue(Type::FLOAT, $1);}
| CHAR {$$=rvalue(Type::CHAR, $1);}
| BOOL {$$=rvalue(Type::BOOL, $1);}
| SYMBOL {$$=drv.getVariable($1).getValue();}
| decl
| exp "+" exp {try{$$= $1 + $3;} catch(ParserException e) {throw yy::parser::syntax_error(drv.grabLocation(), e.getMessage());}}
| exp "-" exp {try{$$= $1 - $3;} catch(ParserException e) {throw yy::parser::syntax_error(drv.grabLocation(), e.getMessage());}}
| exp "*" exp {try{$$= $1 * $3;} catch(ParserException e) {throw yy::parser::syntax_error(drv.grabLocation(), e.getMessage());}}
| exp "/" exp {try{$$= $1 / $3;} catch(ParserException e) {throw yy::parser::syntax_error(drv.grabLocation(), e.getMessage());}}

;

%%
namespace yy
{
  // Report an error to the user.
  auto parser::error (const location_type& l, const std::string& msg) -> void
  {
    std::string* arr = drv.getLastLines();
    for(int i=0; i < 3; i++){
      if(*(arr+i) != ""){
        std::cerr << i + (l.begin.line - 1) << " | " << *(arr + i) << std::endl;
      }
    }
    int offset = std::to_string(l.end.line).size() + 3 + (l.end.column) - 1;
    // divide columns by 2 to find the real region
    // pretty errors
    for(int i=0; i < offset; i++){
      std::cerr << "~";
    }
    std::cerr << "^" << '\n';
    std::cerr << l << ":" << msg << '\n';

  }
}

// int main ()
// {
//   std::string s = "-";
//   loc.initialize(&s);
//   yy::parser parse;
//   return parse ();
// }
