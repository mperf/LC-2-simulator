lc2compile: main.c symbol_table.c ast.c semantics.c helper.c exec.c
	flex lexer.l
	yacc -v -d bnf.y
	gcc -ll -ly -g main.c y.tab.c lex.yy.c symbol_table.c ast.c semantics.c helper.c exec.c -o lc2
