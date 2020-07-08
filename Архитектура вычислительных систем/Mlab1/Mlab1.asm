.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA
      x dw 65535
      y dw 65535
.CODE
START:
      XOR EAX, EAX
      XOR EBX, EBX   ; первичная очистка регистров
      XOR EDX, EDX

      MOV AX, y      ; запись в регистр AX данных из ячейки памяти, соответствующей y
      MOV EBX, 65536 ; запись в регистр EBX большого числа
      MUL EBX        ; умножение регистра EAX на регистр EBX,
                     ; результат сохраняется в расширенном регистре EDX:EAX
                     ; даже при максимальном значении y, результат полностью поместится в EAX
      MOV EBX, EAX   ; запись значения регистра EAX в регитр EBX
      
      XOR EAX, EAX   ; очистка регистра EAX
      MOV AX, x      ; запись в регистр AX данных из ячеки памяти, соответствующей x
      ADD EAX, EBX   ; сложение данных из регистров EAX и EBX
                     ; результат записывается в регистр EAX
      
      XOR EBX, EBX   ; очистка регистра EBX
      MOV BL, 17     ; запись в регистр BL десятеричного числа 17
      DIV EBX        ; деление расширенного регистра EDX:EAX на регистр EBX
                     ; в EAX будет записано частное, в EDX - остаток

      PUSH NULL
      CALL ExitProcess
END START
