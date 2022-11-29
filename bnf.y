
%{

#include"lex.yy.c"
    
void yyerror(const char *s);
int yylex();
int yywrap();
void add(char type);
int search(char *type);
int countn=1;

typedef struct {
        char * token_val;
        char * token;
        int line_num;
}symbol_table;

symbol_table symtab[512];


int q,count=0,last=0,errors=0;

%}


%token REGISTER RETS EOF LDST NOT LABEL NUMBERS ORIG COMMENT JUMP COMMA ADDR END BLKW STRINGZ BINARY NUM FILL STR JSR JSRR IMOP BSOP TRAP
%start program

%%

program :   orig lines end  {printf("input accepted\n");last=1;}
        ;

end     : endb EOF 
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

int main() {
    yyparse();
    if(errors){
                return 0;
        }
        printf("\n\n");
	printf("\t\t\t\t\t\t\t\t PHASE 1: LEXICAL ANALYSIS \n\n");
	printf("\nVALUE   TOKEN_TYPE   LINE NUMBER \n");
	printf("_______________________________________\n\n");
	int i=0;
	for(i=0; i<count; i++) {
		printf("%s\t\t%s\t\t%d\t\t\n", symtab[i].token_val, symtab[i].token, symtab[i].line_num);
	}
	for(i=0;i<count;i++) {
		free(symtab[i].token_val);
	}
	printf("\n\n");
}



void yyerror(const char* msg) {
        if(!last){
                fprintf(stderr, "%s at line %d code line %d\n\"%s\" \n", msg,countline,countn,yytext);
                last=0,errors=1;
        }  
}

void add(char type){
        
        q=search(yytext);
        if(!q){
        switch(type){

                case 'O':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].token=strdup("opcode");
                        symtab[count].line_num=countn;
                        break;
                case 'V':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].token=strdup("value");
                        symtab[count].line_num=countn;
                        break;
                case 'D':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].token=strdup("directive");
                        symtab[count].line_num=countn;
                        break;
                case 'J':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].token=strdup("jump");
                        symtab[count].line_num=countn;
                        break;
                case 'R':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].token=strdup("register");
                        symtab[count].line_num=countn;
                        break;
                case 'L':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].token=strdup("label");
                        symtab[count].line_num=countn;
                        break;
                case 'S':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].token=strdup("string");
                        symtab[count].line_num=countn;
                        break;

                }
                count++;
        }
}

int search(char *type) { 
    int i; 
    for(i=count-1; i>=0; i--) {
        if(strcmp(symtab[i].token_val, type)==0) {   
            return -1;
            break;  
        }
    } 
    return 0;
}