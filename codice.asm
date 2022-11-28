	.orig	x3000
; se la somma di due numeri con lo stesso segno danno l'altro allora over under flow
	LD	R1,ONE
	LD	R2,TWO
	JSR	SUM	;Salto a funzione
FINE	BRNZP	FINE

ONE	.fill	-30000
TWO	.fill	-30000
FIRST	.fill	b1000000000000000

SUM	LD	R6,FIRST
	ADD	R1,R1,R2
	AND	R3,R1,R6
	AND 	R4,R2,R6
	BRZ	PLUST
;DEVO OTTENERE UNA XOR: not(notA and notB) and not(A and B)
BACKT	AND	R5,R3,R4
	BRZ	PLUS    
BACK	NOT	R5,R5
	NOT	R4,R4
	NOT	R3,R3
	AND	R3,R3,R4
	NOT	R3,R3
	AND	R3,R3,R5
;fine XOR (su r3)
	ADD	R0,R3,#0
	BRZ	CON
	AND	R0,R0,#0
FIN	RET	

PLUS	ADD	R5,R5,#1
	BRNZP	BACK

PLUST	ADD	R4,R4,#1
	BRNZP	BACKT		
	
CON	ADD 	R2,R2,#0
	BRN	NEG
	ADD	R1,R1,#0
	BRN	OVER
	AND	R0,R0,#0
	BRNZP	FIN


OVER	AND 	R0,R0,#0
	ADD	R0,R0,#1
	BRNZP	FIN

NEG	ADD	R1,R1,#0
	BRP	UNDER
	AND	R0,R0,#0
	BRNZP 	FIN

UNDER	AND	R0,R0,#0
	ADD	R0,R0,#-1
	.end