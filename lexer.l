%{

int countline=1;
#include "y.tab.h"
#include "tree.h"
#define TABLE strcpy(yylval.nd_obj.name,(yytext));
%}

%option yylineno

%%

(?i:"RET"|"RTI")                                {TABLE return RETS;} 
(?i:"LD"|"LDI"|"LEA"|"ST"|"STI")                {TABLE return LDST;}
(?i:"NOT")                                      {TABLE  return NOT;}
(?i:"ADD"|"AND")                                {TABLE  return IMOP;}
(?i:"LDR"|"STR")                                {TABLE  return BSOP;}
(?i:"TRAP")                                     {TABLE  return TRAP;}
(?i:"r")[0-7]                                   {TABLE  return REGISTER;}
(?i:"br")(?i:"z"|"n"|"p")                       {TABLE  return JUMP;}
(?i:"brn")(?i:"z"|"p")                          {TABLE  return JUMP;}
(?i:"brzp")                                     {TABLE  return JUMP;}
(?i:"brnzp")                                    {TABLE  return JUMP;}
(?I:"JSR")                                      {TABLE  return JSR;}
(?I:"JSRR")                                     {TABLE  return JSRR;}
"."(?i:"orig")                                  {TABLE  return ORIG;}
"."(?i:"end")                                   {TABLE  return END;}
"."(?i:"blkw")                                  {TABLE  return BLKW;}
"."(?i:"fill")                                  {TABLE  return FILL;}
"."(?i:"stringz")                               {TABLE  return STRINGZ;}
(?i:"b")[0-1]{16}                               {TABLE  return BINARY;}
"x"[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F] {TABLE  return ADDR;}
";".*                                           { ; }
[ \t]*                                          { ; }
[\n]                                            countline++;
"#"[-]?[0-9]                                    {TABLE  return NUMBERS;}
"#"[-]?[1][0-5]                                 {TABLE  return NUMBERS;}
[-]?[0-9]*                                      {TABLE  return NUM;}
[a-zA-Z_][a-zA-Z0-9_]*                          {TABLE  return LABEL;}
["].*["]                                        {TABLE  return STR;} 
","                                             {TABLE  return COMMA;}
<<EOF>>                                         {TABLE  return EOFF;}
.                                               { ; }


%%
int yywrap (void) {return 1;}
//short int per ca2 registri
//sistemare limite minimo di bit per BINARY