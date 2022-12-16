lc2compile: main.c y.tab.c lex.yy.c symbol_table.c ast.c semantics.c
	flex lexer.l
	yacc -v -d bnf.y
	gcc -ll -ly main.c y.tab.c lex.yy.c symbol_table.c ast.c semantics.c -o lc2
