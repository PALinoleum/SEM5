.386
.model FLAT, STDCALL
option casemap: NONE
    include c:\masm32\include\windows.inc
    include c:\masm32\include\kernel32.inc
    include c:\masm32\include\user32.inc
    include c:\masm32\include\msvcrt.inc
    includelib c:\masm32\lib\user32.lib
    includelib c:\masm32\lib\kernel32.lib
    includelib c:\masm32\lib\msvcrt.lib
.data
    arr dw 1, 2, 3, 4, 5

    n dd 5

    i dd 0

    fmt db "(arr[%d])^2 = %d", 10, 0
.code

output_square proc
    MOV ECX, dword ptr n
    CMP ECX, 0 
    JLE exit
point:
    MOV EDX, dword ptr i
    XOR EBX, EBX
    MOV BX, arr[EDX*2]
    
    INC EDX
    MOV dword ptr i, EDX
    XOR EDX, EDX
    
    MOV EAX, EBX
    MUL EAX
    
    PUSH EAX
    PUSH EBX
    PUSH offset fmt
    CALL crt_printf
    ADD ESP, 12
    
    MOV ECX, dword ptr n
    MOV EBX, dword ptr i
    SUB ECX, EBX
    CMP ECX, 0
    JG point
    
    RET 12
output_square endp
    
START:
    CALL output_square
    INC EAX
exit:
    CALL crt__getch
    PUSH NULL
    CALL ExitProcess
END START