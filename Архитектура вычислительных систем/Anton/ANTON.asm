.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA
      Mas DW 10,12,14,16
      
.CODE
START:
	XOR EAX, EAX
      MOV AX, Mas[0]
      MOV BX, Mas[2]
      MUL BX
      MOV CX, AX
      MOV AX, Mas[4]
      MOV BX, Mas[6]
      MUL BX
      ADD AX,CX
      MOV ESI,EAX
PUSH NULL
CALL ExitProcess
END START
