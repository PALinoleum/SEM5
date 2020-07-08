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
    fmt db "%X", 0
    a dd 0
.CODE

safe_print proc
   PUSH EAX 
   PUSH EBX 
   PUSH ECX 
   PUSH EDX
   PUSH EBP
        MOV EAX, [ESP+24]
        mov EBX, [ESP+28]
        ;форматная строка
        PUSH EBX
        ;операнд 
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
    XOR EAX, EAX
    XOR EBX, EBX
    XOR ECX, ECX
    XOR EDX, EDX
    XOR EBP, EBP

    ; считываем число

    PUSH EAX
    PUSH ECX
    PUSH EDX
    PUSH offset a
    PUSH offset fmt
    CALL crt_scanf
    ADD ESP, 8
    MOV EBX, a
    POP EDX
    POP ECX
    POP EAX

    ;MOV EBX, 016AB3Eh

    ;PUSH EBX
    ;PUSH offset fmt
    ;CALL safe_print

    ; удаляем лишние символы

    MOV ECX, 0
    MOV EDX, 0

main_loop:

    PUSH EBX
    PUSH EAX

    MOV EAX, 0fh
    PUSH ECX
    CMP ECX, 0
    JE cont1 
shift1:
    SHL EAX, 4
    DEC ECX
    CMP ECX, 0
    JG shift1   
    
cont1:
    POP ECX
    AND EBX, EAX
    PUSH ECX
    CMP ECX, 0
    JE cont2    
shift2:
    SHR EBX, 4
    DEC ECX
    CMP ECX, 0
    JG shift2
    
cont2:
    POP ECX
    POP EAX
    CMP EBX, 1
    JE cont3
    CMP EBX, 3
    JE cont3

    CMP EDX, 0
    JE cont4
    PUSH EDX
shift3:
    SHL EBX, 4
    DEC EDX
    CMP EDX, 0
    JG shift3
    POP EDX
    
cont4:
    INC EDX
    ADD EAX, EBX

cont3:
    POP EBX
    INC ECX
    CMP ECX, 8
    JL main_loop
    
    ; выводим число
    
    PUSH EAX
    PUSH offset fmt
    CALL safe_print

END START
