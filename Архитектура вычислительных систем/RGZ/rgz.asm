.386
.model flat,stdcall
option casemap:none
include C:\masm32\include\windows.inc
include C:\masm32\include\user32.inc
include C:\masm32\include\kernel32.inc
include C:\masm32\include\gdi32.inc
INCLUDE C:\masm32\include\msvcrt.inc
includelib C:\masm32\lib\msvcrt.lib
includelib C:\masm32\lib\user32.lib 
includelib C:\masm32\lib\kernel32.lib 
includelib C:\masm32\lib\gdi32.lib
 
WinMain proto :DWORD,:DWORD,:DWORD,:DWORD
.data?
hInstance dd ? 
CommandLine dd ?
.data
AppName db " ",0
ClassName db "SimpleWinClas",0

maxX SDWORD ? 
maxY SDWORD ? 

sx SDWORD ? 		;������ ���� �� �
sy SDWORD ? 		;������ ���� �� �

;���������
c100  SDWORD 100
c1 	  SDWORD 1
c0	  SDWORD 0

;��������� ����������
temp  SDWORD ? 
t1 	  SDWORD ?
t2 	  SDWORD ?

; ��������� - �������
normX SDWORD ?
normY SDWORD ?
normX2 SDWORD ?
normY2 SDWORD ?
scalar SDWORD ?
len SDWORD ?

format db "EAX = %d", 13, 10, 0

;��������� ������
ballX 	SDWORD 500 	;x 
ballY	SDWORD 500	;y
ballR 	SDWORD 10 	;������ ����
ballDX SDWORD 5 	;�������� �� �
ballDY SDWORD 4	;�������� �� �
ballS 	SDWORD 2 	

;����� ����� � ���� ������
left_top_t1_x SDWORD 100 
left_top_t1_y SDWORD 100
left_top_t2_x SDWORD 100
left_top_t2_y SDWORD 300

;����� ����� � ���� ������
right_top_t1_x SDWORD 500 
right_top_t1_y SDWORD 100
right_top_t2_x SDWORD 500
right_top_t2_y SDWORD 300

;����� ����� � ���� ������
left_bottom_t1_x SDWORD 100 
left_bottom_t1_y SDWORD 100
left_bottom_t2_x SDWORD 500
left_bottom_t2_y SDWORD 100

;����� ����� � ���� ������
right_bottom_t1_x SDWORD 100 
right_bottom_t1_y SDWORD 300
right_bottom_t2_x SDWORD 500
right_bottom_t2_y SDWORD 300

;������ ������ �������������� � ������ ������ ����, ������� ������ ������ ������ ����������
circleR SDWORD 0
 
hdc 	SDWORD ?
memBit 	SDWORD ?
hBitmap SDWORD ?

ps	PAINTSTRUCT <?>
.code 

;�������� ������
circle_check proc
	pushad
		;a[esp+52] - � ������ �������
		;b[esp+48] - � ������ �������
        ;r[esp+44] - ������ �������
		;x[esp+40] - ���������� ������ �� �
		;y[esp+36] - ���������� ������ �� �
		
		;x-a
		fild dword ptr [esp + 40] ; st(1) = x
		fild dword ptr [esp + 52] ; st(0) = a
		fsubp st(1), st(0)
		fmul st(0), st(0)
        ;y-b
        fild dword ptr [esp + 36] ; st(1) = y
        fild dword ptr [esp + 48] ; st(0) = b
		fsubp st(1), st(0)
		fmul st(0), st(0)
        faddp st(1), st(0)
        
		fild dword ptr [esp + 44] ; st(0) = r
		fiadd ballR				  ; ����������� ��������� ������ ������
		fmul st(0), st(0)
	popad
        db 0dbh, 0f0h+1
        jae check_eq
        check_neq:
            mov eax,0
            jmp check_end
        check_eq:
            mov eax,1
        check_end:
            FFREE st(0) 
            FFREE st(1) 
			FFREE st(2)
			FFREE st(3)
    ret 20
circle_check endp

