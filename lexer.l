%{


int yylex();
//.   return printf("error\n");
//trap 21-22-23-25
int countline=1;
#include "y.tab.h"


%}

%option yylineno

%%

(?i:"RET"|"RTI") {return RETS;} 
(?i:"LD"|"LDI"|"LEA"|"ST"|"STI") return LDST;
(?i:"NOT") {return NOT;}
(?i:"ADD"|"AND") {return IMOP;}
(?i:"LDR"|"STR") {return BSOP;}
(?i:"TRAP") {return TRAP;}
(?i:"r")[0-7]   return REGISTER;
(?i:"br")(?i:"z"|"n"|"p")   return JUMP;
(?i:"brn")(?i:"z"|"p") return JUMP;
(?i:"brzp") return JUMP;
(?i:"brnzp") return JUMP;
(?I:"JSR") return JSR;
(?I:"JSRR") return JSRR;
"."(?i:"orig") return ORIG;
"."(?i:"end")  return END;
"."(?i:"blkw") return BLKW;
"."(?i:"fill") return FILL;
"."(?i:"stringz") return STRINGZ;
(?i:"b")[0-1]{16} return BINARY;
"x"[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F] return ADDR;
";".* 
[ \t]*                      { ; }
[\n]                        countline++;
"#"[-]?[0-9] return NUMBERS;
"#"[-]?[1][0-5] return NUMBERS;
[-]?[0-9]* return NUM;
[a-zA-Z_][a-zA-Z0-9_]* return LABEL;
["].*["]     return STR; 
"," return COMMA;
<<EOF>> return EOF;
.   ;


%%
int yywrap (void) {return 1;}
//short int per ca2 registri
//sistemare limite minimo di bit per BINARY