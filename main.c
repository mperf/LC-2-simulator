#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "tree.h"
#include "semantic.h"

extern int yyparse(),errors;
extern symbol_table *symtab;
extern char *yytext;
extern FILE *yyin;
extern int printSymtab(),genLibTable();


int main(int argc, char const *argv[]) {
    if(argc == 1){
        printf("errore, passare come secondo parametro il nome del file assembly.\n");
        return 0;
    }
    symtab=malloc(sizeof(symbol_table)*512);
    yyin=fopen(argv[1],"r");
    //richiamo il parser
    yyparse();
    if(errors){
            return 0;
        }
    //stampo su file la tabella dei simboli
    printSymtab(symtab);
    //stampo su file l'AST
    printSyntaxTree(head);
    //inizializzo radice lista tabella delle label
    labelTab *radix= malloc(sizeof(labelTab));
    //genero la tabella delle label e controllo errori semantici sulle label
    if(genLibTable(symtab, radix)){
    //    return 0;
    }
    return 0;

}


//showinstruction()


