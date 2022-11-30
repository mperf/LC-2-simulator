
%{

#include"lex.yy.c"
#include "structures.h"   
#include "proto.h"
int yylex();
int yywrap();


int countn=1,q,count=0,last=0,errors=0;

%}


%token REGISTER RETS LDST EOFF NOT LABEL NUMBERS ORIG COMMENT JUMP COMMA ADDR END BLKW STRINGZ BINARY NUM FILL STR JSR JSRR IMOP BSOP TRAP
%start program

%%

program :   orig lines end  {printf("input accepted\n");last=1;}
        ;

end     : endb EOFF
        ;

endb    : END  {add('D');}
        ;

orig    :   ORIG  {add('D');} ADDR  {countn++;}
        ;

lines   :   code        {countn++;}
        |   lines code  {countn++;}
        ;

code    :   ldst 
        |   imop
        |   bsop
        |   ret
        |   jump
        |   directive 
        |   jsr
        |   not
        |   trap
        |   codeb ldst 
        |   codeb imop
        |   codeb bsop
        |   codeb ret
        |   codeb jump
        |   codeb directive 
        |   codeb jsr
        |   codeb not
        |   codeb trap
        ;

codeb   :   LABEL {add('L');}
        ;

imop    :   imopb COMMA REGISTER { add('R'); }
        |   imopb COMMA NUMBERS { add('V'); }
        |   imopb COMMA BINARY { add('V'); }
        |   imopb COMMA ADDR { add('V'); }
        ;

imopb   : IMOP  { add('O'); } REGISTER  { add('R'); } COMMA REGISTER  { add('R'); }
        ;

    
bsop    :   BSOP  {add('O');} REGISTER  {add('R');} COMMA REGISTER {add('R');}  COMMA NUMBERS {add('V');}
        ;


ldst    :   ldstb COMMA ADDR {add('V');}
        |   ldstb COMMA LABEL {add('L');}
        ;

ldstb   :   LDST  {add('O');} REGISTER {add('R');} 
        ;

not     :   NOT  {add('O');} REGISTER {add('R');} COMMA REGISTER {add('R');}
        ;

jump    :   jumpb ADDR {add('V');}
        |   jumpb LABEL {add('L');}
        ;

jumpb   :   JUMP {add('J');}
        ;

directive : dirb ADDR  {add('V');}
          | dirb NUM  {add('V');}
          | dirb BINARY  {add('V');}
          | dirb LABEL  {add('L');}
          | BLKW {add('D');} NUM  {add('V');}
          | STRINGZ {add('D');} STR {add('S');}
          | endb
          ;

dirb      : FILL {add('D');}
          ;


trap    :  TRAP {add('O');} ADDR {add('V');}
        ;

ret     :  RETS {add('O');}
        ;

jsr     :   JSR  {add('O');} LABEL {add('L');}
        |   JSRR  {add('O');} REGISTER  {add('R');} COMMA ADDR {add('V');}
        ;

%%

