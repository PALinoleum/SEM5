.386 
.model flat, stdcall 
option casemap: none 

include c:\masm32\include\windows.inc


.DATA
    format db "%x%x"
    big_number dd 2d,0d,0d,0d,0d,0d,0d,0d,0d,0d,4d
.CODE

mult_arr proc
    ;x=x<<n
    ;4 байта - n
    ;4 байта - x
    ;4 байта - адрес возврата 
    push eax
    push ebx
    push ecx
    push edx

    ;16 байт - сохранение переменных
    xor edx,edx
    mov ecx,[esp+20]
outer_loop:
    push ecx
    mov ecx,0
    clc 
    inner_loop:
        ;адрес начала массива x
        mov ebx,[esp+28]
        ;x[ecx]
         mov eax,dword ptr [ecx*4+ebx]
        ;прибавить CF
        mov edx,0
        adc edx,0
        or eax,edx
        ;сдвиг влево (старший бит в CF)
        shl eax,1
        ;запись обратно
        mov [ecx*4+ebx],eax
        inc ecx
        cmp ecx,11
    jl inner_loop
    pop ecx 
loop outer_loop
    
    pop edx
    pop ecx
    pop ebx
    pop eax
    ret 8
mult_arr endp


START:
    push offset big_number
    push 1
    call mult_arr

END START
