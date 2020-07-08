.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA
     one db 0ffh, 0ffh, 0ffh, 0ffh, 0ffh, 0ffh, 0ffh, 0ffh
     two db 0ffh, 0ffh, 0ffh, 0ffh, 0ffh, 0ffh, 0ffh, 0ffh

     
     s db 0, 0, 0, 0, 0, 0, 0, 0
     d db 0, 0, 0, 0, 0, 0, 0, 0
     e db 0, 0, 0, 0, 0, 0, 0, 0
     f db 0, 0, 0, 0, 0, 0, 0, 0

     res db 16 dup(0)
.CODE
START:
      XOR EAX, EAX
      XOR EBX, EBX

      MOV EAX, dword ptr one[0]
      MOV EBX, dword ptr two[0]
      MUL EBX
      MOV dword ptr s[0], EAX
      MOV dword ptr s[4], EDX

      MOV EAX, dword ptr one[4]
      MOV EBX, dword ptr two[0]
      MUL EBX
      MOV dword ptr d[0], EAX
      MOV dword ptr d[4], EDX

      MOV EAX, dword ptr one[0]
      MOV EBX, dword ptr two[4]
      MUL EBX
      MOV dword ptr e[0], EAX
      MOV dword ptr e[4], EDX

      MOV EAX, dword ptr one[4]
      MOV EBX, dword ptr two[4]
      MUL EBX
      MOV dword ptr f[0], EAX
      MOV dword ptr f[4], EDX

      MOV EAX, dword ptr s[0]
      MOV dword ptr res[0], EAX

      MOV EAX, dword ptr s[4]
      MOV EBX, EAX
      ADD EAX, dword ptr d[0]
      MOV EBX, EAX
      MOV EAX, dword ptr res[8]
      ADC EAX, 0
      MOV dword ptr res[8], EAX
      MOV EAX, dword ptr res[12]
      ADC EAX, 0
      MOV dword ptr res[12], EAX
      MOV EAX, EBX
      ADD EAX, dword ptr e[0]
      MOV EBX, EAX
      MOV EAX, dword ptr res[8]
      ADC EAX, 0
      MOV dword ptr res[8], EAX
      MOV EAX, dword ptr res[12]
      ADC EAX, 0
      MOV dword ptr res[12], EAX
      MOV dword ptr res[4], EBX

      MOV EAX, dword ptr res[8]
      ADD EAX, dword ptr d[4]
      MOV EBX, EAX
      MOV EAX, dword ptr res[12]
      ADC EAX, 0
      MOV dword ptr res[12], EAX
      MOV EAX, EBX
      ADD EAX, dword ptr e[4]
      MOV EBX, EAX
      MOV EAX, dword ptr res[12]
      ADC EAX, 0
      MOV dword ptr res[12], EAX
      MOV EAX, EBX
      ADD EAX, dword ptr f[0]
      MOV dword ptr res[8], EAX
      MOV EAX, dword ptr res[12]
      ADC EAX, 0
      MOV dword ptr res[12], EAX

      MOV EAX, dword ptr res[12]
      ADD EAX, dword ptr f[4]
      MOV dword ptr res[12], EAX

      PUSH NULL
      CALL ExitProcess
END START
