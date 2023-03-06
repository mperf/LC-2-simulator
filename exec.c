#include "exec.h"
#define PC registers[8]

int exec_code(symbol_table *code, int opt,short int mode){
    short int end=0,base=0,flag=0,temp=0,shift=0,lea=0,lsreg=0,retShift[10],retidx=0,registers[9]={0,0,0,0,0,0,0,0,0},len,i;
    char cc, user;
    //r0-7 = registers[0] to [7], PC= pc
    base=hexToInt(code[1].token_val)-1;
    //printInstr(PC,base,code,shift);
    PC++; 
    shift++;
    while(!end){
        printInstr(PC,base,code,shift);
        
        if(strcmp(code[PC+shift].type,"label")==0){
            shift++;
        }
        //          BR TUTTE
        if(code[PC+shift].token_val[0]=='B' && code[PC+shift].token_val[1]=='R'){

            for(len=0;code[PC+shift].token_val[len]!='\0';len++);

            for(i=2;i<=len && len!=10;i++){
                if(i==len){
                    flag=1;
                }

                if(flag==1 || code[PC+shift].token_val[i]==cc){
                    //tengo salvato lo shift per atoi
                    temp=shift;

                    //br sulla stessa riga
                    if(code[PC+shift].line_num==atoi(code[PC+shift+1].token_val)){
                        printf("\033[A\t\t\t%s\n",code[PC+shift-1].token_val);
                        end=1;
                        len=10;

                        //br con label sopra nel codice
                    }else if(code[PC+shift].line_num>atoi(code[PC+temp+1].token_val)){
                        while(len!=10){
                            shift--;
                            if(code[PC+shift].line_num==atoi(code[PC+temp+1].token_val) && code[PC+shift].line_num != code[PC+shift-1].line_num){
                                len=10;
                                if(strcmp(code[PC+temp-1].type,"label")==0 && code[PC+temp-1].line_num == code[PC+temp].line_num){
                                    printf("\033[A\t\t\t%s\n",code[PC+shift].token_val);
                                }else{
                                    printf("\033[A\t\t%s\n",code[PC+shift].token_val);
                                }
                            }
                        }

                        //br con label sotto nel codice
                    }else{
                        while(len!=10){
                            shift++;
                            if(code[PC+shift].line_num==atoi(code[PC+temp+1].token_val)){
                                len=10;
                                if(strcmp(code[PC+temp-1].type,"label")==0 && code[PC+temp-1].line_num == code[PC+temp].line_num){
                                    printf("\033[A\t\t\t%s\n",code[PC+shift].token_val);
                                }else{
                                    printf("\033[A\t\t%s\n",code[PC+shift].token_val);
                                }
                                
                            }
                        }
                    }

                    //faccio salto se necessario
                    if(!flag){
                        shift=PC+shift-atoi(code[PC+temp+1].token_val)+1;
                        PC=atoi(code[PC+temp+1].token_val)-2;
                    }else{
                        shift=temp;
                        shift++;
                    }
                    flag=0;
                }
            }
        temp=0;
            
        }else if(strcmp(code[PC+shift].token_val,"ADD")==0){

            switch(code[PC+shift+3].token_val[0]){
                case 'R':
                    registers[regNum(code[PC+shift+1].token_val[1])]=registers[regNum(code[PC+shift+2].token_val[1])]+registers[regNum(code[PC+shift+3].token_val[1])];
                    break;
                case 'X':
                    temp=hexToInt(code[PC+shift+3].token_val);
                    if(temp>15){
                        registers[regNum(code[PC+shift+1].token_val[1])]=0;
                    }else{
                        registers[regNum(code[PC+shift+1].token_val[1])]=registers[regNum(code[PC+shift+2].token_val[1])]+hexToInt(code[PC+shift+3].token_val);
                    }
                    break;
                case 'B':
                    temp=binToInt(code[PC+shift+3].token_val);
                    //printf("\n\ntemp: %d\n\n",temp);
                    if(temp>15 || temp<-15){
                        registers[regNum(code[PC+shift+1].token_val[1])]=0;
                    }else{                 
                    registers[regNum(code[PC+shift+1].token_val[1])]=registers[regNum(code[PC+shift+2].token_val[1])]+binToInt(code[PC+shift+3].token_val);
                    }
                    break;
                case '#':
                    //printf("\n\n coos? %s\n\n",code[PC+shift+3].token_val);
                    registers[regNum(code[PC+shift+1].token_val[1])]=registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val);
                    //printf("\n\n che succ? %s\n\n",code[PC+shift+3].token_val);
            }
            cc=checkCC(registers[regNum(code[PC+shift+1].token_val[1])]);
            shift+=3;



        }else if(strcmp(code[PC+shift].token_val,"LD")==0 || strcmp(code[PC+shift].token_val,"ST")==0 || strcmp(code[PC+shift].token_val,"LEA")==0){
            //printf("beh si\n\n\n");
            if(strcmp(code[PC+shift].token_val,"ST")==0){
                flag=1;
            }
            if(strcmp(code[PC+shift].token_val,"LEA")==0){
                lea=1;
            }
            temp=shift;
            len=0;
            //errore, sulla stessa riga
            if(code[PC+shift].line_num==atoi(code[PC+temp+2].token_val)){
                        printf("\033[A\t\t\t%s\n",code[PC+shift-1].token_val);
                        printf("\ninternal error\n");
                        end=1;
                        

                        //br con label sopra nel codice
                    }else if(code[PC+shift].line_num>atoi(code[PC+temp+2].token_val)){
                        while(len!=10){

                            shift--;
                            if(code[PC+shift].line_num==atoi(code[PC+temp+2].token_val) && code[PC+shift].line_num != code[PC+shift-1].line_num){
                                //rintf("\n\na%sa\n\n",code[PC+shift+1].token_val);
                                len=10;
                                //printf("coso: \"%d\"\n\n",strcmp(code[PC+shift+1].type,".blkw")==0);
                                if(!(strcmp(code[PC+shift+1].type,".blkw")==0) && !(strcmp(code[PC+shift+1].type,".stringz")==0) && !(strcmp(code[PC+shift+1].token_val,".FILL")==0) ){
                                
                                    printf("\ninternal error\n");
                                    end=1;
                                }else{
                                    //printf("\n\na%sa\n\n",code[PC+shift+1].type);
                                    if(strcmp(code[PC+shift+1].type,".stringz")==0){
                                        //printf("siii\n\n\n");
                                        if(flag){
                                            
                                            realloc(code[PC+shift+1].token_val, sizeof(char)*6);
                                            sprintf(code[PC+shift+1].token_val,"%c",(registers[regNum(code[PC+temp+1].token_val[1])]));
                                            //printf("salvato: %s\n\n",code[PC+shift+1].token_val);
                                        }else if(lea){
                                            //LINEA VECCHIA  registers[regNum(code[PC+temp+1].token_val[1])]=PC+shift+1+base;
                                            registers[regNum(code[PC+temp+1].token_val[1])]=(atoi(code[PC+temp+2].token_val)+base-1);
                                            //printf("staz a: %d\n\n",atoi(code[PC+temp+2].token_val)-1);
                                        }else{
                                            //printf("trovato: %c\n\n",code[PC+shift+1].token_val[0]);
                                            registers[regNum(code[PC+temp+1].token_val[1])]=code[PC+shift+1].token_val[0];
                                        }
                                    }else if(strcmp(code[PC+shift+1].type,".blkw")==0){
                                        if(flag){
                                            //printf("\n\nst\n\n");
                                            code[PC+shift+1].token_val=malloc(sizeof(char)*6);
                                            sprintf(code[PC+shift+1].token_val,"%d",registers[regNum(code[PC+temp+1].token_val[1])]);
                                            //code[PC+shift+1].token_val=registers[regNum(code[PC+temp+1].token_val[1])]+'0';
                                            //printf("salvato: %d\n\n",registers[regNum(code[PC+temp+1].token_val[1])]);
                                        }else if(lea){
                                            //LINEA VECCHIA  registers[regNum(code[PC+temp+1].token_val[1])]=PC+shift+1+base;
                                            registers[regNum(code[PC+temp+1].token_val[1])]=atoi(code[PC+temp+2].token_val)+base-1;
                                            //printf("sta a: %d\n\n",atoi(code[PC+temp+2].token_val));
                                        }else{
                                            if(code[PC+shift+1].token_val==NULL){
                                                registers[regNum(code[PC+temp+1].token_val[1])]=0;
                                            }else{
                                                registers[regNum(code[PC+temp+1].token_val[1])]=atoi(code[PC+shift+1].token_val);
                                            }
                                        }
                                        
                                    }else if(strcmp(code[PC+shift+1].token_val,".FILL")==0){

                                        if(flag){
                                            //printf("\n\nst\n\n");
                                            code[PC+shift+2].token_val=malloc(sizeof(char)*6);
                                            sprintf(code[PC+shift+2].token_val,"%d",registers[regNum(code[PC+temp+1].token_val[1])]);
                                        }else if(lea){
                                            //LINEA VECCHIA  registers[regNum(code[PC+temp+1].token_val[1])]=PC+shift+1+base;
                                            registers[regNum(code[PC+temp+1].token_val[1])]=atoi(code[PC+temp+2].token_val)+base-1;
                                            //printf("sta a: %d\n\n",atoi(code[PC+temp+2].token_val));
                                        }else{
                                            switch(code[PC+shift+2].token_val[0]){
                                                case 'X':
                                                    registers[regNum(code[PC+temp+1].token_val[1])]=hexToInt(code[PC+shift+2].token_val);
                                                    break;
                                                case 'B':
                                                    registers[regNum(code[PC+temp+1].token_val[1])]=binToInt(code[PC+shift+2].token_val);
                                                    break;
                                                default:
                                                if(atoi(code[PC+shift+2].token_val)>32767){
                                                    registers[regNum(code[PC+temp+1].token_val[1])]=0;
                                                }else{
                                                    registers[regNum(code[PC+temp+1].token_val[1])]=atoi(code[PC+shift+2].token_val);
                                                }
                                            }
                                            cc=checkCC(registers[regNum(code[PC+temp+1].token_val[1])]);
                                        }
                                        
            
                                    }
                                    //printf("nooo\n\n\n");
                                    if(strcmp(code[PC+temp-1].type,"label")==0 && code[PC+temp-1].line_num == code[PC+temp].line_num){
                                        printf("\033[A\t\t\t\t%s\n",code[PC+shift].token_val);
                                    }else{
                                        printf("\033[A\t\t\t%s\n",code[PC+shift].token_val);
                                    }

                                }
                            }
                        } 

                        //br con label sotto nel codice
                    }else{
                        //printf("here %d\n\n",len);
                        while(len!=10){
                            //printf("here\n\n");
                            shift++;
                            if(code[PC+shift].line_num==atoi(code[PC+temp+2].token_val) && code[PC+shift].line_num != code[PC+shift-1].line_num){
                                //rintf("\n\na%sa\n\n",code[PC+shift+1].token_val);
                                len=10;
                                //printf("si.\n");
                                //printf("coso: \"%d\"\n\n",strcmp(code[PC+shift+1].type,".blkw")==0);
                                if(!(strcmp(code[PC+shift+1].type,".blkw")==0) && !(strcmp(code[PC+shift+1].type,".stringz")==0) && !(strcmp(code[PC+shift+1].token_val,".FILL")==0) ){
                                
                                    printf("\ninternal error\n");
                                    end=1;
                                }else{
                                    //printf("\n\na%sa\n\n",code[PC+shift+1].type);
                                    if(strcmp(code[PC+shift+1].type,".stringz")==0){
                                        //printf("siii\n\n\n");
                                        if(flag){
                                            
                                            realloc(code[PC+shift+1].token_val, sizeof(char)*6);
                                            sprintf(code[PC+shift+1].token_val,"%c",(registers[regNum(code[PC+temp+1].token_val[1])]));
                                            //printf("salvato: %s\n\n",code[PC+shift+1].token_val);
                                        }else if(lea){
                                            //LINEA VECCHIA  registers[regNum(code[PC+temp+1].token_val[1])]=PC+shift+1+base;
                                            registers[regNum(code[PC+temp+1].token_val[1])]=(atoi(code[PC+temp+2].token_val)+base-1);
                                            //printf("stac a: %d\n\n",registers[regNum(code[PC+temp+1].token_val[1])]-base);
                                            //printf("a: %s\n\n",code[PC+shift+1].token_val);
                                        }else{
                                            //printf("trovato: %c\n\n",code[PC+shift+1].token_val[0]);
                                            registers[regNum(code[PC+temp+1].token_val[1])]=code[PC+shift+1].token_val[0];
                                        }
                                    }else if(strcmp(code[PC+shift+1].type,".blkw")==0){
                                        //printf("qui?\n\n");
                                        if(flag){
                                            //printf("\n\nst\n\n");
                                            code[PC+shift+1].token_val=malloc(sizeof(char)*6);
                                            sprintf(code[PC+shift+1].token_val,"%d",registers[regNum(code[PC+temp+1].token_val[1])]);
                                            //code[PC+shift+1].token_val=registers[regNum(code[PC+temp+1].token_val[1])]+'0';
                                            //printf("salvato: %d\n\n",registers[regNum(code[PC+temp+1].token_val[1])]);
                                        }else if(lea){
                                            //LINEA VECCHIA  registers[regNum(code[PC+temp+1].token_val[1])]=PC+shift+1+base;
                                            registers[regNum(code[PC+temp+1].token_val[1])]=(atoi(code[PC+temp+2].token_val)+base-1);
                                            //printf("sta a: %d\n\n",atoi(code[PC+temp+2].token_val));
                                        }else{
                                            if(code[PC+shift+1].token_val==NULL){
                                                registers[regNum(code[PC+temp+1].token_val[1])]=0;
                                            }else{
                                                registers[regNum(code[PC+temp+1].token_val[1])]=atoi(code[PC+shift+1].token_val);
                                            }
                                        }
                                        
                                    }else if(strcmp(code[PC+shift+1].token_val,".FILL")==0){
                                            //printf("almeno...\n\n");
                                        if(flag){
                                            //printf("\n\nst\n\n");
                                            code[PC+shift+2].token_val=malloc(sizeof(char)*6);
                                            sprintf(code[PC+shift+2].token_val,"%d",registers[regNum(code[PC+temp+1].token_val[1])]);
                                        }else if(lea){
                                            //LINEA VECCHIA  registers[regNum(code[PC+temp+1].token_val[1])]=PC+shift+1+base;
                                            registers[regNum(code[PC+temp+1].token_val[1])]=(atoi(code[PC+temp+2].token_val)+base-1);
                                            //printf("sta a: %d\n\n",atoi(code[PC+temp+2].token_val));
                                        }else{
                                            switch(code[PC+shift+2].token_val[0]){
                                                case 'X':
                                                    registers[regNum(code[PC+temp+1].token_val[1])]=hexToInt(code[PC+shift+2].token_val);
                                                    break;
                                                case 'B':
                                                    registers[regNum(code[PC+temp+1].token_val[1])]=binToInt(code[PC+shift+2].token_val);
                                                    break;
                                                default:
                                                //printf("num!: %d\n\n",atoi(code[PC+shift+2].token_val));
                                                if(atoi(code[PC+shift+2].token_val)>32767){
                                                    registers[regNum(code[PC+temp+1].token_val[1])]=0;
                                                }else{
                                                    registers[regNum(code[PC+temp+1].token_val[1])]=atoi(code[PC+shift+2].token_val);
                                                }
                                            }
                                            cc=checkCC(registers[regNum(code[PC+temp+1].token_val[1])]);
                                        }
                                        
            
                                    }else{
                                        printf("error\n\n");
                                    }
                                    //printf("nooo\n\n\n");
                                    if(strcmp(code[PC+temp-1].type,"label")==0 && code[PC+temp-1].line_num == code[PC+temp].line_num){
                                        printf("\033[A\t\t\t\t%s\n",code[PC+shift].token_val);
                                    }else{
                                        printf("\033[A\t\t\t%s\n",code[PC+shift].token_val);
                                    }

                                }
                            }
                        }
                    }
                    shift=temp;
                    cc=checkCC(registers[regNum(code[PC+shift+1].token_val[1])]);
                    shift+=2;
                    temp=0,len=0,flag=0,lea=0,lsreg=0;
            
        }else if(strcmp(code[PC+shift].token_val,"JSR")==0){
            
            temp=shift;
            //br sulla stessa riga
            if(code[PC+shift].line_num==atoi(code[PC+shift+1].token_val)){
                printf("\ninternal error\n");
                end=1;

                //br con label sopra nel codice
            }else if(code[PC+shift].line_num>atoi(code[PC+temp+1].token_val)){
                while(len!=10){
                    shift--;
                    if(code[PC+shift].line_num==atoi(code[PC+temp+1].token_val) && code[PC+shift].line_num != code[PC+shift-1].line_num){
                        len=10;
                        if(strcmp(code[PC+temp-1].type,"label")==0 && code[PC+temp-1].line_num == code[PC+temp].line_num){
                            printf("\033[A\t\t\t%s\n",code[PC+shift].token_val);
                        }else{
                            printf("\033[A\t\t%s\n",code[PC+shift].token_val);
                        }
                    }
                }

                //br con label sotto nel codice
            }else{
                while(len!=10){
                    shift++;
                    if(code[PC+shift].line_num==atoi(code[PC+temp+1].token_val)){
                        len=10;
                        if(strcmp(code[PC+temp-1].type,"label")==0 && code[PC+temp-1].line_num == code[PC+temp].line_num){
                            printf("\033[A\t\t\t%s\n",code[PC+shift].token_val);
                        }else{
                            printf("\033[A\t\t%s\n",code[PC+shift].token_val);
                        }
                        
                    }
                }
            }
            //controllare shift e altro

            registers[7]=PC+base;
            retShift[retidx]=temp+1;
            retidx++;
            shift=PC+shift-atoi(code[PC+temp+1].token_val)+1;
            PC=atoi(code[PC+temp+1].token_val)-2;
            temp=0,len=0;



        }else if(strcmp(code[PC+shift].token_val,"AND")==0){
            //printf("\n%d & %d=%d\n\n",registers[regNum(code[PC+shift+2].token_val[1])],numToInt(code[PC+shift+3].token_val),registers[regNum(code[PC+shift+2].token_val[1])]& numToInt(code[PC+shift+3].token_val));
            //lc2And(registers[regNum(code[PC+shift+2].token_val[1])],numToInt(code[PC+shift+3].token_val));
            //AND BIT A BIT ANCHE CA2
            switch(code[PC+shift+3].token_val[0]){
                case 'R':
                    registers[regNum(code[PC+shift+1].token_val[1])]=lc2And(registers[regNum(code[PC+shift+2].token_val[1])],registers[regNum(code[PC+shift+3].token_val[1])]);
                    break;
                case 'X':
                    temp=hexToInt(code[PC+shift+3].token_val);
                    if(temp<=15 || temp>=-15){
                        registers[regNum(code[PC+shift+1].token_val[1])]=0;
                    }else{
                        registers[regNum(code[PC+shift+1].token_val[1])]=lc2And(registers[regNum(code[PC+shift+2].token_val[1])],hexToInt(code[PC+shift+3].token_val));
                    }
                    break;
                case 'B':
                temp=binToInt(code[PC+shift+3].token_val);
                printf("bin: %d\n\n",binToInt(code[PC+shift+3].token_val));
                    if(temp>15 || temp<-15){
                        registers[regNum(code[PC+shift+1].token_val[1])]=0;
                    }else{
                    registers[regNum(code[PC+shift+1].token_val[1])]=lc2And(registers[regNum(code[PC+shift+2].token_val[1])],binToInt(code[PC+shift+3].token_val));
                    }
                    break;
                case '#':
                    registers[regNum(code[PC+shift+1].token_val[1])]=lc2And(registers[regNum(code[PC+shift+2].token_val[1])],numToInt(code[PC+shift+3].token_val));
            }
            cc=checkCC(registers[regNum(code[PC+shift+1].token_val[1])]);
            shift+=3;
        

        }else if(strcmp(code[PC+shift].token_val,"LDR")==0){
            //printf("tipoz: %d\n\n",registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base+1);
            temp=0;
            //if(code[registers])
            //printf("tipso: %d\n",code[PC+temp].line_num);
            while(code[temp].line_num != registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base+1 ){
                //printf("tipo: %d\n",code[temp].line_num);
                temp++;
            }
            
            if(strcmp(code[temp].type,"label")==0){
                temp++;
            }
            
            //printf("tipo: %s, l: %d\n\n",code[temp].type,registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base+1);
            

            if(strcmp(code[temp].type,".stringz")==0){
                registers[regNum(code[PC+shift+1].token_val[1])] = code[temp].token_val[0];
                

            }else if(strcmp(code[temp].type,".blkw")==0){

                if(code[temp].token_val==NULL){
                    registers[regNum(code[PC+shift+1].token_val[1])]=0;
                    //printf("LDR err\n\n");
                }else{
                    //printf("\n\naaa: %d\n\n",atoi(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base].token_val));
                    registers[regNum(code[PC+shift+1].token_val[1])]=atoi(code[temp].token_val);
                }

            }else if(strcmp(code[temp].token_val,".FILL")==0){

                switch(code[temp+1].token_val[0]){
                    case 'X':
                        registers[regNum(code[PC+shift+1].token_val[1])]=hexToInt(code[temp+1].token_val);
                        break;
                    case 'B':
                        registers[regNum(code[PC+shift+1].token_val[1])]=binToInt(code[temp+1].token_val);
                        break;
                    default:
                    if(atoi(code[temp+1].token_val)>32767){
                        registers[regNum(code[PC+shift+1].token_val[1])]=0;
                        printf("LDR err\n\n");
                    }else{
                        //printf("trovato: %d\n\n",atoi(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base+1].token_val));
                        registers[regNum(code[PC+shift+1].token_val[1])]=atoi(code[temp+1].token_val);
                    }
                }

            }else{
                printf("LDR error\n\n");
            }
            cc=checkCC(registers[regNum(code[PC+shift+1].token_val[1])]);
            if(registers[regNum(code[PC+shift+1].token_val[1])]=='0'){
                cc='Z';
            }

            // if(strcmp(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base].type,".stringz")==0){
            //     registers[regNum(code[PC+shift+1].token_val[1])] = code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base].token_val[0];

            // }else if(strcmp(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base].type,".blkw")==0){

            //     if(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base].token_val==NULL){
            //         registers[regNum(code[PC+shift+1].token_val[1])]=0;
            //         //printf("LDR err\n\n");
            //     }else{
            //         //printf("\n\naaa: %d\n\n",atoi(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base].token_val));
            //         registers[regNum(code[PC+shift+1].token_val[1])]=atoi(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base].token_val);
            //     }

            // }else if(strcmp(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base].token_val,".FILL")==0){

            //     switch(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base+1].token_val[0]){
            //         case 'X':
            //             registers[regNum(code[PC+shift+1].token_val[1])]=hexToInt(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base+1].token_val);
            //             break;
            //         case 'B':
            //             registers[regNum(code[PC+shift+1].token_val[1])]=binToInt(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base+1].token_val);
            //             break;
            //         default:
            //         if(atoi(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base+1].token_val)>32767){
            //             registers[regNum(code[PC+shift+1].token_val[1])]=0;
            //             printf("LDR err\n\n");
            //         }else{
            //             //printf("trovato: %d\n\n",atoi(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base+1].token_val));
            //             registers[regNum(code[PC+shift+1].token_val[1])]=atoi(code[registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base+1].token_val);
            //         }
            //     }

            // }else{
            //     printf("LDR error\n\n");
            // }
            shift+=3,flag=0,len=0,temp=0;


        }else if(strcmp(code[PC+shift].token_val,"STR")==0){
            temp=0;
            //if(code[registers])
            //printf("tipso: %d\n",code[PC+temp].line_num);
            while(code[temp].line_num != registers[regNum(code[PC+shift+2].token_val[1])]+numToInt(code[PC+shift+3].token_val)-base+1 ){
                //printf("tipo: %d\n",code[temp].line_num);
                temp++;
            }
            
            if(strcmp(code[temp].type,"label")==0){
                temp++;
            }

           //printf("stuff: %d\n\n",registers[regNum(code[PC+shift+2].token_val[1])]-base+numToInt(code[PC+shift+3].token_val));
            if(strcmp(code[temp].type,".stringz")==0){
                //registers[regNum(code[PC+shift+1].token_val[1])] = [0];
                realloc(code[temp].token_val,sizeof(char)*2);
                sprintf(code[temp].token_val,"%c",registers[regNum(code[PC+shift+1].token_val[1])]);
                printf("messo: %s\n\n",code[temp].token_val);
                cc=checkCC(atoi(code[temp+1].token_val));
                if((code[temp+1].token_val[0])=='0'){
                    cc='Z';
                }
            }else if(strcmp(code[temp].type,".blkw")==0){

                realloc(code[temp].token_val,sizeof(char)*6);
                sprintf(code[temp].token_val,"%d",registers[regNum(code[PC+shift+1].token_val[1])]);
                 printf("messob: %s\n\n",code[temp].token_val);
                cc=checkCC(atoi(code[temp+1].token_val));
            }else if(strcmp(code[temp].token_val,".FILL")==0){
            
                realloc(code[temp+1].token_val,sizeof(char)*6);
                sprintf(code[temp+1].token_val,"%d",registers[regNum(code[PC+shift+1].token_val[1])]);
                 printf("messof: %s\n\n",code[temp].token_val);
                cc=checkCC(atoi(code[temp+1].token_val));
                
            }else{
                printf("STR error\n\n");
            }
            shift+=3,temp=0,len=0;

        }else if(strcmp(code[PC+shift].token_val,"RTI")==0){
            printf("instruction RTI not yet implemented.");
            end=1;
        }else if(strcmp(code[PC+shift].token_val,"NOT")==0){

            registers[regNum(code[PC+shift+1].token_val[1])]=~(registers[regNum(code[PC+shift+2].token_val[1])]);
        shift+=2;
        }else if(strcmp(code[PC+shift].token_val,"LDI")==0){
            printf("pages not yet implemented.");
            end=1;

        }else if(strcmp(code[PC+shift].token_val,"STI")==0){
            printf("pages not yet implemented.");
            end=1;
        }else if(strcmp(code[PC+shift].token_val,"JSRR")==0){
            printf("instruction JSRR not yet implemented.");
            end=1;

        }else if(strcmp(code[PC+shift].token_val,"RET")==0){
            PC=registers[7]-base;
            retidx--;
            shift=retShift[retidx];
            
        }else if(strcmp(code[PC+shift].token_val,"TRAP")==0){
            printf("instruction TRAP not yet implemented.");
            end=1;

        }else if(strcmp(code[PC+shift].token_val,".END")==0){
            end=1;
        }else{
            printf("internal error");
            end=1;
        }

        PC++;

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

short int lc2And(short int one, short int two){
   //printf("one: %d two: %d\n",one,two);
    char *first,*second;
    //int res[16];
    short int i,result=0;

    first=malloc(sizeof(char)*17);
    second=malloc(sizeof(char)*17);
    toCa2(one,first);
    toCa2(two,second);
    for (i=0;i<16;i++){
         //printf("out: %d\n",(first[i]=='1' && second[i]=='1'));
         if((first[i]=='1' && second[i]=='1')){
            //printf("idx: %d\n",i);
            result+=powz(2,i);
         }
    }
    
    //perchè funziona? Grazie all'overflow dello short !!! numeri negativi corretti!
    //printf("\nres: %d\n",result);
    return result;

}

void toCa2(short one, char *first){
    int i;

    if(!(one >=0)){
        //one--;
        one=~(one);
        for(i=0;i<16;i++){
            if(one%2==0){
                first[i]='1';
            }else if(one%2==1){
                first[i]='0';
            }
            //printf("second: %c, mass: %d\n",first[i], one);
            one=one/2;
            
        }
        //printf("\n\n\n");
    }else{
        for(i=0;i<16;i++){
            if(one%2==0){
                first[i]='0';
            }else if(one%2==1){
                first[i]='1';
            }
            //printf("second: %c, mass: %d\n",first[i], one);
            one=one/2;
        }
        //printf("\n\n");
    }

}


//ca2 binary
int binToInt(char *bin){

    int i = 0,len,result = 0,n=0;
    for(len=0;bin[len]!='\0';len++);
    len-=2;
    if(bin[1]=='1'){
        len--;
        for(i=2;bin[i]!='\0';i++){
        //ca2
        if(bin[i]=='0'){
            result+=powz(2,len);

        }
        len--;
    }
    result=result-(2*result);
    result--;
    }else{
        for(i=1;bin[i]!='\0';i++){
        //ca2
        if(bin[i]=='1'){
            result+=powz(2,len);

        }
        len--;
    }
    }
    
    return (result);
}

short int numToInt(char *num){
    int i,j;
    char *str;
    for(i=0;num[i]!='\0';i++);
    //printf("\n\nlen: %d\n\n",i);
    str=malloc(sizeof(char)*i);
    if(num[1]=='-'){
        str[0]='-';
        for(j=1;j<i;j++){
        //printf("num:%d\n\n",num[j+1]);
        str[j]=num[j+1];
    }
    }else{
        for(j=0;j<i;j++){
        str[j]=num[j+1];
        //printf("num:%d\n\n",num[j+1]);
        }
    }
    //printf("\n ris: %d\n\n",atoi(str));
    return atoi(str);
}


short int hexToInt(char *hex){
    
    int i = 0,len,result = 0;
    for(len=0;hex[len]!='\0';len++);
    len-=2;
    //printf("len: %d\n",len);
    for(i=1;hex[i]!='\0';i++){
        //printf("%c per len:%d\n",hex[i],len);
        switch (hex[i])
        {
        case 'A':
            printf("si\n\n\n");
            result+=10*powz(16,len);
            break;

        case 'B':
            result+=11*powz(16,len);
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
    //printf("res: %d\n\n",result);
    if(result>32767){
        result=0;
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
    printf("x%X\t",pc+base);
    do{
        printf("%s\t",code[pc+shift].token_val);
        pc++;
    }while(code[pc+shift].line_num==code[pc+shift-1].line_num);
    //non so perchè l'avevo messo
    /*if(code[pc+shift].type!=0 ){
        printf("a%s",code[pc+shift].token_val);
    }*/
    printf("\n");
}

int regNum(char reg){
    int number=0;

    return number=reg-48;
}