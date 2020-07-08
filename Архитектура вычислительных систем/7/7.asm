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
a db "aaa aaa aaa bba",0
format_str db "%s", 10,13,0
.CODE

; первый аргумент - указатель на строку
; второй аргумент - индекс для удаления
delete_char proc
    PUSH EAX
    PUSH EBX
    PUSH ECX
    PUSH EDX

    XOR EAX, EAX
    XOR EBX, EBX
    XOR ECX, ECX
    XOR EDX, EDX
    
    MOV EAX, [ESP+24]
    MOV EBX, [ESP+20]
    MOV ECX, EBX
    ADD ECX, 1
    DEC EBX 
    DEC ECX 
loop_start: 
    INC EBX 
    INC ECX 
    MOV DL, byte ptr[EAX+ECX]
    MOV byte ptr[EAX+EBX], DL
    MOV DL, byte ptr[EAX+EBX]
    CMP EDX, 0
    JNE loop_start
    
    POP EDX
    POP ECX
    POP EBX
    POP EAX
    RET 12
delete_char endp

START:
PUSH offset a
PUSH offset format_str
call crt_printf
ADD ESP, 8

MOV EBX, offset a - 1               
work_cycle:
    find_cycle:
        ; EBX - текущий указатель
        ADD EBX, 1
        MOV ECX, [EBX]
        CMP CL, 0
        JE work_end
        MOV ECX, [EBX]
        CMP CL, 20h
        JLE find_cycle
    ;ebx - указатель на начало слова
    ;edx - рабочий указатель внутри слова
    MOV EDX, EBX
    MOV EAX, 0
    check_cycle:
        ADD EDX, 1
        MOV ECX, [EDX]
        CMP CL,0
        JE del_check
        MOV ECX, [EDX]
        CMP CL, 20h
        JLE del_check
        MOV ECX, [EDX]
        PUSH EAX
        MOV EAX, [EBX]
        CMP AL, CL
        POP EAX
        JE check_cycle
        MOV EAX, 1
        JMP check_cycle
    del_check_false:
        MOV EBX, EDX
        JMP find_cycle
    del_check:
        CMP EAX, 1
        JE del_check_false
    del_cycle:
        PUSH EBX
        PUSH 0 
        CALL delete_char
        MOV ECX, [EBX]
        CMP CL, 20h
        JNLE del_cycle
        JMP find_cycle
work_end:

PUSH offset a
PUSH offset format_str
CALL crt_printf
ADD ESP, 8

END START

