#include <stdio.h>
#include <strings.h>

#include "defaults.h"
#include "structures.h"
#include "proto.h"

#include "check.c"


int main(int argc, char const *argv[]){
    /*
    "print"				   {return print;}
"exit"				   {return exit_command;}
[a-zA-Z]			   {yylval.id = yytext[0]; return identifier;}
[0-9]+                 {yylval.num = atoi(yytext); return number;}
[ \t\n]                ;
[-+=;]           	   {return yytext[0];}
.                      {ECHO; yyerror ("unexpected character");}
    
    FILE *fp;
    fp=fopen(argv[1],"r");

    printf("%s\n",LCopcodes[7]);
    printf("\n\n\n%d\n",check(fp));*/

    extern int yylex();

    int ntoken;

    ntoken=yylex();
    while(ntoken){

        printf("%d\n",ntoken);
        ntoken=yylex();
    }



    return 0;
}
