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
    XOR EAX, EAX                ; очистка регистров
    XOR ECX, ECX
    XOR EBP, EBP
    MOV EBP, 1                  ; запишем 1 в EBP
    MOV ECX, 1                  ; запишем 1 в ECX
loop_start:
    ;вложенный цикл
    MOV BL, alphabet[ECX-1]     ; запишем в BL символ для перебора
    PUSH ECX                    ; сохраним ECX в стеке
    MOV ECX, 7                  ; запишем 7 в ECX

    ;установка первого символа
    XOR EDX, EDX                ; очистка регистра EDX
    MOV DX, half_num            ; запишем 0AAAAh в DX
    MOV EAX, empty_num          ; запишем 0AAAAAAAAh в EAX
    shl EAX, 4                  ; выполним побитовый сдвиг влево на 4 регистра EAX
    ADD AL, BL                  ; сложим регистры AL и BL, результат в AX
    
    ;вывод первого числа
    PUSH EBP                    ; запишем в стек EBP
    PUSH offset count_format
    CALL safe_print
    INC EBP                     ; прибавим 1 к EBP
    PUSH EDX                    ; запишем EDX в стек
    PUSH offset half_format
    CALL safe_print
    PUSH EAX                    ; запишем EAX в стек
    PUSH offset number_format
    CALL safe_print
    ex_loop:
        shl EAX, 4                  ; выполним побитовый сдвиг влево на 4 регистра EAX
        ADD AL, 000Ah               ; прибавим к AL 000Ah

        PUSH EBP                    ; запишем EBP в стек
        PUSH offset count_format
        CALL safe_print
        INC EBP                     ; прибавим 1 к EBP
        PUSH EDX
        PUSH offset half_format
        CALL safe_print
        PUSH EAX                    ; запишем EAX в cn
        PUSH offset number_format
        CALL safe_print

    LOOP ex_loop

    MOV ECX, 3                  ; запишем 3 в ECX
    MOV EAX, empty_num          ; запишем 0AAAAAAAAh в EAX 

    shl EDX, 4                  ; выполним побитовый сдвиг влево на 4 регистра EDX
    ADD DL, BL                  ; сложим регистры DL и BL, результат в DX
    and EDX, 0000FFFFh          ; выполним логическое И над EDX и 0000FFFFh
    
    PUSH EBP                    ; запишем EBP в стек
    PUSH offset count_format
    CALL safe_print
    INC EBP                     ; прибавим 1 к EBP
    PUSH EDX                    ; запишем EDX
    PUSH offset half_format
    CALL safe_print
    PUSH EAX                    ; запишем EAX в стек
    PUSH offset number_format
    CALL safe_print
    
    ex_loop2:
        shl EDX, 4                  ; выполним побитовый сдвиг влево на 4 регистра EDX
        ADD DL, 000Ah               ; прибавим к DL 000Ah
        and EDX, 0000FFFFh          ; выполним логическое И над EDX и 0000FFFFh
        
        PUSH EBP                    ; запишем EBP в стек
        PUSH offset count_format
        CALL safe_print
        INC EBP                     ; прибавим 1 к EBP
        PUSH EDX                    ; запишем EDX
        PUSH offset half_format
        CALL safe_print
        PUSH EAX                    ; запишем EAX в стек
        PUSH offset number_format
        CALL safe_print

    LOOP ex_loop2
    POP ECX                     ; вернем ECX з
    INC ECX                     ; прибавим 1 к ECX
CMP ECX, 5                      ; стравним ECX и 5
JL loop_start                   ; если ECX меньше, повторить цикл

END START
