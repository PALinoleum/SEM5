@echo off
echo -------------------
echo Считываем конфиг
echo -------------------
set conf_in=conf.json
set conf_out=config.tex
set tools_dir=tools
set tex_dir=tex_files


if not exist %conf_out% ( 
    goto build
)

for %%i in (%conf_in%) do set date1=%%~ti
for %%i in (%conf_out%) do set date2=%%~ti

if "%date1%"=="%date2%" ( 
    goto build
)

for /f %%i in ('dir /b /o:d %conf_in% %conf_out%') do set newest=%%i
if "%newest%"=="%conf_in%" ( 
    goto build
) else ( 
    goto end
)

:build
python %tools_dir%\build.py

:end
echo -------------------
echo Компиляция Markdown
echo -------------------
pandoc -o %tex_dir%\task_md.tex task.md
pandoc -o %tex_dir%\work_progress_md.tex work_progress.md
echo -------------------
echo Сборка листингов
echo -------------------
python %tools_dir%\build_listings.py
echo ----------------
echo Компиляция LaTeX
echo ----------------
pdflatex --shell-escape --halt-on-error %tex_dir%/lab.tex

if %ERRORLEVEL% NEQ 0 ( 
    echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
    echo Компиляция завершилась с ошибкой
    echo !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
)

echo -------------------------
echo Удаление временных файлов
echo -------------------------
rmdir /s /q _markdown_lab 2> nul
rmdir /s /q _minted-lab 2> nul
rmdir /s /q %tools_dir%\__pycache__ 2> nul
del %tex_dir%\*.aux 2> nul
del %tex_dir%\*.lua 2> nul
del %tex_dir%\*.in 2> nul
del %tex_dir%\*.log 2> nul
del %tex_dir%\*.out 2> nul
del *.in 2> nul
del *.aux 2> nul
del *.log 2> nul
del *.out 2> nul
del %tex_dir%\config.tex
del %tex_dir%\task_md.tex
del %tex_dir%\work_progress_md.tex
del %tex_dir%\listings.tex
pause