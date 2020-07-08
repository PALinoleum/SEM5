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
    format db "n = %d, lg(n) = %llf", 13, 10, 0
    
.CODE

start:
    XOR EAX, EAX    ; очищаем регистры
    XOR EBX, EBX
    XOR EDX, EDX
    XOR ECX, ECX

loop_start:
    INC ECX        ; увеличиваем счетчик основного цикла
    PUSH ECX

    MOV EAX, 1
    SUB ESP, 4
    MOV [ESP], EAX
    fild dword ptr [ESP]
    ADD ESP, 4

    MOV EAX, 10
    SUB ESP, 4
    MOV [ESP], EAX
    fild dword ptr [ESP]
    ADD ESP, 4

    fyl2x

    MOV EAX, 1
    SUB ESP, 4
    MOV [ESP], EAX
    fild dword ptr [ESP]
    ADD ESP, 4

    fdiv ST(0), ST(1)

    SUB ESP, 4
    MOV [ESP], ECX
    fild dword ptr [ESP]
    ADD ESP, 4

    fyl2x

    SUB ESP, 8
    fstp qword ptr [ESP]
    PUSH ECX        ; записываем ECX в стек
    PUSH offset format
    CALL crt_printf
    fstp qword ptr [ESP]
    MOV EAX, [ESP]
    ADD ESP, 16
    
    
    POP ECX
    CMP ECX, 50     ; сравниваем ECX и 50
    JL loop_start   ; если ECX меньше, повторить цикл
END start
