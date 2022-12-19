	.orig	x3000
	LEA	R1, iONE	;carico var
	LEA	R2, iTWO	;carico var
	JSR	COMPAR		;Salto a funzione
FINE	BRNZP	FINE

iONE	.fill	ONE
iTWO	.fill	TWo
ONe	.fill	b1010101010101011
TWO	.fill	35
b  .fill 2
a .blkw 1
.stringz"  "
.stringz" "
g .stringz" a"
.stringz"bbz "
z.blkw 1
.blkw 2
  .blkw 5
boh .stringz "ciao a tutti!!"
.stringz"alak"
.fill b1010101111111111
ah .blkw 5
.stringz "a"
COMPAR  LDR	R1,R1,#0
	LDR	R2,R2,#0
	LDR	R1,R1,#0
	LDR	R2,R2,#0
	NOT	R0, R1
	ADD	R0, R0, #1	;nego a ca2 r1 e lo metto in r0
	ADD	R0, R0, R2	;r0=-(r1)+r2
	BRN	PLUS		;salto al caso positivo
	BRP	NEG 		;salto al caso negativo
	RET			; non faccio caso z, tanto il risultato Ë gi‡ zero!
	
NEG	AND	R0, R0, #0
	AdD	R0, R0, #-1
	BRNZP	FINE

PLUS	AND	R0, R0, #0
	ADD	R0, R0, #1
	BRNZP	FINE
	.END