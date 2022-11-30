lc2compile: main.c y.tab.c lex.yy.c
	flex lexer.l
	yacc -v -d bnf.y
	gcc -ll -ly main.c y.tab.c lex.yy.c -o o.out
