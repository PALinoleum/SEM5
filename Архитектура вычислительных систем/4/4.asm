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
    x dw 12 ; 26 ; 20 
    y db -5 ; 16 ; 12 
    z db 10 ; -2 ; -8 
       ; p3 ; p2 ; p1 

    fmt db "%d", 0
.code
START:
    MOVSX ECX, y        ; записывем y в ECX
    CMP ECX, 10         ; если y <= 10, отправляемся к p3
    JLE p3
    MOVSX ECX, z        ; записываем z в ECX
    CMP ECX, 0          ; если z < 0, отправляемся в neg 
    JL negation

abs:
    CMP EAX, 5          ; если abs(z) > 5, отправляемся в p1
    JG p1
    JMP p2              ; если y > 10 и abs(z) <= 5, отправляемся в p2

negation:
    MOV EAX, -1         ; записывем -1 в EAX
    CBW
    CWDE
    IMUL ECX            ; умножаем EAX на EDX ; abs(z)
    JMP abs             ; отправляемся в abs

 p1:
    XOR EAX, EAX        ; очищаем EAX
    MOV AX, x           ; записываем x в EAX
    MOVSX EDX, y        ; записываем y в EDX
    ADD EAX, EDX        ; складываем EAX и EDX ; x + y
    ADD EAX, 1          ; прибавляем 1 к EAX ; x + y + 1
    IMUL EAX            ; умножаем EAX на EAX, результат в EAX ; (x+y+1)^2
    MOV EBX, EAX        ; записываем EAX в EBX

    MOVSX EAX, z        ; записываем z в EAX
    IMUL EAX            ; умножаем EAX на EAX, результат в EAX ; z^2
    IMUL EAX            ; умножаем EAX на EAX, результат в EAX ; z^4
    IMUL EBX            ; умножаем EAX на EBX, результат в EAX ; (x+y+1)^2 * z^4
    MOV EBX, EAX        ; записываем EAX в EBX

    MOVSX EAX, y        ; записываем y в EAX
    IMUL EAX            ; умножаем EAX на EAX, результат в EAX ; y^2
    MOVSX EDX, y        ; записываем y в EDX
    IMUL EDX            ; умножаем EAX на EDX, результат в EAX ; y^3
    SUB EAX, 2          ; вычитаем 2 из EAX ; y^3 + 2
    MOV ECX, EAX        ; записываем EAX в ECX
    MOV EAX, EBX        ; записываем EBX в EAX
    CDQ
    IDIV ECX            ; делим EAX на ECX, результат в EDX:EAX ; (x+y+1)^2 * z^4 / (y^3 + 2)

    PUSH EAX            ; загрузка в стек первого аргумента
    PUSH offset fmt     ; загрузка в стек второго аргумента
    CALL crt_printf     ; вызов подпрограммы вывода
    ADD ESP, 8          ; освобождение памяти
    
    JMP exit

 p2:
    MOV EAX, 1          ; записываем 1 в EAX
    XOR EBX, EBX
    MOV BX, x           ; записываем x в EBX
    IDIV EBX            ; делим EAX на EBX, результат в EAX ; 1/x
    MOV EBX, EAX        ; записываем EAX в EBX
    
    MOV EAX, ECX        ; запимываем ECX в EAX ; z
    IMUL EAX            ; умножаем EAX на EAX, результат в EAX ; z^2
    MOV ECX, EAX        ; записываем EAX в ECX
    MOV EAX, -1         ; записываем -1 в EAX     
    IMUL ECX            ; умножаем EAX на ECX, результат в EAX ; -z^2
    ADD EBX, EAX        ; складываем EBX и EAX, результат в EBX ; -z^2 + 1/x

    XOR EAX, EAX        
    MOV AX, x           ; записываем x в EAX
    MOV ECX, EBX        ; записываем EBX в ECX
    MOVSX EBX, y        ; записываем y в EBX
    ADD EBX, 10         ; прибавляем 10 к EBX ; y + 10
    XOR EDX, EDX
    IDIV EBX            ; делим EAX на EBX, результат в EAX ; x/(y+10)
    ADD EAX, ECX        ; складываем EAX и ECX, результат в EAX ; -z^2 + 1/x + x/(y+10)

    PUSH EAX            ; загрузка в стек первого аргумента
    PUSH offset fmt     ; загрузка в стек второго аргумента
    CALL crt_printf     ; вызов подпрограммы вывода
    ADD ESP, 8          ; освобождение памяти
    
    JMP exit
    
 p3:
    MOVSX EAX, z        ; записываем z в EAX
    ADD EAX, 1          ; прибавляем 1 к EAX ; z + 1
    MOV EDX, 2          ; записываем 2 в EDX
    IMUL EDX            ; умножаем EAX на EDX, результат в EAX ; 2*(z+1)
    IMUL ECX            ; умножаем EAX на ECX, результат в EAX ; 2*(z+1)*y
    MOV EBX, EAX        ; записываем EAX в EBX

    XOR EAX, EAX
    MOV AX, x           ; записываем x в AX
    IMUL EAX            ; умножаем EAX на EAX, результат в EAX ; x^2
    MOV ECX, -5         ; записываем -5 в ECX
    IMUL ECX            ; умножаем EAX на ECX, результат в EAX ; -5*(x^2)
    SUB EAX, EBX        ; вычитаем EBX из EAX, результат в EAX ; -5*(x^2) - 2*(z+1)*y

exit:
    PUSH EAX            ; загрузка в стек первого аргумента
    PUSH offset fmt     ; загрузка в стек второго аргумента
    CALL crt_printf     ; вызов подпрограммы вывода
    ADD ESP, 8          ; освобождение стека
    CALL crt__getch
    PUSH NULL
    CALL ExitProcess
    
END START
