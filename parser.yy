%require "3.4"
%language "c++"

%define api.value.type variant
%define api.token.constructor

%token END_OF_FILE 0
%token <std::string> TYPE SYMBOL;

%code {
  yy::parser::symbol_type yylex();
}

%%
%start result;
result:
  | result decl  { std::cout << $2 << '\n'; }
;

%type <std::string> decl;
decl: TYPE SYMBOL {$$=$1+$2;}
;

%%
namespace yy
{
  // Report an error to the user.
  auto parser::error (const std::string& msg) -> void
  {
    std::cerr<< msg << '\n';
  }
}

int main ()
{
  yy::parser parse;
  return parse ();
}
