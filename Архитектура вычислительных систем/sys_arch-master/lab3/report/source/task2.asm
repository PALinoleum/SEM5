.386 
.model flat, stdcall 
option casemap: none 

include c:\masm32\include\windows.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\user32.inc
includelib c:\masm32\lib\user32.lib
includelib c:\masm32\lib\kernel32.lib

.DATA
    a db 0B0h, 0B9h, 98h, 0F2h, 0FAh, 8Dh, 11h, 1Ch, 5Eh, 5Bh, 0DEh, 23h, 99h, 0Fh, 0CAh, 0FFh, 0F1h
    b db 40h, 71h, 1Dh, 0F2h, 67h, 67h, 49h, 0AFh, 4Fh, 0EFh, 0C7h, 1Fh, 94h, 52h, 85h, 03h, 8Bh
    r db 18 dup(?)
.CODE
START:
    clc
    xor cl,cl
    xor dl,dl

    mov eax,dword ptr [a+0]
    adc eax,dword ptr [b+0]
    mov dword ptr [r+0],eax

    mov eax,dword ptr [a+4]
    adc eax,dword ptr [b+4]
    mov dword ptr [r+4],eax

    mov eax,dword ptr [a+8]
    adc eax,dword ptr [b+8]
    mov dword ptr [r+8],eax

    mov eax,dword ptr [a+12]
    adc eax,dword ptr [b+12]
    mov dword ptr [r+12],eax

    mov al,a[16]
    adc al,b[16]
    mov r[16],al
    
    adc cl,dl
    mov r[17],cl

    push 0
    call ExitProcess
END START
