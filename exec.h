#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <strings.h>
#include "structures.h"

int exec_code(symbol_table *code, int opt,short int mode);
int hexToInt(char *hex);
int powz(int base, int exp);
int regNum(char reg);
int binToInt(char *bin);
int numToInt(char *num);
void printRegisters(short int reg[], short int base,char cc);
char checkCC(short int result);
void printInstr(short int pc, short int base, symbol_table *code, short int shift);

const char opcodes[16][5]={"BR","ADD","LD","ST","JSR","AND","LDR","STR","RTI","NOT","LDI","STI","JSRR","RET","LEA","TRAP"};