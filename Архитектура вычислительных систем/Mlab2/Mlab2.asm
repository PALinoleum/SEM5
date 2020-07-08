.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA
      reg dw 0 ; 6F00h ; 7000h ; 714Fh
               ;   c1  ;   c2  ;   c3
.CODE
START:
      XOR EAX, EAX
      XOR EBX, EBX  ; начальная очистка регистров
      XOR ECX, ECX

      MOV AX, reg   ; первичная запись в регистр AX данных из области памяти reg
      
      MOV BX, AX    ; пересылка регистра AX в регистр BX
      
      CMP AH, 111   ; сравнение данных регистра AH и десятеричного числа 111 (6Fh)
      JZ c1         ; если результат предыдущей команды равен нулю, переход к флагу c1

      CMP AH, 112   ; сравнение данных регистра AH и десятеричного числа 112 (70h)
      JZ c2         ; если результат предыдущей команды равен нулю, переход к флагу c2

      CMP AH, 113   ; сравнение данных регистра AH и десятеричного числа 113 (71h)
      JGE c3        ; если результат больше или равен 113, переход к флагу c3

      JMP exit      ; переход к флагу выхода

  c1: MOVZX AX, BH  ; пересылка с расширением целого числа регистра BH в регистр AX
      MUL AL        ; целочисленное умножение AL на AL, результат в AX
      JMP exit      ; переход к флагу выхода

  c2: MOVZX AX, BH  ; пересылка с расширением целого числа регистра BH в регистр AX
      XOR BX, BX    ; очистка регистра BX
      MOV BL, 8     ; пересылка в регистр BL десятичного числа 8
      DIV BL        ; деление регистра AX на BL, частное в AL, остаток в AH
      JMP exit      ; переход к флагу выхода

  c3: MOV CL, AL    ; пересылка регистра AL в CL
      MOV CH, BL    ; пересылка регистра BL в CH
      NOT AL        ; инвертирование битов регистра AL ; НЕ AL
      NOT BL        ; инвертирование битов регистра BL ; НЕ BL
      AND AL, CH    ; логическое перемножение AL и CH, результат в AL ; (НЕ AL) И BL
      AND BL, CL    ; логическое перемножение BL и CL, результат в BL ; (НЕ BL) И AL
      OR AL, BL     ; логическое сложение AL и BL, результат в AL ; ((НЕ BL) И AL) ИЛИ ((НЕ AL) И BL)
      
exit: PUSH NULL
      CALL ExitProcess
      
END START
