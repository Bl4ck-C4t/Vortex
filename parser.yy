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
#include "../Variables/vars.hpp"  
%}


%code requires {
  #include <string>
  class Driver;
}

// The parsing context.
%param { Driver& drv }

%token END_OF_FILE 0
%token <std::string> TYPE SYMBOL STRING;
%token EQUALS "="
%token <int> INTEGER


%code {
  yy::parser::symbol_type yylex(Driver& drv);
}

%%
%start result;
result:
  | result decl  { std::cout << $2 << '\n'; }
;

%type <std::string> decl;
decl: TYPE SYMBOL "=" exp {drv.setVariable(Var(Type::INT, "asd", rvalue(Type::INT, $4))); $$="asd";}
;

%type <int> exp;
exp: INTEGER
;

%%
namespace yy
{
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
