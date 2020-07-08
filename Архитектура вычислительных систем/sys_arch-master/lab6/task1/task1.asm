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
   push eax 
   push ebx 
   push ecx 
   push edx
   push ebp
        mov eax,[esp+24]
        mov ebx,[esp+28]
        ;форматная строка
        push ebx
        ;операнд 
        push eax
        call crt_printf
        pop eax
        pop eax
   pop ebp
   pop edx
   pop ecx
   pop ebx
   pop eax
   ret 8 
safe_print endp

START:
    xor eax,eax
    xor ecx,ecx
    xor ebp,ebp
    mov ebp,1
    mov ecx,1
loop_start:
    ;вложенный цикл
    mov bl,alphabet[ecx-1]
    push ecx
    mov ecx,7

    ;установка первого символа
    xor edx,edx
    mov dx,half_num
    mov eax,empty_num
    shl eax, 4
    add al,bl
    
    ;вывод первого числа
    push ebp
    push offset count_format
    call safe_print
    inc ebp
    push edx
    push offset half_format
    call safe_print
    push eax
    push offset number_format
    call safe_print
    ex_loop:
        shl eax, 4
        add al,000Ah

        push ebp
        push offset count_format
        call safe_print
        inc ebp
        push edx
        push offset half_format
        call safe_print
        push eax
        push offset number_format
        call safe_print

    loop ex_loop

    mov ecx,3
    mov eax,empty_num

    shl edx,4
    add dl,bl
    and edx,0000FFFFh
    
    push ebp
    push offset count_format
    call safe_print
    inc ebp
    push edx
    push offset half_format
    call safe_print
    push eax
    push offset number_format
    call safe_print
    
    ex_loop2:
        shl edx,4
        add dl,000Ah
        and edx,0000FFFFh
        
        push ebp
        push offset count_format
        call safe_print
        inc ebp
        push edx
        push offset half_format
        call safe_print
        push eax
        push offset number_format
        call safe_print

    loop ex_loop2
    pop ecx
    inc ecx
cmp ecx,5
jl loop_start

END START
