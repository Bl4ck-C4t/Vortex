%option noyywrap
%{
#include <iostream>
#include <string>
#include <string.h>
#include "parser.hh"
#include "location.hh"
#include "../src/Driver/driver.hh"
#include "../src/Variables/vars.hpp"  
#define YY_DECL yy::parser::symbol_type yylex(Driver& drv)
#define yyterminate() return yy::parser::make_END_OF_FILE(loc)
YY_DECL;
// #define YY_USER_ACTION loc.columns (yyleng);
bool stob(std::string s);
%}


identifier [[:alpha:]_][[:alnum:]_]*
string_v1 \'[^']*\'
string_v2 \"[^"]*\"
char \'.?\'
bool true|false
float [0-9]+\.([0-9]+)?
path (([[:alnum:]_\/\.]+)?\/)*([[:alnum:]_]+\.vx)

%x BODY_S

%{
  int brackets = 0;
  std::string body = "";
%}
%%

%{
    yy::location& loc = drv.grabLocation();
   
    loc.columns (yyleng);
    // loc.columns (yyleng);
%}
^.+$       {drv.addLine(yytext);REJECT;}
\n+        {loc.lines (yyleng); loc.step (); }
"int"      return yy::parser::make_TYPE   (Type::INT, loc);
"string"   return yy::parser::make_TYPE   (Type::STRING, loc);
"char"     return yy::parser::make_TYPE   (Type::CHAR, loc);
"float"    return yy::parser::make_TYPE   (Type::FLOAT, loc);
"bool"     return yy::parser::make_TYPE   (Type::BOOL, loc);
"void"     return yy::parser::make_TYPE   (Type::VOID, loc);

"if"       return yy::parser::make_IF              (loc);
"else"     return yy::parser::make_ELSE            (loc);
"=="       return yy::parser::make_COMPARE         (loc);
">"        return yy::parser::make_GREATER         (loc);
"<"        return yy::parser::make_LESS            (loc);
">="       return yy::parser::make_GREATEREQUAL    (loc);
"<="       return yy::parser::make_SMALLEREQUAL    (loc);
"!="       return yy::parser::make_DIFFERENT       (loc);

"-"        return yy::parser::make_MINUS           (loc);
"+"        return yy::parser::make_PLUS            (loc);
"*"        return yy::parser::make_STAR            (loc);
"/"        return yy::parser::make_SLASH           (loc);
"("        return yy::parser::make_LPAREN          (loc);
")"        return yy::parser::make_RPAREN          (loc);
"="        return yy::parser::make_EQUALS          (loc);
";"        return yy::parser::make_SEMICOL         (loc);
"fn"       return yy::parser::make_FUNC            (loc);
"->"       return yy::parser::make_RETSIGN         (loc);  
","        return yy::parser::make_COMMA           (loc);  
"ret"      return yy::parser::make_RET             (loc);
"import"   return yy::parser::make_IMPORT          (loc);
"loop"     return yy::parser::make_LOOP            (loc);
"break"    return yy::parser::make_BREAK           (loc);



"{"        brackets=1;body=""; BEGIN(BODY_S); return yy::parser::make_LCURLY(loc);
<BODY_S>[^\}]*  { 
  body += yytext;
  for(int i=0; i < yyleng; i++) { 
       if(yytext[i] == '{') { brackets++; }
       
  }
  brackets--; 
  if(brackets == 0){
    return yy::parser::make_BODY(body, loc);
  }
}
<BODY_S>"}" if(brackets == 0) { BEGIN(INITIAL); return yy::parser::make_RCURLY(loc);} else{ body += "}"; } 

{path} { return yy::parser::make_FILEPATH(yytext, loc); }


{bool} return yy::parser::make_BOOL(stob(yytext), loc);
{char} return yy::parser::make_CHAR(yytext[1], loc);
{float} return yy::parser::make_FLOAT(atof(yytext), loc);
[0-9]+ return yy::parser::make_INTEGER(atoi(yytext), loc);

{string_v1} |
{string_v2} { /* " help \" me \" from " */
  if(yytext[yyleng-2] == '\\'){
    yyless(yyleng-1);
    yymore();
  }else{
    std::string text = std::string(yytext);
    return yy::parser::make_STRING(text.substr(1,yyleng-2), loc);
  }
  
}

{identifier} { return yy::parser::make_SYMBOL(yytext, loc); }


[ \t]+ {loc.step();} 
. {throw yy::parser::syntax_error
               (loc, "invalid character: " + std::string(yytext));}

%%
// "{}"       return yy::parser::make_BODY   ("", loc);
// fn asd() -> int { if(true) { ret 5; } ret 7;}
// fn tes() -> int { 10 }

bool
stob(std::string s){
  if(s == "true"){
      return true;
  }
  else if(s == "false"){
      return false;
  }
  throw std::exception();
}

void
Driver::scan_begin ()
{
  yy_flex_debug = trace_scanning;
  if (file.empty () || file == "-"){
    yyin = stdin;
    interpretatorMode = true;
  }
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

YY_BUFFER_STATE
Driver::scan_string(const char* str){
  auto curr = YY_CURRENT_BUFFER;
     auto bp = yy_scan_string(str);
     yy_switch_to_buffer(bp);
     this->addLine(str);
     return curr;
}
void 
Driver::revertBuffer(YY_BUFFER_STATE bp){
  yy_switch_to_buffer(bp);

}


yy::parser::symbol_type 
Driver::get_token(){
  return yylex(*this);
}