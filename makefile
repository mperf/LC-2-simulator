lc2compile: main.c symbol_table.c tree.c semantics.c helper.c exec.c
	flex lexer.l
	yacc -v -d bnf.y
	gcc -g main.c y.tab.c lex.yy.c symbol_table.c tree.c semantics.c helper.c exec.c -o lc2
