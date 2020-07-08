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
    x dw 1,2,3,4,5,6,7,8,9,10
    n dd 10
    format db "%d ", 0
.CODE

output_array proc
    push eax
    push ebx
    push ecx
    push edx
    xor edx,edx
loop_start:
    mov ecx,[esp+20]
    mov ax,word ptr [edx*2+ecx]
    cwde
    push edx
    push eax
    push offset format
    call crt_printf
    pop eax
    pop eax
    pop edx
mov eax,dword ptr[esp+24]
dec eax
cmp edx,eax
inc edx
jb loop_start
    pop edx
    pop ecx
    pop ebx
    pop eax
    ret 8
output_array endp

start:
    push n
    push offset x
    call output_array
end start
