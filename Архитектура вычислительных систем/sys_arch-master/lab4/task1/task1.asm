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
    x DW 020h
    y DB 050h
    z DB 020h
    format db "a = %d", 0
.CODE
start:
    xor eax,eax
    xor ecx,ecx
    xor ebx,ebx
    xor edx,edx
    ;проверка y>=0 -> z+1+xy
    mov al,0
    cmp y,al
    jae case_Y
    ;проверка z<-1 -> x^2*y^3*z^4
    mov al,-1
    cmp z,al
    jb case_Z_not_in
    ;проверка z>1 -> x^2*y^3*z^4
    mov al,1
    cmp z,al
    ja case_Z_not_in
    ;если 3 перехода не сработали переходим на ветку 4x-2z
    jmp case_Z_in

    case_Y:
        ;ebx = x
        mov ax,x
        cwde
        mov ebx,eax

        ;eax = y
        mov al,y
        cbw
        cwde
        
        ;ebx = x*y
        imul ebx
        mov ebx,eax

        ;eax = z+1+x*y
        mov al,z
        cbw
        cwde
        add eax,1
        add eax,ebx
    
        jmp print_mark

    case_Z_in:
        ;ebx = 4*x
        mov ax,x
        cwde
        mov ebx,4
        imul ebx
        mov ebx,eax

        ;eax = 2*z
        mov al,z
        cbw
        cwde
        mov ecx,2
        imul ecx
        
        ;eax = 4*x-2*z
        sub ebx,eax
        mov eax,ebx

        jmp print_mark

    case_Z_not_in:
        ;ebx = z*z*z*z
        mov al,z
        cbw
        cwde
        mov ebx,eax
        imul ebx
        imul ebx
        imul ebx
        mov ebx,eax

        ;ecx = y*y*y
        mov al,y
        cbw
        cwde
        mov ecx,eax
        imul ecx
        imul ecx
        mov ecx,eax

        ;eax = x*x
        mov ax,x
        cwde
        imul eax

        ;eax = x^2*y^3*z^4
        imul ebx
        imul ecx
        
        jmp print_mark

    print_mark:
        push eax
        push offset format
        call crt_printf

    call crt__getch
    push 0
    call ExitProcess
END start
