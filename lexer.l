%option noyywrap
%{
#include <iostream>
#include <string>
#include "parser.hh"
#include "location.hh"
yy::location loc;
#define YY_DECL yy::parser::symbol_type yylex()
#define yyterminate() return yy::parser::make_END_OF_FILE(loc)
YY_DECL;
# define YY_USER_ACTION  loc.columns (yyleng);

%}


identifier [[:alpha:]_][[:alnum:]_]*
string_v1 \'[^']*\'
string_v2 \"[^"]*\"


%%
"int" |
"char" |
"float" |
"bool" {return yy::parser::make_TYPE(yytext, loc);}

{identifier} { return yy::parser::make_SYMBOL(yytext, loc); }

[ \s\t] {} 
. {throw yy::parser::syntax_error
               (loc, "invalid character: " + std::string(yytext));}

%%

