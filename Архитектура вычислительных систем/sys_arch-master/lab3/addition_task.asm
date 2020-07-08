.386
.MODEL FLAT, STDCALL
OPTION CASEMAP: NONE
INCLUDE C:\MASM32\INCLUDE\WINDOWS.INC
INCLUDE C:\MASM32\INCLUDE\KERNEL32.INC
INCLUDE C:\MASM32\INCLUDE\USER32.INC
INCLUDELIB C:\MASM32\LIB\USER32.LIB
INCLUDELIB C:\MASM32\LIB\KERNEL32.LIB


.DATA
	a DD 0FFFFFFFFh,0FFFFFFFFh
	b DD 0FFFFFFFFh,0FFFFFFFFh
	r DD ?,?,?,?
.CODE
START:
	xor eax,eax
	xor edx,edx
	xor ecx,ecx
	xor ebx,ebx
	xor ebp,ebp

	mov eax,dword ptr [a+4]
	mul dword ptr [b+4]	
	mov ebx,edx
	mov dword ptr [r],eax


	mov eax,dword ptr [a]
	mul dword ptr [b+4]
	add ebx,eax
	adc ecx,0
	adc ebp,0
	mov ecx,edx

	mov eax,dword ptr [a+4]
	mul dword ptr [b]
	add ebx,eax
	adc ecx,0
	adc ebp,0
	add ecx,edx
	adc ebp,0
	mov dword ptr [r+4],ebx

	mov eax,dword ptr [a]
	mul dword ptr [b]
	add ecx,eax
	adc ebp,0
	mov dword ptr [r+8],ecx
	add ebp,edx
	mov dword ptr [r+12],ebp
END START
