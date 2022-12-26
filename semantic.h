#include "structures.h"
// creating a list of labels (with name and references)

typedef struct labelTab_t {
    char *name;
    int line;
    struct labelTab_t *next;
}labelTab;

int genLibTable(symbol_table* table, labelTab *list);
int toAddr(symbol_table *code, labelTab *head);
int initLabelDeclarations(symbol_table *table, labelTab *list);
int initLabelReferences(symbol_table* table, labelTab *list);
void freeSymTab(symbol_table* table);
void freeLabelTab(labelTab *labTab);
symbol_table *codeGen(symbol_table *symtab, symbol_table *code);
int defineLen(symbol_table *symtab);
