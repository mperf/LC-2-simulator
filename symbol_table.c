#include <stdio.h>
#include <strings.h>
#include "structures.h"

void add(char type, char *token);
int search(char *type);
void printSymtab(symbol_table* table);
void yyerror(const char *s);
void toupp(char*s);

extern int count,countline,last,errors,countn;
extern char *yytext;

void printSymtab(symbol_table* table){
    FILE *tab;
    tab=fopen("symbol.lst","w");
    fprintf(tab,"\n\n");
	fprintf(tab,"\t\t PHASE 1: LEXICAL ANALYSIS \n\n");
	fprintf(tab,"\nVALUE\t\t\t\t\tTOKEN_TYPE   \tLINE NUMBER   \tOCCURRENCES\n");
	fprintf(tab,"_________________________________________________________________________\n\n");
	int i=0;
	for(i=0; i<count; i++) {
		fprintf(tab,"%-17s\t\t%8s\t\t%2d\t\t\t\t%2d\t\t\n", table[i].token_val,table[i].type, table[i].line_num,table[i].times);
	}
	
	fprintf(tab,"\n\n");
}


void yyerror(const char* msg) {
        if(!last){
                fprintf(stderr, "%s at line %d code line %d\n\"%s\" \n", msg,countline,countn,yytext);
                last=0,errors=1;
        }  
}

void add(char type, char * token){
        toupp(yytext);
        int q=search(yytext);
        switch(type){

                case 'O':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("opcode");
                        symtab[count].line_num=countn;
                        symtab[count].times=q;
                        break;
                case 'V':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("value");
                        symtab[count].line_num=countn;
                        symtab[count].times=q;
                        break;
                case 'D':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("directive");
                        symtab[count].line_num=countn;
                        symtab[count].times=q;
                        break;
                case 'J':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("jump");
                        symtab[count].line_num=countn;
                        symtab[count].times=q;
                        break;
                case 'R':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("register");
                        symtab[count].line_num=countn;
                        symtab[count].times=q;
                        break;
                case 'L':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("label");
                        symtab[count].line_num=countn;
                        symtab[count].times=q;
                        break;
                case 'S':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("string");
                        symtab[count].line_num=countn;
                        symtab[count].times=q;
                        break;

                }
                count++;
}

int search(char *type) { 
    int i,o=1; 
    for(i=count-1; i>=0; i--) {
        if(strcmp(symtab[i].token_val, type)==0) {   
            o++;  
        }
    } 
    return o;
}

void toupp(char*s){
    int n=0,i;
    for(;s[n]!= '\0';n++);
    for (i=0; i < n; i++){
        if(s[i]>96 &&s[i]<123){
            s[i]=(char)(s[i]-32);
        }
    }
}