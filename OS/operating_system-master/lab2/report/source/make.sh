#!/bin/bash
if [ ! -f "config.tex" ] || [ "conf.json" -nt "config.tex" ] ; then aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
if [ ! -f "config.tex" ] || [ "conf.json" -nt "config.tex" ] ; then aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    python build.py
fi
pdflatex --shell-escape lab.tex
rm -rf _markdown_lab
rm lab.markdown.in lab.markdown.lua lab.markdown.out lab.log lab.aux