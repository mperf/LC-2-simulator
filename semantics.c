#include <stdio.h>
#include <strings.h>
#include "semantic.h"
#include <stdlib.h>

//genero tabella label e controllo semantica
int genLibTable(symbol_table* table, labelTab *list){

    if(initLabelDeclarations(table, list)){
        return 1;
    }
    if(initLabelReferences(table, list)){
        return 1;
    }
    toAddr(table,list);

    return 0;
}

int toAddr(symbol_table *code, labelTab *head){
    int i,check,j=0;
    labelTab *list;
    for(i=0; code[i].type != NULL;i++){
        //label--> ADDR
        if(strcmp(code[i].type,"label")==0 && code[i].line_num==code[i-1].line_num){
            list=head;
            check=0,j=0;
            while(list->next != NULL && check!=1){
                if(strcmp(list->name,code[i].token_val)==0){
                    free(code[i].token_val);
                    code[i].token_val=malloc(sizeof(char)*4);
                    sprintf(code[i].token_val,"%d",list->line);
                    check=1,j++;    
                }
                list=list->next;
            }
            if(check==0){
                return 1;
            } 
        }

    }
    return 0;

}

symbol_table * codeGen(symbol_table *table,symbol_table *code){
    // FILE *tab;
    // tab=fopen("debug.txt","w");

    int len,i,padd=0,j=0,k=0,shift=0;
    len=defineLen(symtab);
    code=malloc(sizeof(symbol_table)*len);
    symbol_table *rad=code;

    for(i=0; table[i].type != NULL;i++){
        //padding from stringz and blkw
            //j>1?printf("instr: %s  tipo: %s, riga %d\n",table[j-1].token_val,table[j-1].type,table[j-1].line_num):printf("");
            if(i>0 && strcmp(table[i].type,"directive")==0 && (strcmp(table[i].token_val,".BLKW")==0 || strcmp(table[i].token_val,".STRINGZ")==0)){
            
            //blkw
            if(strcmp(table[i].token_val,".BLKW")==0){
                if(!(strcmp(table[i+1].token_val,"1")==0)){
                    padd=atoi(table[i+1].token_val);
                    for(k=0;k<padd;k++){
                        code[j].type=malloc(sizeof(char)*6);
                        strcpy(code[j].type,".blkw");
                        code[j].line_num=table[i].line_num+shift;
                        //token val NULL
                        code[j].token_val=0;
                        j++,shift++;
                    }
                }else{
                    code[j].type=malloc(sizeof(char)*6);
                    strcpy(code[j].type,".blkw");
                    //code[j].type=strdup(".blkw");
                    code[j].line_num=table[i].line_num+shift;
                    //token val NULL
                    code[j].token_val=0;
                    j++;
                    shift++;
                }
                i++,shift--;
                
            }


            //stringz
            if(strcmp(table[i].token_val,".STRINGZ")==0){
                for(len=0;table[i+1].token_val[len]!='\0';len++);
                if(len>3){
                    for(k=0;k<len-2;k++){
                        code[j].type=strdup(".stringz");
                        code[j].line_num=table[i].line_num+shift;
                        code[j].token_val=malloc(sizeof(char)*2);
                        //printf("ciclo string: %c\n",table[i+1].token_val[1+k]);
                        code[j].token_val[0]=table[i+1].token_val[1+k];
                        code[j].token_val[1]='\0';
                        j++,shift++;
                    }
                    j++;
                    code[j-1].token_val="0";
                    code[j-1].type=strdup(".stringz");
                    code[j-1].line_num=table[i].line_num+shift;
                    shift++;
                }else{
                    code[j].type=strdup(".stringz");
                    code[j].line_num=table[i].line_num+shift;
                    code[j].token_val=malloc(sizeof(char)*2);
                    code[j].token_val[0]=table[i+1].token_val[1];
                    code[j].token_val[1]='\0';
                    j+=2,shift++;
                    code[j-1].token_val="0";
                    code[j-1].type=strdup(".stringz");
                    code[j-1].line_num=table[i].line_num+shift;
                    shift++;
                }
                i++,shift--;
            }

        }else{
            //printf("size of %s : %d\n",table[i].type,(strlen(table[i].type)+1));
            code[j].type=malloc(sizeof(char)*(strlen(table[i].type)+1));
            strcpy(code[j].type,table[i].type);
            //code[j].type=strdup(table[i].type);
           // printf("strdup: %s\n",table[i].type);
            code[j].line_num=table[i].line_num+shift;
            //printf("size of %s : %d\n",table[i].token_val,(strlen(table[i].token_val)+1));
            code[j].token_val=malloc(sizeof(char)*(strlen(table[i].token_val)+1));
            strcpy(code[j].token_val,table[i].token_val);
            //code[j].token_val=strdup(table[i].token_val);
            //fprintf(tab,"bah: %s\n",code[j].type);
            j++;
        }
        
    //fprintf(tab,"\n\n");
    }
    //printf("i: %d\n",i);
    code[j].type=0;
    // for(i=0; i<j; i++) {
	// 	fprintf(tab,"%-17s\t\t%8s\t\t%2d\t\t\n", code[i].token_val, code[i].type, code[i].line_num);
	// }

    return code;
}

