.386 
.model flat, stdcall 
option casemap: none 

include c:\masm32\include\windows.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\user32.inc
includelib c:\masm32\lib\user32.lib
includelib c:\masm32\lib\kernel32.lib

.DATA
	as DB 10, 13, "a-s", 0
	h DW 20
	w DW 100
	s DD ?
	DT 17834.55
.CODE
START:
	MOV BP, 101111010101b
	AND WORD PTR [EBP+2F2h], 23
	ADD [EBX*8+EDI+'i'], EAX
	CMP DL, [EDI*4]
	SBB CX, AX
	ADD EBX, [EBX+02h]

END START
