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
    h db 3h ;знаковая
    x db 2h,3h; знаковая
    y dw 4h,5h; беззнаковая
    m dw 2h; беззнаковая
    const_mul1 dd 1000
    format db "sum = %d", 0
.CODE

;eax - число, ecx - степень.
pow proc
    push ecx
    push edx
    push ebx

    mov ecx,[esp+16]
    mov eax,[esp+20]
    mov ebx,[esp+20]
    sub ecx,1
pow_cycle:
    mul ebx
loop pow_cycle
    pop ebx
    pop edx
    pop ecx
    ret 8
pow endp

;2 аргумента x,y результат в eax
f proc
    push edx
    push ebx
    ;eax - x
    mov eax,[esp+12]
    cmp eax,10 
    ja f_x_true
    ;ebx - y
    mov ebx,[esp+16]
    sub eax,ebx
    mov ebx,eax
    mov eax,const_mul1
    idiv ebx
    jmp f_return

f_x_true:
    xor eax,edx 
    sub eax,edx
    mov edx,eax
    mov ax,[esp+12]
    cwde
    sub edx,eax
    mov eax,edx
    jmp f_return

f_return:
    pop ebx
    pop edx
    ret 8
f endp

start:
    ;esi - i
    ;ecx - j
    ;ebp - аккумулятор суммы
    ;eax,ebx,edx - свободны

    xor eax,eax
    xor ebx,ebx
    xor ecx,ecx
    xor edx,edx
    xor ebp,ebp
    xor esi,esi
start_external_loop:
    cmp si,m
    jb external_loop_body
    jmp end_prog
external_loop_body:
    mov cx,0
internal_loop_body:
        ;ebx = (h+17*i)
        xor eax,eax
        add eax,17
        imul esi
        mov ebx,eax
        mov al,h
        cbw
        cwde 
        add ebx,eax

        ;ebx = (h+17*i)*f(x[i],y[j])
        mov ax,y[ecx*2]
        cwde
        push eax
        mov al,x[esi]
        cbw
        cwde
        push eax
        call f
        mul ebx
        mov ebx,eax
        mov ax,y[esi*2]
        cwde
        mul ebx
        mov ebx,eax 

        mov al,x[esi]
        cbw
        cwde
        push eax
        push 5 
        call pow
        add eax,ebx
        add ebp,eax

        mov al,h
        cbw
        cwde 
        imul esi
        sub ebp,eax
    inc cx
    cmp cx,m
    jb internal_loop_body
    add esi,1
    jmp start_external_loop
end_prog:
    mov eax,ebp
    push eax
    push offset format
    call crt_printf
END start
