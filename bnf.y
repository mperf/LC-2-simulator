%token REGISTER
%token DIRECTIVE
%token THROP
%token TWOP
%token LABEL
%token NUMBERS
%token ORIG
%token COMMENT
%token JUMP
%token COMMA
%token ADDR

%start program

%%

program :   ORIG code {printf("input accepted");exit(0);}
        ;

code    :   twop 
        |   throp
        |   jump
        |   directive
        |   jsr
        |   twop COMMENT
        |   throp COMMENT
        |   jump  COMMENT
        |   directive COMMENT
        |   jsr COMMENT
        ;

twop    :   LABEL TWOP REGISTER COMMA ADDR
        |   LABEL TWOP REGISTER COMMA REGISTER
        |   TWOP REGISTER COMMA REGISTER
        |   TWOP REGISTER COMMA ADDR
        ;
    
throp   :   LABEL THROP REGISTER COMMA REGISTER COMMA REGISTER
        |   LABEL THROP REGISTER COMMA REGISTER COMMA NUMBERS
        |   
