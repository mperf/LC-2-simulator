#define MAX_PAGE 512

typedef struct {
        char * token_val;
        char * token;
        char * type;
        int line_num;
        int times;
}symbol_table;

typedef struct {
    char name[20];
    struct listLabels *next;
}listLabels;


symbol_table symtab[MAX_PAGE];