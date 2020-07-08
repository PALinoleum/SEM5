.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA
     one db 65, 76, 0Fh, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 
     two db 3, 6, 0Bh, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0

     res db 15 dup(0)
.CODE
START:

      MOV EAX, dword ptr one[0]
      ADD EAX, dword ptr two[0]
      MOV dword ptr res[0], EAX

      MOV EAX, dword ptr one[4]
      ADC EAX, dword ptr two[4]
      MOV dword ptr res[4], EAX

      MOV EAX, dword ptr one[8]
      ADC EAX, dword ptr two[8]
      MOV dword ptr res[8], EAX

      MOV AX, word ptr one[12]
      ADC AX, word ptr two[12]
      MOV word ptr res[12], AX

      PUSH NULL
      CALL ExitProcess
END START
