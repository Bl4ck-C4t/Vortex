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
#include "../src/Driver/driver.hh"
%}


%code requires {
  #include <string>
  #include <any>
  #include <vector>
  #include "../src/Variables/vars.hpp"
  #include "../src/Functions/Function.hpp"
  class Driver;
}

// The parsing context.
%param { Driver& drv }

%token END_OF_FILE 0
%token <Type> TYPE;
%token <std::string> SYMBOL STRING BODY;
%token <int> INTEGER;
%token <float> FLOAT;
%token <char> CHAR;
%token <bool> BOOL;
%token
  COMPARE "=="
  GREATER ">"
  LESS "<"
  DIFFERENT "!="
  GREATEREQUAL ">="
  SMALLEREQUAL "<="
  EQUALS "="
  MINUS   "-"
  PLUS    "+"
  STAR    "*"
  SLASH   "/"
  COMMA   ","
  LPAREN  "("
  RPAREN  ")"
  SEMICOL ";"
  FUNC "fn"
  RETSIGN "->"
  RET "ret"
  ;


%code {
  yy::parser::symbol_type yylex(Driver& drv);

}


%%
%start result;
result:
  %empty {}
  | result clause  { 
    if(!$2.isStatement()) {
      drv.setLastValue(std::move($2)); if(drv.isPrintingLastValue()) std::cout << ">> " << drv.getLastValue() << '\n';
    }
  }
  | result "ret" exp {drv.setLastValue(std::move($3)); return 0;}
  | result "ret" ";" {drv.setLastValue(std::move(rvalue()));return 0;}
;

%type <rvalue> clause;
clause: exp
| statement {$$=rvalue();}



statement:
  "fn" SYMBOL "(" args_d ")" "->" TYPE BODY[body] {drv.declareFunction(Function($2, $7, std::move($args_d), $body));}

%type <std::vector<Var>> args_d;
args_d:
%empty {}
|  arg_d {$$.push_back($arg_d);}
| args_d "," arg_d {$$=$1; $$.push_back($arg_d); }

%type <Var> arg_d;
arg_d: TYPE SYMBOL {$$=Var($1, $2);}

%type <std::vector<rvalue>> args;
args:
%empty {}
| arg {$$.push_back($arg);}
| args "," arg {$$=$1; $$.push_back($arg);}

%type <rvalue> arg;
arg: exp

%type <rvalue> decl;
decl: TYPE SYMBOL "=" exp ";" {drv.setVariable(Var($1, $2, $exp)); $$=std::move($exp);}
| SYMBOL "=" exp ";" {drv.setVariable(Var($exp.getType(), $1, $exp)); $$=std::move($exp);}
;

%left "+" "-";
%left "*" "/";
%precedence NEG;

%type <rvalue> exp;
exp: INTEGER {$$=rvalue(Type::INT, $1);}
| STRING {$$=rvalue(Type::STRING, $1);}
| FLOAT {$$=rvalue(Type::FLOAT, $1);}
| CHAR {$$=rvalue(Type::CHAR, $1);}
| BOOL {$$=rvalue(Type::BOOL, $1);}
| SYMBOL {$$=drv.getVariable($1).getValue();}
| decl
| exp[base] "*" "*" exp[power] {$$=$base.pow($power);}
| exp "+" exp {$$= $1 + $3;}
| exp "-" exp {$$= $1 - $3;} 
| exp "*" exp {$$= $1 * $3;} 
| exp "/" exp {$$= $1 / $3;}
| exp "==" exp {$$=$1 == $3;}
| "-" exp %prec NEG {$$= -$2;}
| SYMBOL "(" args ")" {drv.callFunction($1, std::move($args)); $$=drv.getLastValue();}


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