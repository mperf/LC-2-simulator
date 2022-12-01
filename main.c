#include <stdio.h>
#include <strings.h>
#include "structures.h"

extern int yyparse(),errors;
extern symbol_table symtab[MAX_PAGE];
extern char *yytext;
extern void printSymtab();

int main() {
    yyparse();
    if(errors){
            return 0;
        }
    printSymtab(symtab);
    
}



//aggiungere nella struct contatore di occorrenze, se label esce due volte warning possibile errore logico

