	.orig	x2000
	LEA	r0,array
	LD	r1,n1
	LD	r2,n2
	jsr	INTERVAL
stoqui	brnzp	stoqui

array .fill 6
      .fill -7
      .fill 3
      .fill 10
      .fill -8
      .fill -14
      .fill 0

n1    .fill 5
n2    .fill 10

INTERVAL ST r3,reg3
	ST r4,reg4
	ST r5,reg5
	ST r6,reg6
	AND R4,R4,#0
	AND R5,R5,#0
	AND R6,R6,#0

start	LDR R3,R0,#0
	brz fine
	brp change
check	ADD R0,R0,#1
	
	add r3,r3,r1
	brp case1

	not r1,r1
	add r1,r1,#1
	add r3,r3,r1
	not r1,r1
	add r1,r1,#1

	add r3,r3,r2
	brn case3
	brzp case2
	
case1 ADD R4,R4,#1
      brnzp start

case2 ADD R5,R5,#1
      brnzp start

case3 ADD R6,R6,#1
      brnzp start

fine  	AND R0,R0,#0
	AND R1,R1,#0
	AND R2,R2,#0

	ADD R0,R4,#0
	ADD R1,R5,#0
	ADD R2,R6,#0
	
	LD r3,reg3
	LD r4,reg4
	LD r5,reg5
	LD r6,reg6
	
	RET
	
change  not r3,r3
	ADD r3,r3,#1
	brnzp check

reg3 .blkw 1
reg4 .blkw 1
reg5 .blkw 1
reg6 .blkw 1

.END