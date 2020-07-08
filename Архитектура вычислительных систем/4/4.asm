.386
.model FLAT, STDCALL
option casemap: NONE
    include c:\masm32\include\windows.inc
    include c:\masm32\include\kernel32.inc
    include c:\masm32\include\user32.inc
    include c:\masm32\include\msvcrt.inc
    includelib c:\masm32\lib\user32.lib
    includelib c:\masm32\lib\kernel32.lib
    includelib c:\masm32\lib\msvcrt.lib
.data
    x dw 12 ; 26 ; 20 
    y db -5 ; 16 ; 12 
    z db 10 ; -2 ; -8 
       ; p3 ; p2 ; p1 

    fmt db "%d", 0
.code
START:
    MOVSX ECX, y        ; ��������� y � ECX
    CMP ECX, 10         ; ���� y <= 10, ������������ � p3
    JLE p3
    MOVSX ECX, z        ; ���������� z � ECX
    CMP ECX, 0          ; ���� z < 0, ������������ � neg 
    JL negation

abs:
    CMP EAX, 5          ; ���� abs(z) > 5, ������������ � p1
    JG p1
    JMP p2              ; ���� y > 10 � abs(z) <= 5, ������������ � p2

negation:
    MOV EAX, -1         ; ��������� -1 � EAX
    CBW
    CWDE
    IMUL ECX            ; �������� EAX �� EDX ; abs(z)
    JMP abs             ; ������������ � abs

 p1:
    XOR EAX, EAX        ; ������� EAX
    MOV AX, x           ; ���������� x � EAX
    MOVSX EDX, y        ; ���������� y � EDX
    ADD EAX, EDX        ; ���������� EAX � EDX ; x + y
    ADD EAX, 1          ; ���������� 1 � EAX ; x + y + 1
    IMUL EAX            ; �������� EAX �� EAX, ��������� � EAX ; (x+y+1)^2
    MOV EBX, EAX        ; ���������� EAX � EBX

    MOVSX EAX, z        ; ���������� z � EAX
    IMUL EAX            ; �������� EAX �� EAX, ��������� � EAX ; z^2
    IMUL EAX            ; �������� EAX �� EAX, ��������� � EAX ; z^4
    IMUL EBX            ; �������� EAX �� EBX, ��������� � EAX ; (x+y+1)^2 * z^4
    MOV EBX, EAX        ; ���������� EAX � EBX

    MOVSX EAX, y        ; ���������� y � EAX
    IMUL EAX            ; �������� EAX �� EAX, ��������� � EAX ; y^2
    MOVSX EDX, y        ; ���������� y � EDX
    IMUL EDX            ; �������� EAX �� EDX, ��������� � EAX ; y^3
    SUB EAX, 2          ; �������� 2 �� EAX ; y^3 + 2
    MOV ECX, EAX        ; ���������� EAX � ECX
    MOV EAX, EBX        ; ���������� EBX � EAX
    CDQ
    IDIV ECX            ; ����� EAX �� ECX, ��������� � EDX:EAX ; (x+y+1)^2 * z^4 / (y^3 + 2)

    PUSH EAX            ; �������� � ���� ������� ���������
    PUSH offset fmt     ; �������� � ���� ������� ���������
    CALL crt_printf     ; ����� ������������ ������
    ADD ESP, 8          ; ������������ ������
    
    JMP exit

 p2:
    MOV EAX, 1          ; ���������� 1 � EAX
    XOR EBX, EBX
    MOV BX, x           ; ���������� x � EBX
    IDIV EBX            ; ����� EAX �� EBX, ��������� � EAX ; 1/x
    MOV EBX, EAX        ; ���������� EAX � EBX
    
    MOV EAX, ECX        ; ���������� ECX � EAX ; z
    IMUL EAX            ; �������� EAX �� EAX, ��������� � EAX ; z^2
    MOV ECX, EAX        ; ���������� EAX � ECX
    MOV EAX, -1         ; ���������� -1 � EAX     
    IMUL ECX            ; �������� EAX �� ECX, ��������� � EAX ; -z^2
    ADD EBX, EAX        ; ���������� EBX � EAX, ��������� � EBX ; -z^2 + 1/x

    XOR EAX, EAX        
    MOV AX, x           ; ���������� x � EAX
    MOV ECX, EBX        ; ���������� EBX � ECX
    MOVSX EBX, y        ; ���������� y � EBX
    ADD EBX, 10         ; ���������� 10 � EBX ; y + 10
    XOR EDX, EDX
    IDIV EBX            ; ����� EAX �� EBX, ��������� � EAX ; x/(y+10)
    ADD EAX, ECX        ; ���������� EAX � ECX, ��������� � EAX ; -z^2 + 1/x + x/(y+10)

    PUSH EAX            ; �������� � ���� ������� ���������
    PUSH offset fmt     ; �������� � ���� ������� ���������
    CALL crt_printf     ; ����� ������������ ������
    ADD ESP, 8          ; ������������ ������
    
    JMP exit
    
 p3:
    MOVSX EAX, z        ; ���������� z � EAX
    ADD EAX, 1          ; ���������� 1 � EAX ; z + 1
    MOV EDX, 2          ; ���������� 2 � EDX
    IMUL EDX            ; �������� EAX �� EDX, ��������� � EAX ; 2*(z+1)
    IMUL ECX            ; �������� EAX �� ECX, ��������� � EAX ; 2*(z+1)*y
    MOV EBX, EAX        ; ���������� EAX � EBX

    XOR EAX, EAX
    MOV AX, x           ; ���������� x � AX
    IMUL EAX            ; �������� EAX �� EAX, ��������� � EAX ; x^2
    MOV ECX, -5         ; ���������� -5 � ECX
    IMUL ECX            ; �������� EAX �� ECX, ��������� � EAX ; -5*(x^2)
    SUB EAX, EBX        ; �������� EBX �� EAX, ��������� � EAX ; -5*(x^2) - 2*(z+1)*y

exit:
    PUSH EAX            ; �������� � ���� ������� ���������
    PUSH offset fmt     ; �������� � ���� ������� ���������
    CALL crt_printf     ; ����� ������������ ������
    ADD ESP, 8          ; ������������ �����
    CALL crt__getch
    PUSH NULL
    CALL ExitProcess
    
END START
