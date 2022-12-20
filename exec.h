#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

int exec_code(symbol_table *code, int opt);
int hexToInt(char *hex);
int powz(int base, int exp);
void printInstr(short int pc, short int base, symbol_table *code);

const char opcodes[16][5]={"BR","ADD","LD","ST","JSR","AND","LDR","STR","RTI","NOT","LDI","STI","JSRR","RET","LEA","TRAP"};