#include <stdio.h>
#include <strings.h>
#include "semantic.h"
#include <stdlib.h>

int genLibTable(symbol_table* table, labelTab *list){
    initLabelDeclarations(symtab, list);
    if(initLabelReferences(symtab, list)){
        return 1;
    }
    return 0;
}



void initLabelDeclarations(symbol_table* table, labelTab *list){

    int i,numLabels=0,counter=0; 

    for(i=0;i<MAX_PAGE && table[i].token_val != NULL;i++){

        if(strcmp(table[i].type,"label")==0 && table[i].line_num!=table[i-1].line_num){
            //risparmio memoria puntando direttamente list.name alla keyword della symbol table
             list->name = table[i].token_val;
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
    }
    return 0;
}
//check binary numbers
//check addr vvv
//se addr di istruzione %16 != 0 errore 