lc2compile: main.c y.tab.c lex.yy.c symbol_table.c ast.c semantics.c exec.c
	flex lexer.l
	yacc -v -d bnf.y
	gcc -ll -ly main.c y.tab.c lex.yy.c symbol_table.c ast.c semantics.c exec.c -o lc2
