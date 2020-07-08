.386
.model flat, stdcall
option casemap :none

.code
; Инициализирующая функция
DLLMain proc hlnstDLL:DWORD, reason:DWORD, unused:DWORD
  mov EAX, 1 
  ret
DLLMain endp

LibMain proc hlnstDLL:DWORD, reason:DWORD, unused:DWORD
  mov EAX, 1 
  ret
LibMain endp

swap proc
  push eax
  push ebx 
  push ecx 
  push edx 
  push esi 
  push ebp 
  mov ebp,[esp+36]
  mov esi,[esp+32]
  mov ebx,[esp+28]
  mov eax,[ebp+4*esi]
  mov edx,[ebp+4*ebx]
  mov ecx,edx
  mov edx,eax
  mov eax,ecx
  mov [ebp+4*esi],eax
  mov [ebp+4*ebx],edx
  pop ebp
  pop esi 
  pop edx
  pop ecx
  pop ebx
  pop eax
	ret 12
swap endp

_sort proc
  push ebx ;занято
  push ecx ;занято
  push edx 
  push esi ;занято
  push ebp ;занято
;ebx - arr
    mov ebx,[esp+24]
    ;ecx - arr_lenght
    mov eax,[esp+28]
    mov ecx,[eax]
    sub ecx,1
    ;pos_arr - [esp+40]
    ;neg_arr - [esp+44]
    
    ;ebp - pos_count [esp+46]
    ;esi - neg_count 
    xor ebp,ebp
    xor esi,esi
    
    to_arr_loop:
        mov eax,[ebx+4*ecx]
        cmp eax,0
        jge check_pos
        check_neg:
          mov edx,[esp+36]
          mov [edx+esi*4],eax
          add esi,1
          jmp check_end
        check_pos:
          mov edx,[esp+32]
          mov [edx+ebp*4],eax
          add ebp,1        
        check_end:
        sub ecx,1
        cmp ecx,-1
        jne to_arr_loop
    
    push ebp
    push [esp+36]
    call select_sort_invert

    push esi
    push [esp+40]
    call select_sort_invert
    mov eax,[esp+40]
    mov [eax],ebp
    mov eax,esi

  pop ebp
  pop esi
  pop edx
  pop ecx
  pop ebx
  ret 20
_sort endp

select_sort_invert proc
  push eax
  push ebx 
  push ecx;указатель на массив 
  push edx;указатель на элемент j 
  push esi;указатель на элемент i
  push ebp;указатель на минимальный элемент 
  ;[esp+28] - массив
  ;[esp+32] - размер массива
  mov ecx,[esp+28]
  xor esi,esi
  xor edx,edx
  xor ebp,ebp
  mov esi,-1
  outer_cycle:
    add esi,1
    mov ebp,esi
    mov edx,esi
    inner_cycle:
      add edx,1
      mov eax,[ecx+edx*4]
      mov ebx,[ecx+ebp*4]
      cmp eax,ebx
      jnl not_if1
      mov ebp,edx
      not_if1:
      mov eax,[esp+32]
      sub eax,1
      cmp edx,eax
      jl inner_cycle
    cmp ebp,esi
    je not_if2
    push ecx
    push esi
    push ebp
    call swap
    mov ebp,esi
    not_if2:
    mov eax,[esp+32]
    sub eax,2
    cmp esi,eax
    jl outer_cycle
  pop ebp
  pop esi 
  pop edx
  pop ecx
  pop ebx
  pop eax
  ret 8
select_sort_invert endp

func_stdcall proc
  push ebp		        ; пролог
    mov ebp, esp	    ; сохранение адреса вершины стека в регистре ebp - пролог
    push [ebp+8+12]		; neg_arr
    push [ebp+8+16]		; pos_c
    push [ebp+8+8]		; pos_arr
    push [ebp+8+4]		; len
    push [ebp+8]		  ; arr 
    call _sort	      ; вызов рабочей функции из обертки 
  leave			          ; эпилог
  ret 16
func_stdcall endp

func_cdecl proc
  push ebp		        ; пролог
    mov ebp, esp	    ; сохранение адреса вершины стека в регистре ebp - пролог
    push [ebp+8+12]		; neg_arr
    push [ebp+8+16]		; pos_c
    push [ebp+8+8]		; pos_arr
    push [ebp+8+4]		; len
    push [ebp+8]		  ; arr 
    call _sort	      ; вызов рабочей функции из обертки 
  leave			          ; эпилог
  ret 
func_cdecl endp

func_fastcall proc
  push ebp		        ; пролог
    mov ebp, esp	    ; сохранение адреса вершины стека в регистре ebp - пролог
    push [ebp+8+4]		; neg_arr
    push [ebp+8+8]		; pos_c
    push [ebp+8]		  ; pos_arr
    push edx		      ; len
    push ecx		      ; arr 
    call _sort	      ; вызов рабочей функции из обертки 
  leave			          ; эпилог
  ret 12
func_fastcall endp

func_stdcall_var proc arr:dword, len:dword, pos_arr:dword, pos_c:dword,neg_arr:dword
    push neg_arr		  ; neg_arr
    push pos_c		    ; pos_c
    push pos_arr		  ; pos_arr
    push len	       	; len
    push arr		      ; arr 
    call _sort	      ; вызов рабочей функции из обертки 
  ret 16
func_stdcall_var endp

func_cdecl_var proc c arr:dword, len:dword, pos_arr:dword, pos_c:dword,neg_arr:dword
    push neg_arr		  ; neg_arr
    push pos_c		    ; pos_c
    push pos_arr		  ; pos_arr
    push len	       	; len
    push arr		      ; arr 
    call _sort	      ; вызов рабочей функции из обертки 
  ret 
func_cdecl_var endp

end LibMain