//aggiungo alla lunghezza le direttive di memoria
int defineLen(symbol_table *table){
    int len,data=0,i;
    for(i=0; table[i].type != NULL ;i++){
        //aggiungo a data le direttive
        if(i>0 && strcmp(table[i].type,"directive")==0){
            if(strcmp(table[i].token_val,".BLKW")==0){
                if(!(strcmp(table[i+1].token_val,"1")==0)){
                    data+=atoi(table[i+1].token_val);
                    i++;
                }else{
                    data++;
                }
                
            }else if(strcmp(table[i].token_val,".STRINGZ")==0){
                for(len=0;table[i+1].token_val[len]!='\0';len++);
                if(len>1){
                    //tolgo due perchè la len vede due vrigolette e terminatore, partendo da zero è già -1 quindi -1-2=-3, aggiungo 1 per lo zero
                    data+=len-1;
                }else{
                    data++;
                }
                i++;
            }else{
                data++;
            }

        }else{
            data++;
        }
        //tante data++! lascio così è più comprensibile
    }
    return data;
}


//popolo lista di dichiarazioni di label e verifico label doppie
int initLabelDeclarations(symbol_table* table, labelTab *list){

    int i,data,check=0; 
    labelTab *head=list,*point=list;
    for(i=0;i<MAX_PAGE && table[i].type != NULL;i++){
        if(strcmp(table[i].type,"label")==0 && table[i].line_num!=table[i-1].line_num){
            point=list;
            list=head;
            while(list->next && check!=1 && list->name){
                if(strcmp(list->name,table[i].token_val)==0){
                    check=1;
                }
                list=list->next;
                
            }
            if(check==1){
                printf("semantic error at code line: %d, \"%s\"\n",table[i].line_num,table[i].token_val);
                return 1;
            }
            
             list=point;
             list->name = strdup(table[i].token_val);
             //printf("LABEL: %s",table[i].token_val);
             list->line=table[i].line_num;
             list->next=malloc(sizeof(labelTab));
             list=list->next;
             list->name=0;
        }

    }
    return 0;
}


//cerco le reference alle label
int initLabelReferences(symbol_table* table, labelTab *list){
    int i,check=0;
    labelTab *head=list;
    for(i=0;i<MAX_PAGE && table[i].type != NULL;i++){

        //ricerca label 
        if(strcmp(table[i].type,"label")==0 && table[i].line_num==table[i-1].line_num){
            list=head;

            while(list->next && check!=1 && list->line){
                
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

void freeSymTab(symbol_table* table){
    int i;
    for(i=0;i<MAX_PAGE && table[i].token_val != NULL;i++){
        free(table[i].token_val);
        free(table[i].type);
    }
    free(table);
}

void freeLabelTab(labelTab *labTab){
    free(labTab->name);
    if(labTab->next != NULL){
        freeLabelTab(labTab->next);
    }
    free(labTab);
    return;
}