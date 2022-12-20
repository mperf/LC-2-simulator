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
#include "exec.h"

int exec_code(symbol_table *code, int opt){
    short int ir=0,pc=0,r0=0,r1=0,r2=0,r3=0,r4=0,r5=0,r6=0,r7=0,end=0,base=0,shift=0;
    char cc[4];
    base=hexToInt(code[1].token_val);
    pc=base;
    printInstr(pc,base,code);
    pc++;
    shift++;
    while(!end){
        printInstr(pc+shift,base,code);
        end++;
        if(pc==base+100){
            break;
        }
    }

return 0;
}

int hexToInt(char *hex){
    //https://stackoverflow.com/questions/66358811/hex-to-int-conversion-in-c
    int i = 0,len,result = 0;
    for(len=0;hex[len]!='\0';len++);
    len-=2;
    //printf("len: %d\n",len);
    for(i=1;hex[i]!='\0';i++){
        //printf("%c per len:%d\n",hex[i],len);
        switch (hex[i])
        {
        case 'A':
            result+=15*powz(16,len);
            break;

        case 'B':
            result+=15*powz(16,len);
            break;

        case 'C':
            result+=12*powz(16,len);
            break;

        case 'D':
            result+=13*powz(16,len);
            break;

        case 'E':
            result+=14*powz(16,len);
            break;

        case 'F':
            result+=15*powz(16,len);
            break;
        
        default:
        if((hex[i] - '0')==0){
            //printf("sis\n");
        }else{
            //printf("cosa: %d\n",(hex[i]- '0')*powz(16,len));
            result+=(hex[i]- '0')*powz(16,len);
        }
        }
        //printf("result: %d\n",result);
        len--;
    }
return result;
}

int powz(int base, int exp){
    int i=0,acc=1;
    for(i=0;i<exp;i++){
        acc*=16;
    }
    return acc;
}

void printInstr(short int pc, short int base, symbol_table *code){
    printf("%X\t",pc);
    do{
        printf("%s\t",code[pc-base].token_val);
        pc++;
    }while(code[pc-base].line_num==code[pc-1-base].line_num);
    printf("\n");
}