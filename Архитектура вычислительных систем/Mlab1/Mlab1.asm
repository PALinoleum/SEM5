.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA
      x dw 65535
      y dw 65535
.CODE
START:
      XOR EAX, EAX
      XOR EBX, EBX   ; ��������� ������� ���������
      XOR EDX, EDX

      MOV AX, y      ; ������ � ������� AX ������ �� ������ ������, ��������������� y
      MOV EBX, 65536 ; ������ � ������� EBX �������� �����
      MUL EBX        ; ��������� �������� EAX �� ������� EBX,
                     ; ��������� ����������� � ����������� �������� EDX:EAX
                     ; ���� ��� ������������ �������� y, ��������� ��������� ���������� � EAX
      MOV EBX, EAX   ; ������ �������� �������� EAX � ������ EBX
      
      XOR EAX, EAX   ; ������� �������� EAX
      MOV AX, x      ; ������ � ������� AX ������ �� ����� ������, ��������������� x
      ADD EAX, EBX   ; �������� ������ �� ��������� EAX � EBX
                     ; ��������� ������������ � ������� EAX
      
      XOR EBX, EBX   ; ������� �������� EBX
      MOV BL, 17     ; ������ � ������� BL ������������� ����� 17
      DIV EBX        ; ������� ������������ �������� EDX:EAX �� ������� EBX
                     ; � EAX ����� �������� �������, � EDX - �������

      PUSH NULL
      CALL ExitProcess
END START
