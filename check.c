#include <stdio.h>



int check(FILE *code){
    int check=0,lines=0,codes,z;
    char line[BUFSIZ];
    while(!feof(code)){
        fgets(line,BUFSIZ,code);
        //for(z=0;line[z]!='\0';z++){
            //printf("son qui\n");
            //printf("debug: %c\n",line[z]);
        //}
        //printf("%d\n",z);
        codes=firstcheck(line);
        if(codes==1){
            lines++;
        }if(code<0){
            printf("errore\n");
            return -1;
        }
        check=1;
    }
    
//usare come registri uno short (16 bit)

//qui verificare se una linea è vuota e nel caso non inserirla

//aumentare limite labels
//primo passaggio: trovo n, malloc di array di linee con n, passo per reference il puntatore e riempio dal check 2
//verificare che se, un'istruzione è ripetuta troppe volte, non sia un ciclo infinito

    return 1;
}


int firstcheck(char *line){
    int i,j,n=0,opcode=0;
    char car;
    printf("inizia printf\n");
    for(n=0;line[n]!=';' && line[n]!='\0';n++){

        printf("debug: %d \t %c\n",n,line[n]);

    }
    printf("ho finito\n");
    if(n==0){
        printf("debug: linea vuota");
        return 2;
    }
    //for(n=0;line[n]!=' ';n++);
    //for(j=n;line[j]!=' ' || line[j]!=';';j++);
    //if(j<9){

    //}
    return 1;
}