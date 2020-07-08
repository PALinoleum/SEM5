.386 
.model flat, stdcall 
option casemap: none 

include c:\masm32\include\windows.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\user32.inc
includelib c:\masm32\lib\user32.lib
includelib c:\masm32\lib\kernel32.lib

.DATA
	x DW 78d
	a DW 39d
	pow2 DD ?
	pow3 DD ?
	d1 DD 2d
	d2 DD 6d
	t DB 9d, 4d, 2d
.CODE
START:
	; очистка регистров
	XOR EAX,EAX
	XOR EBX,EBX
	XOR EDX,EDX
	XOR ECX,ECX
	
	; x-a = 50 = 0x32
	MOV AX,x
	CWDE 
	MOV ECX,EAX
	MOV AX,a
	CWDE 
	MOV EDX,EAX
	SUB ECX,EDX

	;получение степеней x-a
	MOV EAX,ECX
	
	;(x-a)^2 = 2500 = 0x9C4
	MUL ECX
	MOV pow2,EAX
	
	;(x-a)^3 = 125000 = 0x1E848
	MUL ECX
	MOV pow3,EAX

	;ECX = (x-a)*t_1
	MOV AL,t[0]
	CBW
	CWDE
	IMUL ECX,EAX

	;EBX = (x-a)^2*t_2/2
	;преобразование t_2 до 32 бит 
	MOV AL,t[1]
	CBW
	CWDE
	;(x-a)^2*t_2
	MOV EBX,pow2
	IMUL EBX,EAX
	;деление на 2
	XOR EDX,EDX
	MOV EAX,EBX
	IDIV d1
	;перенос результата в EBX
	MOV EBX,EAX
	
	;EAX = (x-a)^3*t_3/6
	;преобразование t_3 до 32 бит 
	MOV AL,t[2]
	CBW
	CWDE
	MOV EDX,EAX
	MOV EAX,pow3
	IMUL EAX,EDX
	XOR EDX,EDX
	IDIV d2
	
	;(x-a)*t_1 + (x-a)^2*t_2/2 + (x-a)^3*t_3/6
	ADD EAX,EBX
	ADD EAX,ECX
	
END START
