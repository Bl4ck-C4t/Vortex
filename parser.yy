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
%token
  EQUALS "="
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  LPAREN  "("
  RPAREN  ")"
  ;


%code {
  yy::parser::symbol_type yylex(Driver& drv);
}

%%
%start result;
result:
  | result exp  { std::cout << $2 << '\n'; }
;

%type <rvalue> decl;
decl: TYPE SYMBOL "=" exp {drv.setVariable(Var($1, $2, $exp)); $$=std::move($exp);}
;

%left "+" "-";
%left "*" "/";
%type <rvalue> exp;
exp: INTEGER {$$=rvalue(Type::INT, $1);}
| STRING {$$=rvalue(Type::STRING, $1);}
| decl
| SYMBOL {$$=drv.getVariable($1).getValue();}
;

%%
namespace yy
{
    enum struct Type;
  // Report an error to the user.
  auto parser::error (const location_type& l, const std::string& msg) -> void
  {
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
