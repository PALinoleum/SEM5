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
    format db "%x%x"
    big_number dd 1d,1d,1d,1d,1d,1d,1d,1d,1d,1d,1d
.CODE

mult_arr proc
    PUSH EAX
    PUSH EBX
    PUSH ECX
    PUSH EDX

    XOR EAX, EAX
    MOV ECX, [ESP+20]
outer_loop:
    PUSH ECX
    MOV ECX, 0
    clc 
    inner_loop:
        MOV EBX, [ESP+28]
        MOV EDX, dword ptr [ECX*4+EBX]
        sahf
        ADC EDX,0
        shl EDX,1
        lahf
        MOV [ECX*4+EBX], EDX
        INC ECX
        CMP ECX, 11
        JL inner_loop
        POP ECX 
    LOOP outer_loop
    
    POP EDX
    POP ECX
    POP EBX
    POP EAX
    RET 8
mult_arr endp


START:
    PUSH offset big_number
    PUSH 2
    CALL mult_arr

END START
