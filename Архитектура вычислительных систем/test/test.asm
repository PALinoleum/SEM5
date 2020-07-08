org 00h
	MOV P0, #1h
	MOV R1, P1
	MOV P0, #2h
	MOV R2, P1
	MOV P0, #4h
	MOV R3, P1
	MOV P0, #8h
	MOV R4, P1
start:
	MOV P0, #1h
	MOV R0, #1h
doWhile:
	MOV A, P1
	XRL A, @R0
	JZ notPrsd

	MOV @R0, P1
	MOV R5, #0h
getCol:
	INC R5
	RRC A
	JNZ getCol

	CJNE R5, #5, not5col
	MOV A, R0
	DEC A
	MOV B, #2
	MUL AB
	ADD A, #68
	JMP cout
not5col:
	CJNE R5, #4, not4col
	MOV A, R0
	DEC A
	MOV B, #2
	MUL AB
	ADD A, #67
	JMP cout 
not4col:
	CJNE R0, #4, not4r13c
	CJNE R5, #2, r4not2c
	MOV A, #48
	JMP cout
r4not2c:
	MOV A, #64
	ADD A, R5
	CJNE R5, #3, r4c1
	DEC A
r4c1:	JMP cout
not4r13c:
	MOV A, R0
	DEC A
	MOV B, #3
	MUL AB
	ADD A, #48
	ADD A, R5

cout:	CLR C
	MOV SBUF, A
	CLR TI
notPrsd:
	MOV A, P0
	RL A
	MOV P0, A
	INC R0
	JNB P0.4, doWhile
	JMP start
end