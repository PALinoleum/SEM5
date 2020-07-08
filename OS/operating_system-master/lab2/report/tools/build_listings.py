#!/usr/bin/env python
# -*- coding: utf-8 -*-
import os
import fnmatch
import lexer_list

def get_files(path = "."):
    return [f for f in os.listdir(path) if os.path.isfile(os.path.join(path, f))]

def guess_lang(file_name):
    for guess in lexer_list.lexer_list:
        if fnmatch.fnmatch(file_name, guess[0]):
            return guess[1]
    return None

def pick_sources():
    source_files = get_files("source")
    if not source_files:
        exit()
    with open("tex_files/listings.tex", "w", encoding='utf-8') as write_file:
        write_file.write(r"\section{Приложение}" + "\n")
        for f in source_files:
            write_file.write(r"\textbf{{Содержимое файла {}}}".format(f) + "\n")
            lang = guess_lang(f)
            if lang:
                write_file.write(r"\inputminted{{{}}}{{{}}}".format(lang, "source/" + f) + "\n")
            else:
                write_file.write(r"\inputminted{{}}{{{}}}".format(os.path.join("source/", f)) + "\n")

if __name__=="__main__":
    pick_sources()