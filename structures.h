#define MAX_PAGE 512

typedef struct {
        char * token_val;
        char * token;
        int line_num;
}symbol_table;

symbol_table symtab[MAX_PAGE];