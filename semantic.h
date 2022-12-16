#include "structures.h"
// creating a list of labels (with name and references)

typedef struct labelTab_t {
    char *name;
    struct labelTab_t *next;
}labelTab;

int genLibTable(symbol_table* table, labelTab *list);
void initLabelDeclarations(symbol_table *table, labelTab *list);
int initLabelReferences(symbol_table* table, labelTab *list);
int codeGen(symbol_table *symtab, int count);
int defineLen(symbol_table *symtab, int count);
