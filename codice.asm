	.orig	x3000
	LEA	R1, ONE		;carico var
	LEA	R2, TWO		;carico var
	JSR	COMPAR		;Salto a funzione
FINE	BRNZP	FINE

ONE	.fill	34
TWO	.fill	3

COMPAR  LDR	R1,R1,#0
	LDR	R2,R2,#0
	NOT	R0, R1
	ADD	R0, R0, #1	;nego a ca2 r1 e lo metto in r0
	ADD	R0, R0, R2	;r0=-(r1)+r2
	BRN	PLUS		;salto al caso positivo
	BRP	NEG 		;salto al caso negativo
	RET			; non faccio caso z, tanto il risultato Ë gi‡ zero!
	
NEG	AND	R0, R0, #0
	ADD	R0, R0, #-1
	BRNZP	FINE

PLUS	AND	R0, R0, #0
	ADD	R0, R0, #1
	BRNZP	FINE
	.END