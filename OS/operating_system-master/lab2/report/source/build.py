#!/usr/bin/env python
# -*- coding: utf-8 -*-

import json

def generate_tex():
    with open("conf.json", "r", encoding='utf-8') as read_file:
        conf = json.load(read_file)
    with open("config.tex", "w", encoding='utf-8') as write_file:
        for field in conf:
            write_file.write("\\newcommand{{\\{0}}}{{{1}}}\n".format(field, conf[field]))

if __name__=="__main__":
    generate_tex()