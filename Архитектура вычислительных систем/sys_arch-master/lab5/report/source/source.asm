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
        x dd 2
        y dd 10
        format db "n = %d, val = %G",13, 10, 0
.CODE

pow proc
    ;4 байта аргумент num
    ;4 байта аргумент pow
    ;4 байта - адрес возврата
    ;12 байт - сохранение состояний регистров
    ;4 байта - буфер в стеке, для передачи в сопроцессор
    push ecx
    push edx 
    push ebx
    
    sub esp,4
    mov eax,[esp+24]
    mov [esp],eax
    fild dword ptr [esp]
    mov ecx,[esp+20]
    dec ecx
pow_cycle:
    fimul dword ptr [esp]
loop pow_cycle
    fistp dword ptr [esp]
    mov eax,[esp]
    mov ebx,eax
    add esp,4

    mov eax,ebx
    
    pop ebx
    pop edx
    pop ecx
    ret 8
pow endp

;Принимает n
;EAX результат 
row proc
    push ecx
    mov eax, [esp+8]
    sub esp,4
    mov [esp],eax
    ;f1
    fild dword ptr [esp]
    mov eax,2
    mov [esp], eax
    fimul dword ptr [esp]
    mov eax,1
    mov [esp], eax
    fiadd dword ptr [esp]
    ;f2
    mov eax, [esp+12]
    mov [esp],eax
    fild dword ptr [esp]
    fimul dword ptr [esp]
    mov eax,2
    mov [esp], eax
    fimul dword ptr [esp]
    mov eax,1
    mov [esp], eax
    fisub dword ptr [esp]
    ;f3
    fdiv st(1),st(0)
    fstp dword ptr [esp]
    mov eax,1
    mov [esp], eax
    fild dword ptr [esp]
    fsubr st(1),st(0)
    ;f4
    fstp dword ptr [esp]
    mov eax, [esp+12]
    mov ecx,2
    mul ecx
    mov ecx,eax
    fldpi
    fldpi
    loop_start:
    dec ecx
    fmul st(1),st(0)
    cmp ecx,0
    jne loop_start
    fmulp st(1),st(0)
    ;f5
    mov eax,1
    mov [esp], eax
    fild dword ptr [esp]
    fdivr st(1),st(0)
    fstp dword ptr [esp]
    fadd st(0),st(1)
    fstp dword ptr [esp]
    mov eax,[esp]
    fstp dword ptr [esp]
    add esp,4
    pop ecx
    ret 8
row endp


start:
    xor eax,eax
    xor ebx,ebx
    xor edx,edx
    xor ecx,ecx
loop_start:
    inc ecx
    push ecx
    call row
    push eax
    push 0
    push ecx
    push offset format
    call crt_printf
    add esp,4
    pop ecx
    cmp ecx,50
    jl loop_start
END start
