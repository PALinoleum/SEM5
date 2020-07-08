@echo off
set MASM=C:\masm32
set MASM_LIB=%MASM%\lib
set MASM_BIN=%MASM%\bin
set MASM_PARAMS=/c /coff
set LINK_PARAMS=/SUBSYSTEM:CONSOLE /LIBPATH:%MASM_LIB%
set OLLYDBG=C:\dbg\OLLYDBG.EXE
if not exist %MASM% (
    echo ���� � ��ᥬ����� ������⢨⥫��! �஢���� ���.
    exit /b 1
)
for %%a in (".") do set CURRENT_DIR_NAME=%%~na
echo %CURRENT_DIR_NAME%
set ARGUMENT=%~1
if defined ARGUMENT ( 
    if exist %ARGUMENT%.asm ( 
        set NAME=%ARGUMENT%
        goto ASSEMBLY
    )
)
if exist %CURRENT_DIR_NAME%.asm ( 
    set NAME=%CURRENT_DIR_NAME%
    goto ASSEMBLY
)
set /a count=0
for %%i in (*.asm) do (set /a count+=1 & set last_file=%%~ni)
if %count%==1 (
    if exist %last_file%.asm (
        set NAME=%last_file%
        goto ASSEMBLY
    )
)
echo �� 㤠���� ���� 䠩�� ��� ��ᥬ���஢����.
exit /b 1

:ASSEMBLY
echo ��ᥬ���஢����...
%MASM_BIN%\ml.exe %MASM_PARAMS% %NAME%.asm
if %ERRORLEVEL% NEQ 0 ( 
    echo �訡�� ��ᥬ���஢����
    exit /b 1
)
echo ���뢠���...
%MASM_BIN%\link.exe %LINK_PARAMS% %NAME%.obj
if %ERRORLEVEL% NEQ 0 ( 
    echo �訡�� ��뢠���
    exit /b 1
)

echo ����� �⫠�稪�...
if exist %OLLYDBG% (
    start %OLLYDBG% %NAME%.exe
    exit 0
) else (
    echo �⫠�稪 �� ������! �஢���� ���.
    exit /b 1
)
