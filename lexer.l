%option noyywrap
%{
#include <iostream>
#include <sstream>
#include <istream>
#include <ostream>
#include "parser.hpp"
using namespace std;
using token = yy::parser::token;
%}

%%
int |
char |
float |
bool {return token::TYPE;}

[[:alpha:]_][[:alnum:]_]* { return token::SYMBOL; }

[ \s\t] {} 
. {yyterminate();}

%%

// int main(){
//     istringstream i_str("int asd int");
//     ostringstream o_str;
//     istream in(i_str.rdbuf());
//     ostream out_s(o_str.rdbuf());
//     yyFlexLexer scanner(&in, &out_s);
//     scanner.yylex();
//     cout << "OUTPUT:" << o_str.str() << endl;
// }