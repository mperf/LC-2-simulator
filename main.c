#include <stdio.h>
#include <strings.h>
#include "y.tab.c"

int main() {
    yyparse();
    if(errors){
            return 0;
        }
    printSymtab(symtab);
    
}





void printSymtab(symbol_table* table){
    printf("\n\n");
	printf("\t\t\t\t\t\t\t\t PHASE 1: LEXICAL ANALYSIS \n\n");
	printf("\nVALUE   TOKEN_TYPE   LINE NUMBER \n");
	printf("_______________________________________\n\n");
	int i=0;
	for(i=0; i<count; i++) {
		printf("%s\t\t%s\t\t%d\t\t\n", table[i].token_val, table[i].token, table[i].line_num);
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