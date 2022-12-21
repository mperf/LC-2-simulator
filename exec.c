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
//se facessi array di tutti i registri e li passassi a una funzione? assignToReg(LEA());
int exec_code(symbol_table *code, int opt,short int mode){
    short int pc=0,r0=0,r1=0,r2=0,r3=0,r4=0,r5=0,r6=0,r7=0,end=0,base=0,shift=0;
    char cc[4], user;

    base=hexToInt(code[1].token_val);
    printInstr(pc,base,code,shift);
    pc++;
    shift++;
    while(!end){
        printInstr(pc,base,code,shift);
        
        if(strcmp(code[pc+shift].type,"label")==0){
            pc++;
        }
        
        if(strcmp(code[pc+shift].token_val,"BR")==0){

        }else if(strcmp(code[pc+shift].token_val,"ADD")==0){

        }else if(strcmp(code[pc+shift].token_val,"LD")==0){

        }else if(strcmp(code[pc+shift].token_val,"ST")==0){

        }else if(strcmp(code[pc+shift].token_val,"JSR")==0){

        }else if(strcmp(code[pc+shift].token_val,"AND")==0){

        }else if(strcmp(code[pc+shift].token_val,"LDR")==0){

        }else if(strcmp(code[pc+shift].token_val,"STR")==0){

        }else if(strcmp(code[pc+shift].token_val,"RTI")==0){

        }else if(strcmp(code[pc+shift].token_val,"NOT")==0){

        }else if(strcmp(code[pc+shift].token_val,"LDI")==0){

        }else if(strcmp(code[pc+shift].token_val,"STI")==0){

        }else if(strcmp(code[pc+shift].token_val,"JSRR")==0){

        }else if(strcmp(code[pc+shift].token_val,"RET")==0){

        }else if(strcmp(code[pc+shift].token_val,"LEA")==0){

        }else if(strcmp(code[pc+shift].token_val,"TRAP")==0){

        }else if(strcmp(code[pc+shift].token_val,".end")==0){
            end=1;
        }else{
            printf("internal error");
        }
        
        pc++,pc+=2;
        //printf("%s",code[pc+shift].token_val);
        printInstr(pc,base,code,shift);
        if(opt==0){
            printf("<LC2> ");
            scanf("%c",&user);
            printf("\n");
            //...implement logic
        }else if(opt==2){
            sleep(1);
            printf("TEST fine sleep\n");
        }
        end++;
    }
    //print registri

return 0;
}



//free symbol table
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

void printInstr(short int pc, short int base, symbol_table *code, short int shift){
    printf("%X\t",pc+base);
    do{
        printf("%s\t",code[pc+shift].token_val);
        pc++;
    }while(code[pc+shift].line_num==code[pc+shift+1].line_num);
    printf("%s",code[pc+shift].token_val);
    printf("\n");
}