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
//JUMP SBAGLIATE,NON CONTANO LO SHIFT
//SISTEMARE CA2 per bin
int exec_code(symbol_table *code, int opt,short int mode){
    short int end=0,base=0,shift=0,registers[9]={0,0,0,0,0,0,0,0,0};
    char cc, user;
    //r0-7 = registers[0] to [7], registers[8]= pc
    base=hexToInt(code[1].token_val);
    printInstr(registers[8],base,code,shift);
    registers[8]++; 
    shift++;
    while(!end){
        printInstr(registers[8],base,code,shift);
        
        if(strcmp(code[registers[8]+shift].type,"label")==0){
            registers[8]++;
        }
        
        if(strcmp(code[registers[8]+shift].token_val,"BR")==0){
            registers[8]=atoi(code[registers[8]+shift].token_val);
            registers[8]++;
            shift++;
        }else if(strcmp(code[registers[8]+shift].token_val,"ADD")==0){
            //shift++;
            //printf("si\n");
            //check if reg,hex,number,bin,
            //shift++;
            //printf("eh : %c",code[registers[8]+shift].token_val[0]);
            switch(code[registers[8]+shift+3].token_val[0]){
                case 'R':
                    registers[regNum(code[registers[8]+shift+1].token_val[1])]=registers[regNum(code[registers[8]+shift+2].token_val[1])]+registers[regNum(code[registers[8]+shift+3].token_val[1])];
                    break;
                case 'X':
                    registers[regNum(code[registers[8]+shift+1].token_val[1])]=registers[regNum(code[registers[8]+shift+2].token_val[1])]+hexToInt(code[registers[8]+shift+3].token_val);
                    break;
                case 'B':                     
                    registers[regNum(code[registers[8]+shift+1].token_val[1])]=registers[regNum(code[registers[8]+shift+2].token_val[1])]+binToInt(code[registers[8]+shift+3].token_val);
                    break;
                case '#':
                    registers[regNum(code[registers[8]+shift+1].token_val[1])]=registers[regNum(code[registers[8]+shift+2].token_val[1])]+numToInt(code[registers[8]+shift+3].token_val);
            }
            cc=checkCC(registers[regNum(code[registers[8]+shift+1].token_val[1])]);
            shift+=3;
        }else if(strcmp(code[registers[8]+shift].token_val,"LD")==0){

        }else if(strcmp(code[registers[8]+shift].token_val,"ST")==0){

        }else if(strcmp(code[registers[8]+shift].token_val,"JSR")==0){

        }else if(strcmp(code[registers[8]+shift].token_val,"AND")==0){

        }else if(strcmp(code[registers[8]+shift].token_val,"LDR")==0){

        }else if(strcmp(code[registers[8]+shift].token_val,"STR")==0){

        }else if(strcmp(code[registers[8]+shift].token_val,"RTI")==0){
            printf("instruction RTI not yet implemented.");
            end=1;
        }else if(strcmp(code[registers[8]+shift].token_val,"NOT")==0){

        }else if(strcmp(code[registers[8]+shift].token_val,"LDI")==0){

        }else if(strcmp(code[registers[8]+shift].token_val,"STI")==0){

        }else if(strcmp(code[registers[8]+shift].token_val,"JSRR")==0){
            printf("instruction JSRR not yet implemented.");
            end=1;

        }else if(strcmp(code[registers[8]+shift].token_val,"RET")==0){

        }else if(strcmp(code[registers[8]+shift].token_val,"LEA")==0){

        }else if(strcmp(code[registers[8]+shift].token_val,"TRAP")==0){
            printf("instruction TRAP not yet implemented.");
            end=1;

        }else if(strcmp(code[registers[8]+shift].token_val,".END")==0){
            end=1;
        }else{
            printf("internal error");
        }

        registers[8]++;

        if(opt==0 && !end){
            printf("> ");
            scanf("%c",&user);
            printf("\033[A"); //FIGATA!!!
            if(user=='r'){
                getchar();
                printRegisters(registers,base,cc);
            }else if(user>32){
                getchar();
            }
        }else if(opt==2 && !end){
            sleep(1);
            //printf("TEST fine sleep\n");
        }
        //printf("ciclo\n");
    }
printRegisters(registers,base,cc);
return 0;
}

void printRegisters(short int reg[],short int base,char cc){
    printf("\n");
    printf("R0=%d\tR1=%d\tR2=%d\tR3=%d\nR4=%d\tR5=%d\tR6=%d\tR7=%d\nCC=%c\tPC=%d (x%X)\n\n",reg[0],reg[1],reg[2],reg[3],reg[4],reg[5],reg[6],reg[7],cc,reg[8]+base-1,reg[8]+base-1);
}

char checkCC(short int result){
    char out;
    if(result>0){
        out='P';
    }else if(result<0){
        out='N';
    }else{
        out='Z';
    }
    return out;
}

int binToInt(char *bin){
    int i = 0,len,result = 0;
    for(len=0;bin[len]!='\0';len++);
    len-=2;
    for(i=1;bin[i]!='\0';i++){
        
        if(bin[i]=='1'){
            result+=powz(2,len);

        }
        len--;
    }
    return result;
}

int numToInt(char *num){
    if(num[1]=='-'){
        num[0]='-';
        num[1]='0';
    }else{
        num[0]='0';
    }
    return atoi(num);
}

//free symbol table

int hexToInt(char *hex){
    
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
        acc*=base;
    }
    return acc;
}

void printInstr(short int pc, short int base, symbol_table *code, short int shift){
    printf("%X\t",pc+base);
    do{
        printf("%s\t",code[pc+shift].token_val);
        pc++;
    }while(code[pc+shift].line_num==code[pc+shift+1].line_num);
    if(code[pc+shift].type!=0){
        printf("%s",code[pc+shift].token_val);
    }
    printf("\n");
}

int regNum(char reg){
    int number;

    switch(reg){

        case '0':
            number=0;
            break;

        case '1':
            number=1;
            break;

        case '2':
            number=2;
            break;

        case '3':
            number=3;
            break;

        case '4':
            number=4;
            break;

        case '5':
            number=5;
            break;

        case '6':
            number=6;
            break;

        case '7':
            number=7;
    }
    return number;
}