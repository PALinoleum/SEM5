.386 
.model flat, stdcall 
option casemap: none 

include c:\masm32\include\windows.inc
include c:\masm32\include\kernel32.inc
include c:\masm32\include\user32.inc
includelib c:\masm32\lib\user32.lib
includelib c:\masm32\lib\kernel32.lib

.DATA
    as DB 10, 13, ;"a-s", 0 
    h DW 20 
    w DW 100 
    s DD ? 
    DT 17834.55 

.CODE

START:
    XOR EAX, EAX
    MOV AX, h
    MUL w
    MOV s, EAX
    PUSH 0
    CALL ExitProcess
END START
