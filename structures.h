#define MAX_PAGE 512

typedef struct {
        char * token_val;
        char * token;
        char * type;
        int line_num;
}symbol_table;

symbol_table *symtab;

