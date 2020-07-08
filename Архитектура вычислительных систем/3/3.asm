.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA
      a db 84
      b db -52
      d db 34
      x dw -1864

      save db 8 dup(0)
.CODE
START:
      XOR EAX, EAX
      XOR EBX, EBX 
      XOR ECX, ECX
      XOR EDX, EDX

      MOVSX ECX, a                  ; ������ � ����������� � ECX ����� �� a
      MOVSX EAX, x                  ; ������ � ����������� � EAX ����� �� x
      IMUL ECX                      ; ��������� EAX �� ECX, ��������� � EAX     ; a*x
      MOV EBX, EAX                  ; ������ ������ �� EAX � EBX

      MOVSX ECX, b                  ; ������ � ����������� � ECX ����� �� b
      MOVSX EAX, x                  ; ������ � ����������� � EAX ����� �� x
      IMUL EAX                      ; ��������� EAX �� EAX, ��������� � EAX     ; x^2
      IMUL ECX                      ; ��������� EAX �� ECX, ��������� � EDX:EAX ; b*x^2
      ADD EAX, EBX                  ; �������� EAX � EBX, ��������� � EAX       ;
      ADC EDX, 0                    ; �������� EDX � ������������               ; a*x+b*x^2

      MOV dword ptr save(0), EDX    ; ������� ������ �� EDX � ������ save(0)
      MOV dword ptr save(4), EAX    ; ������� ������ �� EAX � ������ save(4)

      MOVSX ECX, d                  ; ������ � ����������� � ECX ����� �� d
      MOVSX EAX, x                  ; ������ � ����������� � EAX ����� �� x
      IMUL ECX                      ; ��������� EAX �� ECX, ��������� � EAX     ; d*x
      MOV ECX, EAX                  ; ������� ������ �� EAX � ECX
      MOVSX EAX, x                  ; ������ � ����������� � EAX ����� �� x
      IMUL EAX                      ; ��������� EAX �� EAX, ��������� � EAX     ; x^2
      IMUL ECX                      ; ��������� EAX �� ECX, ��������� � EDX:EAX ; d*x^3
      ADD EAX, dword ptr save(4)    ; �������� EAX � ������� ������ save(4)     ;
      ADC EDX, 0                    ; �������� EDX � ������������               ; a*x+b*x^2+d*x^3
      ADD EDX, dword ptr save(0)    ; �������� EDX � ������� ������ save(0)     ;

      SUB EAX, 14*14*14             ; �������� EAX ���������, ��������� � EAX   ; a*x+b*x^2+d*x^3-14^3
      CMP EAX, 0                    
      JG exit                       ; �����, ���� EAX > 0
      CMP EDX, 0
      JE exit                       ; �����, ���� EDX <> 0
      CDQ                           ; �������� ��������� ������� � ����������� �������� EDX:EAX
     
exit: PUSH NULL
      CALL ExitProcess              ; ���������� ���������
END START