line_check proc

    PUSHAD     
		;x1[esp+56]
		;y1[esp+52]
		;x2[esp+48]
		;y2[esp+44]
		;x[esp+40]
		;y[esp+36]
		
        ;x2-x1
		fild dword ptr [esp+48]
		fild dword ptr [esp+56]
		fsubp st(1),st(0)
        ;y-y1
            fild dword ptr [esp+36]
            fild dword ptr [esp+52]
		fsubp st(1),st(0)
            fmulp st(1),st(0)
	  ;y2-y1
            fild dword ptr [esp+44]
		fild dword ptr [esp+52]
		fsubp st(1),st(0)
        ;x-x1
            fild dword ptr [esp+40]
            fild dword ptr [esp+56]
		fsubp st(1),st(0)
            fmulp st(1),st(0)
            fsubp st(1),st(0)
            SUB ESP, 8
            fstp dword ptr [ESP]
            MOV EAX, [ESP]
            ADD ESP, 8
            CMP EAX, 0
            JNE bad

        ;x1-x
		fild dword ptr [esp+56]
		fild dword ptr [esp+40]
		fsubp st(1),st(0)
        ;x2-x
            fild dword ptr [esp+48]
            fild dword ptr [esp+40]
		fsubp st(1),st(0)
            fmulp st(1),st(0)
            SUB ESP, 8
            fstp dword ptr [ESP]
            MOV EAX, [ESP]
            ADD ESP, 8
            CMP EAX, 0
            JG bad

    
	  ;y1-y
            fild dword ptr [esp+52]
		fild dword ptr [esp+36]
		fsubp st(1),st(0)
        ;y2-y
            fild dword ptr [esp+44]
            fild dword ptr [esp+36]
		fsubp st(1),st(0)
            fmulp st(1),st(0)
            SUB ESP, 8
            fstp dword ptr [ESP]
            MOV EAX, [ESP]
            ADD ESP, 8
            CMP EAX, 0
            JG bad
    POPAD
    MOV EAX, 1
    JMP exit
bad:
    POPAD
    MOV EAX, 0
    JMP exit
exit:
    ffree st(0)
    ffree st(1)
    ffree st(2)
    ffree st(3)
    ffree st(4)
    ffree st(5)
    ffree st(6)
    ffree st(7)
    RET 24
line_check endp


start:
		invoke GetModuleHandle, NULL 
		mov	hInstance,eax ;���������� ���������� ����������
		;���� ���������� �������� ����� ������ ���� ��������� � �� �������� ������������. 
		;���������� hInstance ���� ����� ��������� ��������, ���������� � ��������� ���������.
		
		;HINSTANCE hPrevInstance � ���������� ����������� ���������� ����������.
		;���� ���������� ������� �� ������ ������ Windows - ������ �����, ��� �� ������� �� ����������.
		;HINSTANCE hPrevInstance=NULL � ���������
		invoke GetCommandLine ;get
		mov	CommandLine,eax ;��������� �� ������ ��������� ������, ��������� ��� ������� ���������.
		;int nCmdShow � ��� �������� �������� �������� ��� ���� (��������, ��������� ��� �����������)
		;int nCmdShow=SW_SHOWDEFAULT 
		invoke WinMain, hInstance, NULL, CommandLine, SW_SHOWDEFAULT 
		invoke ExitProcess, eax

