#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#if __linux__
    #include <string.h>
#else
    #include <strings.h>
#endif
#include "structures.h"

int exec_code(symbol_table *code, int opt,short int mode);
short int hexToInt(char *hex);
int powz(int base, int exp);
int regNum(char reg);
int binToInt(char *bin);
short int numToInt(char *num);
short int lc2And(short int one, short int two);
void toCa2(short one, char *first);
void printRegisters(short int reg[], short int base,char cc);
char checkCC(short int result);
void printInstr(short int pc, short int base, symbol_table *code, short int shift);

const char opcodes[16][5]={"BR","ADD","LD","ST","JSR","AND","LDR","STR","RTI","NOT","LDI","STI","JSRR","RET","LEA","TRAP"};