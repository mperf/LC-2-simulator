#include <stdio.h>
#include <strings.h>
#include "semantic.h"
#include <stdlib.h>

//genero tabella label e controllo semantica
int genLibTable(symbol_table* table, labelTab *list){
    initLabelDeclarations(table, list);
    if(initLabelReferences(table, list)){
        return 1;
    }
    return 0;
}

int codeGen(symbol_table *symtab, int count){

}
int defineLen(symbol_table *table, int count){
    int len,data;

}
//TODO: check LDST reference is blkw-fill-stringz?
//TODO: verificare label doppie
//popolo lista di dichiarazioni di label
void initLabelDeclarations(symbol_table* table, labelTab *list){

    int i,data; 

    for(i=0;i<MAX_PAGE && table[i].token_val != NULL;i++){

        if(strcmp(table[i].type,"label")==0 && table[i].line_num!=table[i-1].line_num){
             list->name = strdup(table[i].token_val);
             list->next=malloc(sizeof(labelTab));
             list=list->next;
        }

    }
}


//cerco le reference alle label
int initLabelReferences(symbol_table* table, labelTab *list){
    int i,check=0;
    labelTab *head=list;
    for(i=0;i<MAX_PAGE && table[i].token_val != NULL;i++){

        //ricerca label 
        if(strcmp(table[i].type,"label")==0 && table[i].line_num==table[i-1].line_num){
            list=head;

            while(list->next != NULL && check!=1){
                
                if(strcmp(list->name,table[i].token_val)==0){
                    check=1;
                }
                list=list->next;
            }
            if(check==0){
                printf("semantic error at code line: %d, \"%s\"\n",table[i].line_num,table[i].token_val);
                return 1;
            }
            check=0;
        }  
        //sistemo direttive di memoria
        if(i>=1 && strcmp(table[i-1].type,"directive")==0){
                if(strcmp(table[i-1].token_val,".FILL")){
                    if(strcmp(table[i].type,"label")){

                    }
                }

            }
    }
    return 0;
} 