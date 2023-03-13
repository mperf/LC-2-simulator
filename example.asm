	.orig	x3000
	lea	r0,array	;carica in R0 puntatore ad array
	and	r2,r2,#0	;azzera totalizzatore

ciclo	ldr	r1,r0,#0	; carica in R1 array(i)
	brz	fine		;se array(i) = 0 fine lavori
	add	r2,r1,r2
	add	r0,r0,#1	;si porta a elemento i+1
	brnzp	ciclo
fine	st	r2,result

stoqui	brnzp	stoqui

;area dati
array	.fill	15
	.fill	-27
	.fill	13
	.fill	15
	.fill	0	;tappo
result	.blkw	1
	.end