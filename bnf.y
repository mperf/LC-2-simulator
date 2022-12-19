
%{
 
#include <stdio.h>
#include <stdlib.h>
#include "tree.h"

extern int yylex();
extern int yywrap();
extern void add(),yyerror();


int countn=1,count=0,last=0,errors=0;

%}

%union { 
	struct var_name { 
		char name[100]; 
		struct node* nd;
	} nd_obj; 
}


%token <nd_obj> REGISTER RETS LDST EOFF NOT LABEL NUMBERS ORIG COMMENT JUMP COMMA ADDR END BLKW STRINGZ BINARY NUM FILL STR JSR JSRR IMOP BSOP TRAP
%type <nd_obj> program orig lines end endb code ldst ldstb imop imopb bsop ret jump jumpb directive dirb jsr not trap codeb 
%start program

%%

program :   orig lines end  {
        $2.nd=mknode($2.nd, $3.nd,"code"); 
        $$.nd=mknode($1.nd, $2.nd,"program"); 
        head = $$.nd;   
        printf("Analysis completed...\n");
        last=1;
        }
        ;

end     : endb EOFF { $$.nd = mknode($1.nd, NULL, "end"); }
        ;

endb    :   END  {
         add('D');
         $$.nd = mknode(NULL, NULL, "endchar"); 
         }
        ;

orig    :   ORIG  {add('D');} ADDR  {add('V');countn++;
          $$.nd=mknode(NULL, NULL, "orig");
         }
        ;

lines   :   code        {countn++; $1.nd=mknode($1.nd, NULL, "line"); } 
        |   lines code  {countn++; $$.nd=mknode($1.nd,$2.nd,"lines");}
        ;

code    :   ldst                {$$.nd=mknode(NULL,$1.nd,"ldst");}
        |   imop                {$$.nd=mknode(NULL,$1.nd,"imop");}
        |   bsop                {$$.nd=mknode(NULL,$1.nd,"bsop");}
        |   ret                 {$$.nd=mknode(NULL,$1.nd,"ret");}
        |   jump                {$$.nd=mknode(NULL,$1.nd,"jump");}
        |   directive           {$$.nd=mknode(NULL,$1.nd,"directive");} 
        |   jsr                 {$$.nd=mknode(NULL,$1.nd,"jsr");}
        |   not                 {$$.nd=mknode(NULL,$1.nd,"not");}
        |   trap                {$$.nd=mknode(NULL,$1.nd,"trap");}
        |   codeb ldst          {$$.nd=mknode(NULL,$2.nd,"c-ldst");}
        |   codeb imop          {$$.nd=mknode($1.nd,$2.nd,"c-imop");}
        |   codeb bsop          {$$.nd=mknode($1.nd,$2.nd,"c-bsop");}
        |   codeb ret           {$$.nd=mknode($1.nd,$2.nd,"c-ret");}
        |   codeb jump          {$$.nd=mknode($1.nd,$2.nd,"c-jump");}
        |   codeb directive     {$$.nd=mknode($1.nd,$2.nd,"c-directive");}
        |   codeb jsr           {$$.nd=mknode($1.nd,$2.nd,"c-jsr");}
        |   codeb not           {$$.nd=mknode($1.nd,$2.nd,"c-not");}
        |   codeb trap          {$$.nd=mknode($1.nd,$2.nd,"c-trap");}
        ;

codeb   :   LABEL {add('L'); $$.nd=mknode(NULL,NULL,"label");}
        ;

imop    :   imopb COMMA REGISTER { 
          add('R'); 
          $2.nd=mknode(NULL,NULL,"operands");
          $$.nd=mknode($1.nd,$2.nd,"op");
          } 
        |   imopb COMMA NUMBERS { 
          add('V'); 
          $2.nd=mknode(NULL,NULL,"operands");
          $$.nd=mknode($1.nd,$2.nd,"op");
        }
        |   imopb COMMA BINARY { 
          add('V'); 
          $2.nd=mknode(NULL,NULL,"operands");
          $$.nd=mknode($1.nd,$2.nd,"op");
        }
        |   imopb COMMA ADDR { 
          add('V'); 
          $2.nd=mknode(NULL,NULL,"operands");
          $$.nd=mknode($1.nd,$2.nd,"op");
        }
        ;

imopb   : IMOP  { add('O'); } REGISTER  { add('R'); } COMMA REGISTER  { 
          add('R'); 
          $$.nd=mknode(NULL,NULL,"op");
          }
        ;

    
bsop    :   BSOP  {add('O');} REGISTER  {add('R');} COMMA REGISTER {add('R');}  COMMA NUMBERS {
          add('V');
          $$.nd=mknode(NULL,NULL,"op");
          }
        ;


ldst    :   ldstb COMMA ADDR {
          add('V');
          $2.nd=mknode(NULL,NULL,"operands");
          $$.nd=mknode($1.nd,$2.nd,"op");
          }
        |   ldstb COMMA LABEL {
          add('L');
          $2.nd=mknode(NULL,NULL,"operands");
          $$.nd=mknode($1.nd,$2.nd,"op");
          }
        ;

ldstb   :   LDST  {add('O');} REGISTER {add('R'); $$.nd=mknode(NULL,NULL,"op");} 
        ;

not     :   NOT  {add('O');} REGISTER {add('R');} COMMA REGISTER {
          add('R');
          $$.nd=mknode(NULL,NULL,"op");
          }
        ;

jump    :   jumpb ADDR {add('V'); $$.nd=mknode($1.nd,NULL,"op");}
        |   jumpb LABEL {add('L'); $$.nd=mknode($1.nd,NULL,"op");}
        ;

jumpb   :   JUMP {add('J');  $$.nd = mknode(NULL, NULL, $1.name);}
        ;

directive : dirb ADDR  {add('V'); $$.nd=mknode($1.nd,NULL,"op");}
          | dirb NUM  {add('V'); $$.nd=mknode($1.nd,NULL,"op");if(atoi($2.name)>32767){yyerror("Constraints error");}}
          | dirb BINARY  {add('V'); $$.nd=mknode($1.nd,NULL,"op"); int i;for(i=0;$2.name[i]!='\0';i++);if(i!=17){yyerror("Syntax error");}}
          | dirb LABEL  {add('L'); $$.nd=mknode($1.nd,NULL,"op");}
          | BLKW {add('D');} NUM  {add('V'); $$.nd=mknode(NULL,NULL,"op");}
          | STRINGZ {add('D');} STR {add('S'); $$.nd=mknode(NULL,NULL,"op");}
          | endb {$$.nd=mknode($1.nd,NULL,"op");}
          ;

dirb      : FILL {add('D'); $$.nd = mknode(NULL, NULL, "fill");}
          ;


trap    :  TRAP {add('O');} ADDR {add('V'); $$.nd = mknode(NULL, NULL, "trap");}
        ;

ret     :  RETS {add('O'); $$.nd = mknode(NULL, NULL, $1.name);}
        ;

jsr     :   JSR  {add('O');} LABEL {add('L'); $$.nd = mknode(NULL, NULL, "jsr");}
        |   JSRR  {add('O');} REGISTER  {add('R');} COMMA ADDR {add('V'); $$.nd = mknode(NULL, NULL, $1.name);}
        ;

%%

