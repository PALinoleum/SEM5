.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA
      string DB "%d", 0
      num DW 500
      mas DD 8 DUP(1)
      ten DT 30000000
.CODE
START:
      XOR EAX, EAX
      MOV AX, num
      MOV BX, num
      MUL BX
      MOV BX, 10
      DIV BX
      XOR EDX, EDX
      MOV EDX, EAX
      ADD EDX, mas[0]
PUSH NULL
CALL ExitProcess
END START
