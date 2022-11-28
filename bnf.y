
%{

#include"lex.yy.c"
    
void yyerror(const char *s);
int yylex();
int yywrap();
int countn=1;

%}


%token REGISTER RETS EOF LDST NOT LABEL NUMBERS ORIG COMMENT JUMP COMMA ADDR END BLKW STRINGZ BINARY NUM FILL STR JSR JSRR IMOP BSOP TRAP



%%

program :   orig lines end  {printf("input accepted!\n");exit(0);}
        ;

end     :   END EOF
        ;

orig    :   ORIG ADDR  {countn++;}
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
        ;

imop    :   LABEL IMOP REGISTER COMMA REGISTER COMMA REGISTER
        |   LABEL IMOP REGISTER COMMA REGISTER COMMA NUMBERS
        |   LABEL IMOP REGISTER COMMA REGISTER COMMA BINARY
        |   LABEL IMOP REGISTER COMMA REGISTER COMMA ADDR
        |   IMOP REGISTER COMMA REGISTER COMMA REGISTER
        |   IMOP REGISTER COMMA REGISTER COMMA NUMBERS
        |   IMOP REGISTER COMMA REGISTER COMMA BINARY
        |   IMOP REGISTER COMMA REGISTER COMMA ADDR
        ;

    
bsop    :   LABEL BSOP REGISTER COMMA REGISTER COMMA NUMBERS
        |   BSOP REGISTER COMMA REGISTER COMMA NUMBERS
        ;


ldst    :   LABEL LDST REGISTER COMMA ADDR
        |   LDST REGISTER COMMA ADDR
        |   LABEL LDST REGISTER COMMA LABEL
        |   LDST REGISTER COMMA LABEL
        ;

not     :   LABEL NOT REGISTER COMMA REGISTER
        |   NOT REGISTER COMMA REGISTER
        ;

jump    :   LABEL JUMP ADDR
        |   LABEL JUMP LABEL
        |   JUMP ADDR
        |   JUMP LABEL
        ;

directive : LABEL FILL ADDR 
          | LABEL FILL NUM      
          | LABEL FILL BINARY
          | LABEL FILL LABEL 
          | LABEL BLKW NUM
          | LABEL STRINGZ STR
          | FILL ADDR
          | FILL NUM 
          | FILL BINARY
          | FILL LABEL
          | BLKW NUM
          | STRINGZ STR
          ;

trap    :   LABEL TRAP ADDR
        |   TRAP ADDR
        ;

ret     :   LABEL RETS
        |   RETS
        ;

jsr     :   LABEL JSR LABEL
        |   LABEL JSRR REGISTER COMMA ADDR
        |   JSR LABEL
        |   JSRR REGISTER COMMA ADDR
        ;

%%

int main() {
    yyparse();
}

void yyerror(const char* msg) {
    fprintf(stderr, "%s at line %d code line %d\n\"%s\" \n", msg,countline,countn,yytext);
}