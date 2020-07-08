.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA
      reg dw 0 ; 6F00h ; 7000h ; 714Fh
               ;   c1  ;   c2  ;   c3
.CODE
START:
      XOR EAX, EAX
      XOR EBX, EBX  ; ��������� ������� ���������
      XOR ECX, ECX

      MOV AX, reg   ; ��������� ������ � ������� AX ������ �� ������� ������ reg
      
      MOV BX, AX    ; ��������� �������� AX � ������� BX
      
      CMP AH, 111   ; ��������� ������ �������� AH � ������������� ����� 111 (6Fh)
      JZ c1         ; ���� ��������� ���������� ������� ����� ����, ������� � ����� c1

      CMP AH, 112   ; ��������� ������ �������� AH � ������������� ����� 112 (70h)
      JZ c2         ; ���� ��������� ���������� ������� ����� ����, ������� � ����� c2

      CMP AH, 113   ; ��������� ������ �������� AH � ������������� ����� 113 (71h)
      JGE c3        ; ���� ��������� ������ ��� ����� 113, ������� � ����� c3

      JMP exit      ; ������� � ����� ������

  c1: MOVZX AX, BH  ; ��������� � ����������� ������ ����� �������� BH � ������� AX
      MUL AL        ; ������������� ��������� AL �� AL, ��������� � AX
      JMP exit      ; ������� � ����� ������

  c2: MOVZX AX, BH  ; ��������� � ����������� ������ ����� �������� BH � ������� AX
      XOR BX, BX    ; ������� �������� BX
      MOV BL, 8     ; ��������� � ������� BL ����������� ����� 8
      DIV BL        ; ������� �������� AX �� BL, ������� � AL, ������� � AH
      JMP exit      ; ������� � ����� ������

  c3: MOV CL, AL    ; ��������� �������� AL � CL
      MOV CH, BL    ; ��������� �������� BL � CH
      NOT AL        ; �������������� ����� �������� AL ; �� AL
      NOT BL        ; �������������� ����� �������� BL ; �� BL
      AND AL, CH    ; ���������� ������������ AL � CH, ��������� � AL ; (�� AL) � BL
      AND BL, CL    ; ���������� ������������ BL � CL, ��������� � BL ; (�� BL) � AL
      OR AL, BL     ; ���������� �������� AL � BL, ��������� � AL ; ((�� BL) � AL) ��� ((�� AL) � BL)
      
exit: PUSH NULL
      CALL ExitProcess
      
END START
