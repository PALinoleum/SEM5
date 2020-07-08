.386 
.model flat, stdcall 
option casemap: none 

include c:\masm32\include\windows.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\user32.inc
include c:\masm32\include\msvcrt.inc

includelib c:\masm32\lib\user32.lib
includelib c:\masm32\lib\kernel32.lib
includelib c:\masm32\lib\msvcrt.lib

.DATA
    x dd 10
    y dd 2
    format db "n = %d, val = %G",13, 10, 0
    
.CODE

; �������� x � ������� y
; ��������� � EAX
pow proc
    ; 4 ����� �������� num
    ; 4 ����� �������� pow
    ; 4 ����� - ����� ��������
    ; 12 ���� - ���������� ��������� ���������
    ; 4 ����� - ����� � �����, ��� �������� � �����������
    PUSH ECX                ; ��������� �������� � �����
    PUSH EDX 
    PUSH EBX
    
    SUB ESP, 4              ; �������� � ����� 4 �����
    MOV EAX, [ESP+24]       ; ���������� x � EAX  
    MOV [ESP], EAX          ; ���������� EAX � ����
    fild dword ptr [ESP]    ; ���������� ������� ����� � ST(0)
    MOV ECX, [ESP+20]       ; ���������� y � EC
    DEC ECX                 ; �������� 1 �� ECX
pow_cycle:
    fimul dword ptr [ESP]   ; �������� ST(0) �� ������� �����, ��������� � ST(0)
loop pow_cycle
    fistp dword ptr [ESP]   ; ����������� ST(0) � ����
    MOV EAX, [ESP]          ; ���������� ������� ����� � EAX
    MOV EBX, EAX            ; ���������� EAX � EBX
    ADD ESP, 4              ; ������� �� ����� 4 �����

    MOV EAX, EBX            ; ���������� EBX � EAX
    
    POP EBX                 ; ���������� �������� �� �����
    POP EDX
    POP ECX
    RET 8
pow endp

; �������� �������� n ��������� �����
; ���������� ��������� � EAX
row proc
    PUSH ECX                ; ��������� ECX � ����
    MOV EAX, [ESP+8]        ; ���������� n � EAX 
    SUB ESP, 4              ; ���������� ECX � �����
    MOV [ESP], EAX          ; ���������� � ���� EAX
    ;f1
    fild dword ptr [ESP]    ; ��������� � ST(0) ������� ����� ; n
    MOV EAX, 2              ; ���������� 2 � EAX
    MOV [ESP], EAX          ; ���������� � ���� EAX
    fimul dword ptr [ESP]   ; �������� ST(0) �� ������� �����, ��������� � ST(0) ; 2*n
    MOV EAX, 1              ; ���������� 1 � EAX
    MOV [ESP], EAX          ; ���������� EAX � ����
    fiadd dword ptr [ESP]   ; ���������� ST(0) � ������� �����, ��������� � ST(0) ; 2*n+1
    ;f2
    MOV EAX, [ESP+12]       ; ���������� n � EAX
    MOV [ESP], EAX          ; ���������� EAX � ����
    fild dword ptr [ESP]    ; ���������� � ST(0) ������� ����� ; n
    fimul dword ptr [ESP]   ; �������� ST(0) �� ������� ����� ; n^2
    MOV EAX, 2              ; ���������� 2 � EAX
    MOV [ESP], EAX          ; ���������� EAX � ������� �����
    fimul dword ptr [ESP]   ; �������� ST(0) �� ������� �����, ��������� � ST(0) ; 2*n^2
    MOV EAX, 1              ; ���������� 1 � EAX
    MOV [ESP], EAX          ; ���������� EAX � ������ �����
    fisub dword ptr [ESP]   ; �������� �� ST(0) ������� �����, ��������� � ST(0) ; 2*n^2-1
    ;f3
    fdiv ST(1), ST(0)       ; ����� ST(1) �� ST(0), ��������� � ST(1) ; (2*n+1)/(2*n^2-1)
    fstp dword ptr [ESP]    ; ����������� ST(0) � ����
    MOV EAX, 1              ; ���������� 1 � EAX
    MOV [ESP], EAX          ; ���������� EAX � ����
    fild dword ptr [ESP]    ; ���������� � ST(0) ������� �����
    fsubr ST(1), ST(0)      ; �������� ST(1) �� ST(0), ��������� � ST(1) ; 1 - (2*n+1)/(2*n^2-1)
    ;f4
    fstp dword ptr [ESP]    ; ����������� ST(0) � ����
    MOV EAX, [ESP+12]       ; ���������� n � EAX
    MOV ECX, 2              ; ���������� 2 � ECX
    MUL ECX                 ; �������� EAX �� ECX, ��������� � EDX:EAX ; 2*n
    MOV ECX, EAX            ; ���������� EAX � ECX
    fldpi                   ; ���������� � ST(0) ����� pi
    fldpi                   ; ���������� � ST(0) ����� pi
loop_start:
    DEC ECX                 ; �������� 1 �� ECX ;
    fmul ST(1), ST(0)       ; �������� ST(1) �� ST(0), ��������� � ST(1) ; pi^2
    CMP ECX, 0              ; ���������� ECX � 0
    jne loop_start          ; ���� ECX ������ ��� �����, ��������� ����
    fmulp ST(1), ST(0)      ; �������� ST(1) �� ST(0), ��������� � ST(1), ����������� ST(0) � ���� ; (pi^2)^n
    ;f5
    MOV EAX, 1              ; ���������� 1 � EAX
    MOV [ESP], EAX          ; ���������� EAX � ����
    fild dword ptr [ESP]    ; ���������� � ST(0) ������� �����
    fdivr ST(1), ST(0)      ; ����� ST(0) �� ST(1), ��������� � ST(1) ; 1/(pi^2)^n
    fstp dword ptr [ESP]    ; ����������� ST(0) � ����
    fadd ST(0), ST(1)       ; ���������� ST(0) � ST(1), ��������� � ST(0)
    fstp dword ptr [ESP]    ; ����������� ST(0) � ����
    MOV EAX, [ESP]          ; ���������� � EAX ������� �����
    fstp dword ptr [ESP]    ; ����������� ST(0) � ����
    ADD ESP, 4              ; ��������� � ECX � �����
    POP ECX                 ; ���������� ECX �� �����
    RET 8                   ; ������� �� ������������
row endp


start:
    XOR EAX, EAX    ; ������� ��������
    XOR EBX, EBX
    XOR EDX, EDX
    XOR ECX, ECX

loop_start:
    INC ECX         ; ����������� ������� ��������� �����
    PUSH ECX        ; ���������� ECX � ����
    CALL row

    PUSH EAX        ; ���������� EAX � ����
    PUSH 0          ; ���������� 0 � ����
    PUSH ECX        ; ���������� ECX � ����

    PUSH offset format
    CALL crt_printf
    ADD ESP, 4      ; ������� �� ����� 4 �����
    POP ECX         ; ���������� ECX �� �����
    CMP ECX, 50     ; ���������� ECX � 50
    JL loop_start   ; ���� ECX ������, ��������� ����
END start
