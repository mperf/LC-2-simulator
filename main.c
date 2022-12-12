#include <stdio.h>
#include <strings.h>
#include "structures.h"
#include "tree.h"

extern int yyparse(),checkLabels(),errors;
extern symbol_table symtab[MAX_PAGE];
extern char *yytext;
extern void printSymtab();

int main() {
    
    
    yyparse();
    if(errors){
            return 0;
        }
    printSymtab(symtab);
    
    printSyntaxTree(head);
    if(checkLabels(symtab)){
    }

}


//showinstruction()

