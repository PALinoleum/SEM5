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
    x db 1, 2, 3, 2, 1
    y dw 6, -6, -3, 3, -1
    k dw 4
    n db 5

    i db 0
    j db 0
    f dd 0
    r dd 0

    save dd 0

    fmt db "%d", 0
    
.code

func proc
    PUSH EBX
    PUSH ECX            ; ��������� EBX � ECX

    XOR ECX, ECX
    MOV CL, [ESP+8+8]   ; ���������� xi � ECX
    CMP ECX, 0
    JLE endFunc         ; ��������� � endFunc, ���� xi < 0
    
subLoop:
    XOR EDX, EDX
    MOV DL, j
    MOV AX, y[EDX*2]    ; ���������� yj � EAX
    CWDE
    MOV EBX, EAX        ; ���������� EAX � EBX
    SUB EBX, 1          ; �������� 1 �� EBX ; yi-1
    CMP EBX, 0
    JGE cont            ; ��������� � con, ���� yi-1 > 0
    MOV EAX, -1         ; ���������� -1 � EAX
    IMUL EBX            ; �������� EAX �� EBX, ��������� � EAX ; abs(yi-1)
    MOV EBX, EAX        ; ���������� EAX � EBX
cont:

    MOV EAX, dword ptr f[0]
    ADD EAX, EBX        ; ��������� ��������� ������ subLoop
    MOV dword ptr f[0], EAX

    XOR EAX, EAX
    MOV AL, j
    INC AL
    MOV j, AL          ; ��������� ����� �������� j ; j+1
    
    DEC ECX            ; ��������� ECX �� 1
    CMP ECX, 0
    JG subLoop         ; ��������� � subLoop, ���� ECX >= 0

endFunc:
    MOV j, 0 
    POP ECX
    POP EBX            ; ���������� EBX � ECX
    RET 8              ; ������� �� �������
func endp

START:
    XOR ECX, ECX
    MOV CL, n           ; ���������� n � ECX
    CMP ECX, 0
    JLE exit            ; ��������� � mainLoop, ���� n < 0
    
mainLoop:
    XOR EDX, EDX
    MOV Dl, i
    XOR EBX, EBX
    MOV BL, x[EDX]      ; ���������� xi � EBX
    MOV AX, y[EDX*2]    ; ���������� yi � EAX
    CWDE
    ADD EBX, EAX        ; ���������� EBX � EAX, ��������� � EBX ; x1 + yi
    XOR EAX, EAX
    MOV AX, k           ; ���������� k � EAX
    IMUL EBX            ; �������� EAX �� EDX, ��������� � EAX ; k*(xi+yi)
    MOV EBX, EAX        ; ���������� EAX � EBX
    
    XOR EAX, EAX
    MOV AX, k           ; ���������� k � EAX
    IMUL EAX            ; �������� EAX �� EAX, ��������� � EAX ; k^2
    XOR EDX, EDX
    MOV DX, k           ; ���������� k � EDX
    IMUL EDX            ; �������� EAX �� EDX, ��������� � EAX ; k^3
    ADD EBX, EAX        ; ���������� EBX � EAX, ��������� � EBX ; k*(xi+yi) + k^3

    XOR EDX, EDX
    MOV DL, i
    MOV AX, y[EDX*2]    ; ���������� yi � EAX
    CWDE
    IMUL EAX            ; �������� EAX �� EAX, ��������� � EAX ; yi^2
    SUB EBX, EAX        ; �������� EAX � EBX, ��������� � EBX ; k*(xi+yi) + k^3 - yi^2

    XOR EDX, EDX
    MOV DL, i
    XOR EAX, EAX
    MOV AL, x[EDX]
    PUSH EAX
    MOV AX, y[EDX*2]
    CWDE
    PUSH EAX
    CALL func           ; �������� ������������ func � ����������� xi � yi

    MOV EAX, dword ptr f ; f(xi,yi)
    MOV f, 0
    MOV dword ptr save, ECX
    XOR ECX, ECX
    MOV CX, k           ; ���������� k � EDX
    XOR EDX, EDX
    IDIV ECX            ; ����� EAX �� EDX, ��������� � EAX ; f(xi,yi)/k
    MOV ECX, dword ptr save
    ADD EBX, EAX        ; ���������� EAX � EBX, ��������� � EBX ; k*(xi+yi) + k^3 - yi^2 + f(xi,yi)/k

    MOV EAX, dword ptr r
    ADD EAX, EBX        ; ��������� ��������� ������ mainLoop
    MOV dword ptr r, EAX

    XOR EAX, EAX
    MOV AL, i
    INC AL
    MOV i, AL           ; ��������� ����� �������� i ; i+1

    DEC ECX             ; ��������� ECX �� 1
    CMP ECX, 0
    JG mainLoop         ; ��������� � mainLoop, ���� ECX >= 0
    
exit:
    MOV EAX, dword ptr r
    PUSH EAX            ; �������� � ���� ������� ���������
    PUSH offset fmt     ; �������� � ���� ������� ���������
    CALL crt_printf     ; ����� ������������ ������
    ADD ESP, 8          ; ������������ �����
    CALL crt__getch
    PUSH NULL
    CALL ExitProcess

END START
