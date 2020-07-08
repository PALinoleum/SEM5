#!/bin/bash
TEX_DIR="./tex_files"
TOOLS_DIR="./tools"

echo ----------------
echo Чтение conf.json
echo ----------------
if [ ! -f "config.tex" ] || [ "conf.json" -nt "config.tex" ] ; then
    python ${TOOLS_DIR}/build.py
fi
echo ----------------
echo Сборка листингов
echo ----------------
python ${TOOLS_DIR}/build_listings.py

echo -------------------
echo Компиляция Markdown
echo -------------------
pandoc -o ${TEX_DIR}/task_md.tex task.md
pandoc -o ${TEX_DIR}/work_progress_md.tex work_progress.md

echo ----------------
echo Компиляция LaTeX
echo ----------------
pdflatex --shell-escape ${TEX_DIR}/lab.tex | grep '^!.*' -A200 --color=always 
pdflatex --shell-escape ${TEX_DIR}/lab.tex | grep '^!.*' -A200 --color=always 

echo -------------------------
echo Удаление временных файлов
echo -------------------------
rm -rf _markdown_lab 2>/dev/null
rm -rf _minted-lab 2>/dev/null
rm -rf $TOOLS_DIR/__pycache__ 2>/dev/null
rm $TEX_DIR/*.aux 2>/dev/null
rm $TEX_DIR/*.lua 2>/dev/null
rm $TEX_DIR/*.in 2>/dev/null
rm $TEX_DIR/*.log 2>/dev/null
rm $TEX_DIR/*.out 2>/dev/null
rm *.in 2>/dev/null
rm *.aux 2>/dev/null
rm *.log 2>/dev/null
rm *.out 2>/dev/null

rm $TEX_DIR/config.tex
rm $TEX_DIR/task_md.tex
rm $TEX_DIR/work_progress_md.tex
rm $TEX_DIR/listings.tex
echo "Нажмите Enter для продолжения."; read