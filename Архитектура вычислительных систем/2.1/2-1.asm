.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA

.CODE
START:
      OR BYTE PTR [EDI*2+8], 9
      OR BYTE PTR [EDI*2+EBP+8], 9
      OR BYTE PTR [EDI*2+ESI+8], 9

      MOV ESI, EAX
      MOV BX, 18
      PUSH NULL
      CALL ExitProcess
END START
