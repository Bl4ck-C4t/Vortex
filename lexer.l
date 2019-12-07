%option noyywrap
%{
#include <iostream>
#include "parser.hh"
#include "location.hh"
#define YY_DECL yy::parser::symbol_type yylex()
YY_DECL;
%}

identifier [[:alpha:]_][[:alnum:]_]*
string_v1 \'[^']*\'
string_v2 \"[^"]*\"


%%
"int" |
"char" |
"float" |
"bool" {return yy::parser::make_TYPE(yytext);}

{identifier} { return yy::parser::make_SYMBOL(yytext); }

[ \s\t] {} 


%%