WinMain proc hInst:HINSTANCE, hPrevInst:HINSTANCE, CmdLine:LPSTR, CmdShow:DWORD
		LOCAL wc:WNDCLASSEX ;SS:0018FF68  ��������� WNDCLASSEX �������� ���������� � ������ ���a
		LOCAL msg:MSG ;SS:0018FF4C //��������� ���������
		LOCAL hwnd:HWND ;SS:0018FF78 ���������� - ���������� ����� ���������� ���� ���������
	
		mov wc.cbSize, SIZEOF WNDCLASSEX ;������������� ������ ���� ���������, � ������
		mov wc.style, CS_HREDRAW or CS_VREDRAW ;������������� �����(�) ������. ���� ���� ��������� ����� ���� ����� ����������� ������ ������
		mov wc.lpfnWndProc,OFFSET   WndProc ;��������� �� ������� ���������.
		mov wc.cbClsExtra,NULL ;������������� ����� �������������� ����, ������� ����������� ����� �� ���������� ������ ����
		mov wc.cbWndExtra,NULL ;������������� ����� �������������� ������, ������� ����������� ����� �� ����������� ����
		push hInstance ;���������� ����������, ������� �������� ������� ��������� ��� ������.
		pop wc.hInstance
		mov wc.hbrBackground, COLOR_WINDOW+1;���������� ����� ���� ������.
		mov wc.lpszMenuName ,NULL ;��������� �� ���������� ������ � �������� ����� ������ ('\0')
		mov wc.lpszClassName, OFFSET ClassName ;��������� �� ���������� ������ � ����� � ����� ���  ����
	
		invoke LoadIcon,hInst,500
		mov wc.hIcon, eax ;���������� ������ ������
		
		mov wc.hIconSm,eax ;���������� ���������� ������, ������� ������ � ������� ����
		invoke LoadCursor,NULL,IDC_ARROW
		mov wc.hCursor,eax ;���������� ������� ������
		invoke RegisterClassEx,addr wc ; ������������ ����� ���� ��� ������������ �������������
		;CreateWindowEx ������� �������������, ������������� ��� �������� ���� � ����������� ������
		
		;DWORD dwExStyle,      // ���������� ����� ����
		;LPCTSTR lpClassName,  // ��������� �� ������������������ ��� ������
		;LPCTSTR lpWindowName, // ��������� �� ��� ����
		;DWORD dwStyle,        // ����� ����
		;int x,                // �������������� ������� ����
		;int y,                // ������������ ������� ����
		;int nWidth,           // ������ ����
		;int nHeight,          // ������ ����
		;HWND hWndParent,      // ���������� ������������� ��� ���� ���������
		;HMENU hMenu,          // ���������� ���� ��� ID ��������� ����
		;HINSTANCE hInstance,  // ���������� ���������� ���������� ���������
		;LPVOID lpParam        // ��������� �� ������ �������� ����
		
		;���� ������� ����������� �������, ������������ �������� - ���������� ���������� ����.
		INVOKE CreateWindowEx,NULL,ADDR ClassName,ADDR AppName,\
			13303808,CW_USEDEFAULT,\
			CW_USEDEFAULT,CW_USEDEFAULT,CW_USEDEFAULT,NULL,NULL,\
			hInst,NULL
		mov hwnd,eax ;���������� ���������� ����.
		invoke LoadMenu,hInst,600 ;���p����� ������������� p���p� ����
		invoke SetMenu,hwnd,eax ;������������� � ��p�p��������� ���� ���� ��� ����, ��p��������� ��p����p�� Menu
	
		invoke ShowWindow,hwnd,SW_SHOWNORMAL ;hwnd-������������p ���� 
		;����p����� ��� �p���� ���� ��p����, ��������� ��p����p�� CmdShow
		invoke UpdateWindow,hwnd  ;��������� ������� ������� ��������� ���� hwnd -���������� ����
		.WHILE TRUE ;��������� ���� ��������� ���������
		
				;ADDR msg ��������� �� ��������� ���������, 
				;� ������� GetMessage ������ ���������.
				;2 �������� -��������� ����, �� �������� GetMessage ������ ��������� 
				;(NULL ��������, ��� GetMessage ��������� ��������� �� ���� ����, ������������� ������
				;3 �������� UINT wMsgFilterMin � ���������� ������������� ���������, ������� ������ GetMessage
				;4 �������� UINT wMsgFilterMax � ���������� ������������� ���������, ������� ������ GetMessage 
				;(���� � ��������� ���������� wMsgFilterMin � wMsgFilterMax �������� 0, ������� ����� ��������� ��� ���������)
				invoke GetMessage,ADDR msg,NULL,0,0
				;� eax ��������� -���������� ���������
				.BREAK .IF (!eax)
				invoke TranslateMessage, ADDR msg ;��������� use ����������
				invoke DispatchMessage, ADDR msg ;������� ���������� windows
		.ENDW
		mov eax,msg.wParam ;���������� �������������� ���������� � ���������
		ret
WinMain endp
;		HWND hwnd,���������� ������� ���������, ������� �������� ���������
;		UINT uMsg,���������� ���������.
;		WPARAM wParam,���������� �������������� ���������� � ���������
;		LPARAM lParam ���������� �������������� ���������� � ���������
WndProc proc hWnd:HWND, uMsg:UINT, wParam:WPARAM, lParam:LPARAM
		;##################################close window
		.if uMsg==WM_DESTROY ;���������� ����� ���������� ���������� ����
		;������� DeleteObject ������� ���������� ����, �����, �����, �������� ��������, ������ ��� �������,
		;���������� ��� ��������� �������, ��������� � ��������
			invoke DeleteObject,memBit;���������� ������������ �������
		;������� PostQuitMessage ��������� �������, ��� ����� ������ ������ �� ��, ����� ��������� ���� ������
		;�������� ���������� ��� ���������� ���������� ���������.
			invoke PostQuitMessage, NULL
		;##################################create window
		.elseif uMsg==WM_CREATE ;��������� �����, ����� ��������� �����������, ������� ����� ������� CreateWindowEx ,������ ���� ������� ����
			;set timer 
			fild c1
			fild c100
			fdiv
			fst temp
			;HWND hWnd, ���������� ����, ������� ������� � ��������
			;UINT_PTR nIDEvent, ��������� ������������� ������� �������� �� ����
			;UINT uElapse,��������� �������� ������� �������, � �������������.
			;TIMERPROC lpTimerFun ��������� �� �������, ������� ����������, ����� �������� ������� ������� ��������
			invoke SetTimer,hWnd,1,c1,0
			
			; get max size window 
			invoke GetSystemMetrics, SM_CXSCREEN
			mov maxX, eax
			invoke GetSystemMetrics,SM_CYSCREEN;������ � ������ ������ � ��������
			mov maxY, eax
	
			; ��������� ��������� 
			;��������� ���������� ����������� ��������� ����������
			invoke GetDC, hWnd ;hWnd ���������� ����
			mov hdc, eax
			;�������� ����� � ������ 
			;c������ �������� ���������� � ������ 
			invoke CreateCompatibleDC, hdc 
			mov memBit, eax
			; CreateCompatibleBitmap  ������� �������� �������
			;HDC hdc,        // ���������� DC
			;int nWidth,     // ������ �������, � ��������
			;int nHeight     // ������ �������, � ��������
			invoke CreateCompatibleBitmap, hdc, maxX, maxY 
			mov hBitmap, eax
			;���� ������� ����������� �������, ������������ �������� - ���������� 
			;������������ ��������� ������� (���������-��������� �������� �������� (DDB)
		
			;SelectObject �������� ������ � �������� �������� ���������� (DC). 
			;����� ������ �������� ���������� ������ ���� �� ������ ���
			invoke SelectObject, memBit, hBitmap
			
			; ########################################### ���������
			.elseif uMsg==WM_PAINT ; ������� ��� ������ ���������� ������ ������ �� ������������ ����� ���� ����������
				; ��������� �������
				invoke PatBlt, memBit, 0, 0, maxX, maxY, WHITENESS
				;BOOL PatBlt(
				;HDC hdc,      // ���������� ��������� ���������� (DC)
				;int nXLeft,   // x-���������� �������� ������ ���� ��������������
				;int nYLeft,   // y-���������� �������� ������ ���� ��������������
				;int nWidth,   // ������ ��������������
				;int nHeight,  // ������ ��������������
				;DWORD dwRop   // ��� ��������� ��������
				invoke GetStockObject, c1;��������� ���������� ������ �� ���������������� (�����������) ������, ������, ������� ��� ������
				invoke SelectObject, memBit, eax
				;��������� �������
				fld sy
				fld circleR
				fadd
				fstp temp
				push temp
				
				fld sx
				fld circleR
				fadd
				fstp temp
				push temp
				
				fld sy
				fld circleR
				fsub
				fstp temp
				push temp
				
				fld sx
				fld circleR
				fsub
				fstp temp
				push temp
				
				push memBit
				call Ellipse

                        ;��������� �������
				fld sy
				fld circleR
				fadd
				fstp temp
				push temp
				
				fld sx
				fld circleR
				fadd
				fstp temp
				push temp
				
				fld sy
				fld circleR
				fsub
				fstp temp
				push temp
				
				fld sx
				fld circleR
				fsub
				fstp temp
				push temp
				
				push memBit
				call Ellipse

                          ; ��������� �����
				push NULL
				push left_top_t1_y 
				push left_top_t1_x 
				push memBit
				call MoveToEx

				push left_top_t2_y 
				push left_top_t2_x  
				push memBit
				call LineTo

                            ; ��������� �����
				push NULL
				push right_top_t1_y 
				push right_top_t1_x 
				push memBit
				call MoveToEx

				push right_top_t2_y 
				push right_top_t2_x  
				push memBit
				call LineTo

                            ; ��������� �����
				push NULL
				push left_bottom_t1_y 
				push left_bottom_t1_x 
				push memBit
				call MoveToEx

				push left_bottom_t2_y 
				push left_bottom_t2_x  
				push memBit
				call LineTo

                            ; ��������� �����
				push NULL
				push right_bottom_t1_y 
				push right_bottom_t1_x 
				push memBit
				call MoveToEx

				push right_bottom_t2_y 
				push right_bottom_t2_x  
				push memBit
				call LineTo



				
				; ��������� ������
				fld ballY
				fld ballR
				fadd
				fstp temp
				push temp
				
				fld ballX
				fld ballR
				fadd
				fstp temp
				push temp
				
				fld ballY
				fld ballR
				fsub
				fstp temp
				push temp
				
				fld ballX
				fld ballR
				fsub
				fstp temp
				push temp
				
				push memBit
				call Ellipse
				
				mov temp, 0
			

				;��������� �� ������ � ����
				;HWND hwnd,            // ���������� ����
				;LPPAINTSTRUCT lpPaint // ���������� �� �����������
				invoke BeginPaint, hWnd, offset ps
				mov hdc, eax
				
				;BOOL BitBlt(
				;HDC hdcDest, // ���������� �������� DC
				;int nXDest,  // x-�����. ������ �������� ���� �������� ��������������
				;int nYDest,  // y-�����. ������ �������� ���� �������� ��������������
				;int nWidth,  // ������ �������� ��������������
				;int nHeight, // ������ �������� ��������������
				;HDC hdcSrc,  // ���������� ��������� DC
				;int nXSrc,   // x-�����. ������ �������� ���� ��������� ��������������
				;int nYSrc,   // y-�����. ������ �������� ���� ��������� ��������������
				;DWORD dwRop  // ��� ��������� ��������
				invoke BitBlt, hdc, 0, 0, sx, sy, memBit, 0, 0, SRCCOPY
				invoke EndPaint, hWnd, offset ps ;�������� ����� ����������� � �������� ����
				
				
			;��������� ������� ���� 
			.elseif uMsg==WM_SIZE ;���������� ���� ����� ����, ��� ��� ������ ���������
				xor eax, eax
				mov ax, word ptr lParam
				mov sx, eax
				mov eax, eax
				mov eax, lParam
				shr eax, 16
				mov sy, eax
								
			;=========================================== ������������ ������� ================================
			.elseif uMsg==WM_TIMER
			;WM_TIMER �������� �����������������
			
			;=========================================== �������� �� �������� � �������� =====================
			

                    ;�������� �� �������� � ������
                    xor eax,eax
			push left_top_t1_x
			push left_top_t1_y
			push left_top_t2_x
			push left_top_t2_y
			push ballX
			push ballY
			call line_check
			.IF(eax == 1)
				fild ballDX
				FCHS
				fistp ballDX
			.ENDIF

                    xor eax,eax
			push right_top_t1_x
			push right_top_t1_y
			push right_top_t2_x
			push right_top_t2_y
			push ballX
			push ballY
			call line_check
			.IF(eax == 1)
				fild ballDX
				FCHS
				fistp ballDX
			.ENDIF

                    xor eax,eax
			push left_bottom_t1_x
			push left_bottom_t1_y
			push left_bottom_t2_x
			push left_bottom_t2_y
			push ballX
			push ballY
			call line_check
			.IF(eax == 1)
				fild ballDY
				FCHS
				fistp ballDY
			.ENDIF

                    xor eax,eax
			push right_bottom_t1_x
			push right_bottom_t1_y
			push right_bottom_t2_x
			push right_bottom_t2_y
			push ballX
			push ballY
			call line_check
			.IF(eax == 1)
				fild ballDY
				FCHS
				fistp ballDY
			.ENDIF

                    
			;================================= �������� �� �������� � �������� =================================
			mov eax,ballX
			.IF(c0 >= eax || sx <= eax )
				fild ballDX
				FCHS
				fistp ballDX
			.ENDIF
			mov eax,ballY
			.IF(c0 >= eax || sy <= eax )
				fild ballDY
				FCHS
				fistp ballDY
			.ENDIF			
			
			;================================= �������� ������ ================================================
			; ���������� dx
			fild ballX
			fild ballDX
			fild ballS
			fmulp st(1),st
			faddp st(1),st
			FRNDINT
			fistp ballX
			; ���������� dy
			fild ballY
			fild ballDY
			fild ballS
			fmulp st(1),st
			faddp st(1),st
			FRNDINT
			fistp ballY
		
			invoke InvalidateRect, hWnd, 0, 0  ;��������� ������������� ��� ����������� ����
			;HWND hWnd,		// ��������� �� ����
			;CONST RECT *lpRect,	// ������������� �����������
			;BOOL bErase		// ����� �����������

			.else
				invoke DefWindowProc, hWnd, uMsg, wParam, lParam 
				;������� DefWindowProc ���������� ������� ���������� �� ���������,
				;����� ���������� ��������� �� ��������� ������ ��������� ����, ������� ���������� �� ������������
				ret
		.endif
	xor eax , eax
	ret
WndProc endp
end start		
