.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA
      a db '5'
      b db '4'
      msg db "sum of x and y is ", 0
.CODE
START:
      XOR EAX, EAX
	MOV AL, [a]
      SUB EAX, '0'
      XOR EBX, EBX
      MOV BL, [b]
      SUB EBX, '0'
      ADD EAX, EBX
      ADD EAX, '0'
PUSH NULL
CALL ExitProcess
END START
