%{
#define THROP 1
#define REGISTER 2
#define LABEL 3
#define DIRECTIVE 4
#define NUMBERS 5
#define COMMENT 6
#define JUMP 7
#define TWOP 8
#define ORIG 9
#define ADDR 10
#define COMMA 11
int yylex();
//.   return printf("error\n");
%}
%%

(?i:"ADD"|"AND"|"JSR"|"JSRR"|"LDR"|"RET"|"RTI"|"STR"|"TRAP") return THROP; 
(?i:"LD"|"LDI"|"LEA"|"NOT"|"ST"|"STI") return TWOP;
(?i:"r")[0-7]   return REGISTER;
(?i:"br")(?i:"z"|"n"|"p")   return JUMP;
(?i:"brn")(?i:"z"|"p") return JUMP;
(?i:"brzp") return JUMP;
(?i:"brnzp") return JUMP;
"."(?i:"orig") return ORIG;
"."(?i:"fill"|"blkw"|"stringz"|"end"|"orig") return DIRECTIVE;
"x"[0-9a-fA-F][0-9a-fA-F][0-9a-fA-F][0-9a-fA-F] return ADDR;
[;]([^\n\r]+) return COMMENT;
[ \t\n] ;
"#"[0-9][0-9] return NUMBERS;
[a-zA-Z_][a-zA-Z0-9_]* return LABEL;
"," return COMMA;
.*   printf("%s\n",yytext);


%%
int yywrap (void) {return 1;}