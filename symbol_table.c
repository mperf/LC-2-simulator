#include <stdio.h>
#if __linux__
    #include <string.h>
#else
    #include <strings.h>
#endif
#include "structures.h"
#include "symtab.h"

extern int count,countline,last,errors,countn;
extern char *yytext;
extern symbol_table *symtab;

//stampo su file lista dei simboli
void printSymtab(symbol_table* table){
    //metto a NULL ultimo elemento per dopo
    table[count].type=0;
    FILE *tab;
    tab=fopen("symbol.lst","w");
    fprintf(tab,"\n\n");
	fprintf(tab,"\t\t PHASE 1: LEXICAL ANALYSIS \n\n");
	fprintf(tab,"\nVALUE\t\t\t\t\tTOKEN_TYPE   \tLINE NUMBER\n");
	fprintf(tab,"_________________________________________________________________________\n\n");
	int i=0;
	for(i=0; i<count; i++) {
                //printf("%-17s\t\t%8s\t\t%2d\t\t\n", table[i].token_val,table[i].type, table[i].line_num);
		fprintf(tab,"%-17s\t\t%8s\t\t%2d\t\t\n", table[i].token_val,table[i].type, table[i].line_num);
	}
	
	fprintf(tab,"\n\n");
}

//errori di yacc
void yyerror(const char* msg) {
        if(!last){
                fprintf(stderr, "%s at line %d code line %d\n\"%s\" \n", msg,countline,countn,yytext);
                last=0,errors=1;
        }  
}

//aggiungo keyword alla lista dei simboli
void add(char type){
        if(type!='S'){
                toupp(yytext);
        }
        switch(type){

                case 'O':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("opcode");
                        symtab[count].line_num=countn;
                        break;
                case 'V':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("value");
                        symtab[count].line_num=countn;
                        break;
                case 'D':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("directive");
                        symtab[count].line_num=countn;
                        
                        break;
                case 'J':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("jump");
                        symtab[count].line_num=countn;
                        
                        break;
                case 'R':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("register");
                        symtab[count].line_num=countn;
                        
                        break;
                case 'L':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("label");
                        symtab[count].line_num=countn;
                        
                        break;
                case 'S':
                        symtab[count].token_val=strdup(yytext);
                        symtab[count].type=strdup("string");
                        symtab[count].line_num=countn;
                        
                        break;

                }
                count++;
}

//to upper case per verificare che i nomi siano uguali case-unsensitive
void toupp(char*s){
    int n=0,i;
    for(;s[n]!= '\0';n++);
    for (i=0; i < n; i++){
        if(s[i]>96 &&s[i]<123){
            s[i]=(char)(s[i]-32);
        }
    }
}