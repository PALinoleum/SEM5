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
    x db 1, 2, 3, 2, 1
    y dw 6, -6, -3, 3, -1
    k dw 4
    n db 5

    i db 0
    j db 0
    f dd 0
    r dd 0

    save dd 0

    fmt db "%d", 0
    
.code

func proc
    PUSH EBX
    PUSH ECX            ; сохраняем EBX и ECX

    XOR ECX, ECX
    MOV CL, [ESP+8+8]   ; записываем xi в ECX
    CMP ECX, 0
    JLE endFunc         ; переходим к endFunc, если xi < 0
    
subLoop:
    XOR EDX, EDX
    MOV DL, j
    MOV AX, y[EDX*2]    ; записываем yj в EAX
    CWDE
    MOV EBX, EAX        ; записываем EAX в EBX
    SUB EBX, 1          ; вычитаем 1 из EBX ; yi-1
    CMP EBX, 0
    JGE cont            ; переходим к con, если yi-1 > 0
    MOV EAX, -1         ; записываем -1 в EAX
    IMUL EBX            ; умножаем EAX на EBX, результат в EAX ; abs(yi-1)
    MOV EBX, EAX        ; запимываем EAX в EBX
cont:

    MOV EAX, dword ptr f[0]
    ADD EAX, EBX        ; сохраняем результат работы subLoop
    MOV dword ptr f[0], EAX

    XOR EAX, EAX
    MOV AL, j
    INC AL
    MOV j, AL          ; сохраняем новое значение j ; j+1
    
    DEC ECX            ; уменьшаем ECX на 1
    CMP ECX, 0
    JG subLoop         ; переходим в subLoop, если ECX >= 0

endFunc:
    MOV j, 0 
    POP ECX
    POP EBX            ; возвращаем EBX и ECX
    RET 8              ; выходим из функции
func endp

START:
    XOR ECX, ECX
    MOV CL, n           ; записываем n в ECX
    CMP ECX, 0
    JLE exit            ; переходим к mainLoop, если n < 0
    
mainLoop:
    XOR EDX, EDX
    MOV Dl, i
    XOR EBX, EBX
    MOV BL, x[EDX]      ; записываем xi в EBX
    MOV AX, y[EDX*2]    ; записываем yi в EAX
    CWDE
    ADD EBX, EAX        ; складываем EBX и EAX, результат в EBX ; x1 + yi
    XOR EAX, EAX
    MOV AX, k           ; записываем k в EAX
    IMUL EBX            ; умножаем EAX на EDX, результат в EAX ; k*(xi+yi)
    MOV EBX, EAX        ; записываем EAX в EBX
    
    XOR EAX, EAX
    MOV AX, k           ; записываем k в EAX
    IMUL EAX            ; умножаем EAX на EAX, результат в EAX ; k^2
    XOR EDX, EDX
    MOV DX, k           ; записываем k в EDX
    IMUL EDX            ; умножаем EAX на EDX, результат в EAX ; k^3
    ADD EBX, EAX        ; складываем EBX и EAX, результат в EBX ; k*(xi+yi) + k^3

    XOR EDX, EDX
    MOV DL, i
    MOV AX, y[EDX*2]    ; записываем yi в EAX
    CWDE
    IMUL EAX            ; умножаем EAX на EAX, результат в EAX ; yi^2
    SUB EBX, EAX        ; вычитаем EAX и EBX, результат в EBX ; k*(xi+yi) + k^3 - yi^2

    XOR EDX, EDX
    MOV DL, i
    XOR EAX, EAX
    MOV AL, x[EDX]
    PUSH EAX
    MOV AX, y[EDX*2]
    CWDE
    PUSH EAX
    CALL func           ; вызываем подпрограмму func с аргументами xi и yi

    MOV EAX, dword ptr f ; f(xi,yi)
    MOV f, 0
    MOV dword ptr save, ECX
    XOR ECX, ECX
    MOV CX, k           ; записываем k в EDX
    XOR EDX, EDX
    IDIV ECX            ; делим EAX на EDX, результат в EAX ; f(xi,yi)/k
    MOV ECX, dword ptr save
    ADD EBX, EAX        ; складываем EAX и EBX, результат в EBX ; k*(xi+yi) + k^3 - yi^2 + f(xi,yi)/k

    MOV EAX, dword ptr r
    ADD EAX, EBX        ; сохраняем результат работы mainLoop
    MOV dword ptr r, EAX

    XOR EAX, EAX
    MOV AL, i
    INC AL
    MOV i, AL           ; сохраняем новое значение i ; i+1

    DEC ECX             ; уменьшаем ECX на 1
    CMP ECX, 0
    JG mainLoop         ; переходим к mainLoop, если ECX >= 0
    
exit:
    MOV EAX, dword ptr r
    PUSH EAX            ; загрузка в стек первого аргумента
    PUSH offset fmt     ; загрузка в стек второго аргумента
    CALL crt_printf     ; вызов подпрограммы вывода
    ADD ESP, 8          ; освобождение стека
    CALL crt__getch
    PUSH NULL
    CALL ExitProcess

END START
