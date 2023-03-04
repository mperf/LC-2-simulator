#include <stdio.h>
#if __linux__
    #include <string.h>
#else
    #include <strings.h>
#endif
#include <stdlib.h>
#include "tree.h"
#include "semantic.h"

extern int yyparse(),errors;
//extern symbol_table *symtab;
symbol_table *symtab;
extern char *yytext;
extern FILE *yyin;
extern int printSymtab(),genLibTable(),exec_code();
extern void printHelp(),freeSymTab(),freeLabelTab();
struct node *head;


int main(int argc, char  *argv[]) {

    int count,options=0,i,shift;
    if(argc == 1){
        printHelp();
        return 0;
    }
    if(argc==3){
        if(strcmp(argv[2],"-e")==0 || strcmp(argv[2],"-E")==0){
            //printf("switch inserito: %c\n",argv[2][1]);
            options=1;
        }else if(strcmp(argv[2],"-s")==0 || strcmp(argv[2],"-S")==0){
            //printf("switch inserito: %c\n",argv[2][1]);
            //scegli tempo?
            options=2;
        }else{
            printf("command error\n");
            return 1;
        }
    }else if(argc!=0 && argc>3){
        printf("command error\n");
        return 1;
    }
    symtab=malloc(sizeof(symbol_table)*512);
    yyin=fopen(argv[1],"r");
    //richiamo il parser
    yyparse();
    if(errors){
            printf("errors detected. exiting...\n");
            return 1;
        }else{
            printf("input accepted\n");
        }
    //stampo su file la tabella dei simboli
    printSymtab(symtab);
    //stampo su file l'AST
    printSyntaxTree(head);
    //inizializzo radice codice

    symbol_table *code_head;
    code_head=codeGen(symtab,code_head);
    //inizializzo radice lista tabella delle label
    labelTab *radix= malloc(sizeof(labelTab));
    radix->name=0;
    //genero la tabella delle label e controllo errori semantici sulle label
    
    
    if(genLibTable(code_head, radix)){
        return 0;
    }
    freeSymTab(symtab);
    if(radix->name!=NULL){
        freeLabelTab(radix);   
    }
    //eseguo codice
    exec_code(code_head,options,options);
    // FILE *tab;
    // tab=fopen("debug.txt","w");
    // for(i=0;code_head[i].type!=NULL; i++) {
    //     shift=0;
	// 	do{
    //         fprintf(tab,"%s\t",code_head[i+shift].token_val);
    //         shift++;
    //     }while(code_head[i+shift].line_num==code_head[i-1+shift].line_num);
    //     fprintf(tab,"\n");
	// }
    
    return 0;

}


//showinstruction()


