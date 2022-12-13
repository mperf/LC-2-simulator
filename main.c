#include <stdio.h>
#include <strings.h>
#include <stdlib.h>
#include "tree.h"
#include "semantic.h"

extern int yyparse(),errors;
extern symbol_table symtab[MAX_PAGE];
extern char *yytext;
extern void printSymtab(),initLabelDeclarations();

int main() {
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
        return 0;
    }
    return 0;

}


//showinstruction()

