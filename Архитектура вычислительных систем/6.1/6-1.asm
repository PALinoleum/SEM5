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
    alphabet db 3h,5h,7h,0Fh
    count_format db "%d. ", 0
    half_format db "%X", 0
    number_format db "%X",0Ah
    new_line_format db 13, 10, 0
    empty_num dd 0AAAAAAAAh
    half_num dw 0AAAAh
.CODE

safe_print proc
   PUSH EAX 
   PUSH EBX 
   PUSH ECX 
   PUSH EDX
   PUSH EBP
        MOV EAX, [ESP+24]
        mov EBX, [ESP+28]
        ;��������� ������
        PUSH EBX
        ;������� 
        PUSH EAX
        CALL crt_printf
        POP EAX
        POP EBX
   POP EBP
   POP EDX
   POP ECX
   POP EBX
   POP EAX
   RET 8 
safe_print endp

START:
    XOR EAX, EAX                ; ������� ���������
    XOR ECX, ECX
    XOR EBP, EBP
    MOV EBP, 1                  ; ������� 1 � EBP
    MOV ECX, 1                  ; ������� 1 � ECX
loop_start:
    ;��������� ����
    MOV BL, alphabet[ECX-1]     ; ������� � BL ������ ��� ��������
    PUSH ECX                    ; �������� ECX � �����
    MOV ECX, 7                  ; ������� 7 � ECX

    ;��������� ������� �������
    XOR EDX, EDX                ; ������� �������� EDX
    MOV DX, half_num            ; ������� 0AAAAh � DX
    MOV EAX, empty_num          ; ������� 0AAAAAAAAh � EAX
    shl EAX, 4                  ; �������� ��������� ����� ����� �� 4 �������� EAX
    ADD AL, BL                  ; ������ �������� AL � BL, ��������� � AX
    
    ;����� ������� �����
    PUSH EBP                    ; ������� � ���� EBP
    PUSH offset count_format
    CALL safe_print
    INC EBP                     ; �������� 1 � EBP
    PUSH EDX                    ; ������� EDX � ����
    PUSH offset half_format
    CALL safe_print
    PUSH EAX                    ; ������� EAX � ����
    PUSH offset number_format
    CALL safe_print
    ex_loop:
        shl EAX, 4                  ; �������� ��������� ����� ����� �� 4 �������� EAX
        ADD AL, 000Ah               ; �������� � AL 000Ah

        PUSH EBP                    ; ������� EBP � ����
        PUSH offset count_format
        CALL safe_print
        INC EBP                     ; �������� 1 � EBP
        PUSH EDX
        PUSH offset half_format
        CALL safe_print
        PUSH EAX                    ; ������� EAX � cn
        PUSH offset number_format
        CALL safe_print

    LOOP ex_loop

    MOV ECX, 3                  ; ������� 3 � ECX
    MOV EAX, empty_num          ; ������� 0AAAAAAAAh � EAX 

    shl EDX, 4                  ; �������� ��������� ����� ����� �� 4 �������� EDX
    ADD DL, BL                  ; ������ �������� DL � BL, ��������� � DX
    and EDX, 0000FFFFh          ; �������� ���������� � ��� EDX � 0000FFFFh
    
    PUSH EBP                    ; ������� EBP � ����
    PUSH offset count_format
    CALL safe_print
    INC EBP                     ; �������� 1 � EBP
    PUSH EDX                    ; ������� EDX
    PUSH offset half_format
    CALL safe_print
    PUSH EAX                    ; ������� EAX � ����
    PUSH offset number_format
    CALL safe_print
    
    ex_loop2:
        shl EDX, 4                  ; �������� ��������� ����� ����� �� 4 �������� EDX
        ADD DL, 000Ah               ; �������� � DL 000Ah
        and EDX, 0000FFFFh          ; �������� ���������� � ��� EDX � 0000FFFFh
        
        PUSH EBP                    ; ������� EBP � ����
        PUSH offset count_format
        CALL safe_print
        INC EBP                     ; �������� 1 � EBP
        PUSH EDX                    ; ������� EDX
        PUSH offset half_format
        CALL safe_print
        PUSH EAX                    ; ������� EAX � ����
        PUSH offset number_format
        CALL safe_print

    LOOP ex_loop2
    POP ECX                     ; ������ ECX �
    INC ECX                     ; �������� 1 � ECX
CMP ECX, 5                      ; �������� ECX � 5
JL loop_start                   ; ���� ECX ������, ��������� ����

END START
