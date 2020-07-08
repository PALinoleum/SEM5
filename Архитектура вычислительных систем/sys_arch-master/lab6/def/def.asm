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
    a dd ? 
    format db "%x"
.CODE

START:
    push offset a
    push offset format
    call crt_scanf
	
    mov ax, word ptr a[2]
    ;проверка левой половины младшего байта
    mov bl,al
    and bl,11110000b
    cmp bl, 10100000b
    jne equal1
        or al,11110000b
    equal1:

    ;правой половины младшего байта
    mov bl,al
    and bl,00001111b
    cmp bl, 00001010b
    jne equal2
        or al,00001111b
    equal2:
    
    ;левая половина старшего байта
    mov bl,ah
    and bl,11110000b
    cmp bl, 10100000b
    jne equal3
        or ah,11110000b
    equal3:

    ;правая половина старшего байта
    mov bl,ah
    and bl,00001111b
    cmp bl, 00001010b
    jne equal4
        or ah,00001111b
    equal4:

    shl eax,16
	mov ax,word ptr a[0]

    ;проверка левой половины младшего байта
    mov bl,al
    and bl,11110000b
    cmp bl, 10100000b
    jne equal5
        or al,11110000b
    equal5:

    ;правой половины младшего байта
    mov bl,al
    and bl,00001111b
    cmp bl, 00001010b
    jne equal6
        or al,00001111b
    equal6:
    
    ;левая половина старшего байта
    mov bl,ah
    and bl,11110000b
    cmp bl, 10100000b
    jne equal7
        or ah,11110000b
    equal7:

    ;правая половина старшего байта
    mov bl,ah
    and bl,00001111b
    cmp bl, 00001010b
    jne equal8
        or ah,00001111b
    equal8:

	
    push eax
    push offset format
    call crt_printf
	add esp, 8
	call crt__getch
END START