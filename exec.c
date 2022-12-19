//fetch decode exec wb PRINT
//pc, cc, ir, r0-7
//ca2 numbers
// e se l'user è stupido e mi fa eseguire delle .fill o blkw?
/*
funzioni ausiliarie:
toCa2();
jumpConditionCheck();
to base16();
getOpcode();

int exec_code(symbol_table *code){
    int ir,pc,cc,r0-7
    while(istruzione non è la stessa per n volte)
        fetch(code);
        decode();
        exec();
        wb();
        printCommand();
    return 0;
}*/
#include <stdio.h>
#include <stdlib.h>
#include "structures.h"

int exec_code(symbol_table *code){
    short int ir=0,pc=0,r0=0,r1=0,r2=0,r3=0,r4=0,r5=0,r6=0,r7=0;
    char cc[4];
    printf("%d", atoi(code[1].token_val[1]));
    //pc=atoi(code[2].token_val);
    //pc+=11;
    //printf("program counter in hex: %X",pc);


}

int hexToInt(char *hex){
    //https://stackoverflow.com/questions/66358811/hex-to-int-conversion-in-c

    //moltiplicare posizione * 16 e sistemare
}