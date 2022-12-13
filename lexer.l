%{

int countline=1;
#include "y.tab.h"
#include "tree.h"
%}

%option yylineno

%%

(?i:"RET"|"RTI")                                {strcpy(yylval.nd_obj.name,(yytext)); return RETS;} 
(?i:"LD"|"LDI"|"LEA"|"ST"|"STI")                {strcpy(yylval.nd_obj.name,(yytext)); return LDST;}
(?i:"NOT")                                      {strcpy(yylval.nd_obj.name,(yytext));  return NOT;}
(?i:"ADD"|"AND")                                {strcpy(yylval.nd_obj.name,(yytext));  return IMOP;}
(?i:"LDR"|"STR")                                {strcpy(yylval.nd_obj.name,(yytext));  return BSOP;}
(?i:"TRAP")                                     {strcpy(yylval.nd_obj.name,(yytext));  return TRAP;}
(?i:"r")[0-7]                                   {strcpy(yylval.nd_obj.name,(yytext));  return REGISTER;}
(?i:"br")(?i:"z"|"n"|"p")                       {strcpy(yylval.nd_obj.name,(yytext));  return JUMP;}
(?i:"brn")(?i:"z"|"p")                          {strcpy(yylval.nd_obj.name,(yytext));  return JUMP;}
(?i:"brzp")                                     {strcpy(yylval.nd_obj.name,(yytext));  return JUMP;}
(?i:"brnzp")                                    {strcpy(yylval.nd_obj.name,(yytext));  return JUMP;}
(?I:"JSR")                                      {strcpy(yylval.nd_obj.name,(yytext));  return JSR;}
(?I:"JSRR")                                     {strcpy(yylval.nd_obj.name,(yytext));  return JSRR;}
"."(?i:"orig")                                  {strcpy(yylval.nd_obj.name,(yytext));  return ORIG;}
"."(?i:"end")                                   {strcpy(yylval.nd_obj.name,(yytext));  return END;}
"."(?i:"blkw")                                  {strcpy(yylval.nd_obj.name,(yytext));  return BLKW;}
"."(?i:"fill")                                  {strcpy(yylval.nd_obj.name,(yytext));  return FILL;}
"."(?i:"stringz")                               {strcpy(yylval.nd_obj.name,(yytext));  return STRINGZ;}
(?i:"b")[0-1]{16}                               {strcpy(yylval.nd_obj.name,(yytext));  return BINARY;}
"x"[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F] {strcpy(yylval.nd_obj.name,(yytext));  return ADDR;}
";".*                                           { ; }
[ \t]*                                          { ; }
[\n]                                            countline++;
"#"[-]?[0-9]                                    {strcpy(yylval.nd_obj.name,(yytext));  return NUMBERS;}
"#"[-]?[1][0-5]                                 {strcpy(yylval.nd_obj.name,(yytext));  return NUMBERS;}
[-]?[0-9]*                                      {strcpy(yylval.nd_obj.name,(yytext));  return NUM;}
[a-zA-Z_][a-zA-Z0-9_]*                          {strcpy(yylval.nd_obj.name,(yytext));  return LABEL;}
["].*["]                                        {strcpy(yylval.nd_obj.name,(yytext));  return STR;} 
","                                             {strcpy(yylval.nd_obj.name,(yytext));  return COMMA;}
<<EOF>>                                         {strcpy(yylval.nd_obj.name,(yytext));  return EOFF;}
.                                               { ; }


%%
int yywrap (void) {return 1;}
//short int per ca2 registri
//sistemare limite minimo di bit per BINARY