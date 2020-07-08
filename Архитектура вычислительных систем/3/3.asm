.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
      include c:\masm32\include\windows.inc
      include c:\masm32\include\kernel32.inc
      include c:\masm32\include\user32.inc
      includelib c:\masm32\lib\user32.lib
      includelib c:\masm32\lib\kernel32.lib
.DATA
      a db 84
      b db -52
      d db 34
      x dw -1864

      save db 8 dup(0)
.CODE
START:
      XOR EAX, EAX
      XOR EBX, EBX 
      XOR ECX, ECX
      XOR EDX, EDX

      MOVSX ECX, a                  ; запись с расширением в ECX байта из a
      MOVSX EAX, x                  ; запись с расширением в EAX слова из x
      IMUL ECX                      ; умножение EAX на ECX, результат в EAX     ; a*x
      MOV EBX, EAX                  ; запись данных из EAX в EBX

      MOVSX ECX, b                  ; запись с расширением в ECX байта из b
      MOVSX EAX, x                  ; запись с расширением в EAX слова из x
      IMUL EAX                      ; умножение EAX на EAX, результат в EAX     ; x^2
      IMUL ECX                      ; умножение EAX на ECX, результат в EDX:EAX ; b*x^2
      ADD EAX, EBX                  ; сложение EAX и EBX, результат в EAX       ;
      ADC EDX, 0                    ; сложение EDX и переполнения               ; a*x+b*x^2

      MOV dword ptr save(0), EDX    ; перенос данных из EDX в память save(0)
      MOV dword ptr save(4), EAX    ; перенос данных из EAX в память save(4)

      MOVSX ECX, d                  ; запись с расширением в ECX байта из d
      MOVSX EAX, x                  ; запись с расширением в EAX слова из x
      IMUL ECX                      ; умножение EAX на ECX, результат в EAX     ; d*x
      MOV ECX, EAX                  ; перенос данных из EAX в ECX
      MOVSX EAX, x                  ; запись с расширением в EAX слова из x
      IMUL EAX                      ; умножение EAX на EAX, результат в EAX     ; x^2
      IMUL ECX                      ; умножение EAX на ECX, результат в EDX:EAX ; d*x^3
      ADD EAX, dword ptr save(4)    ; сложение EAX и участка памяти save(4)     ;
      ADC EDX, 0                    ; сложение EDX и переполнения               ; a*x+b*x^2+d*x^3
      ADD EDX, dword ptr save(0)    ; сложение EDX и участка памяти save(0)     ;

      SUB EAX, 14*14*14             ; разность EAX выражения, результат в EAX   ; a*x+b*x^2+d*x^3-14^3
      CMP EAX, 0                    
      JG exit                       ; выход, если EAX > 0
      CMP EDX, 0
      JE exit                       ; выход, если EDX <> 0
      CDQ                           ; конечный результат записан в расширенном регистре EDX:EAX
     
exit: PUSH NULL
      CALL ExitProcess              ; завершение программы
END START
