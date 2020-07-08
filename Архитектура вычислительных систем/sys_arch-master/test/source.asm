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

circle_check proc
	pushad
		;a[esp+52]
		;b[esp+48]
        ;r[esp+44]
		;x[esp+40]
		;y[esp+36]
		
		;x-a
		fild dword ptr [esp+40]
		fild dword ptr [esp+52]
		fsubp st(1),st(0)
		fmul st(0),st(0)
        ;b-a
        fild dword ptr [esp+36]
        fild dword ptr [esp+48]
		fsubp st(1),st(0)
		fmul st(0),st(0)
        faddp st(1),st(0)

        fild dword ptr [esp+44]
		fmul st(0),st(0)
	popad
        db 0dbh, 0f0h+1
        je check_eq
        check_neq:
            mov eax,0
            jmp check_end
        check_eq:
            mov eax,1
        check_end:
            FFREE st(0) 
            FFREE st(1) 
    ret 24
circle_check endp


start:
    xor eax,eax
    xor ebx,ebx
    xor edx,edx
    xor ecx,ecx
    push 0
    push 0
    push 5 
    push 0 
    push 5
    call circle_check
END start
