#!/usr/bin/env python
# -*- coding: utf-8 -*-

import json
import sys 

def generate_tex():
    cfg_file = open("conf.json", "r", encoding='utf-8')
    cfg = json.load(cfg_file)
    cfg_file.close()
    
    macro_file = open("tex_files/config.tex", "w", encoding='utf-8')
    
    if(cfg.get('LabNum') != None):
        macro_file.write('\\newcommand{\\LabNum}{№'+str(cfg['LabNum'])+'}\n')        
    else: 
        macro_file.write('\\newcommand{\\LabNum}{}\n')

    if(cfg.get('Subject') != None):
        macro_file.write('\\newcommand{\\Subject}{'+cfg['Subject']+'}\n')        
        macro_file.write('\\newcommand{\\SubjectLineTitle}{дисциплина <<\\Subject>>\\\\}\n')        
    else: 
        macro_file.write('\\newcommand{\\Subject}{}\n')
        macro_file.write('\\newcommand{\\SubjectLineTitle}{}\n')

    if(cfg.get('Theme') != None):
        macro_file.write('\\newcommand{\\Theme}{'+cfg['Theme']+'}\n')        
        macro_file.write('\\newcommand{\\ThemeLineTitle}{по теме <<\\Theme>>\\\\}\n')        
        macro_file.write('\\newcommand{\\ThemeLineHead}{\\textbf{<<\\Theme>>}}\n')        
    else: 
        macro_file.write('\\newcommand{\\Theme}{}\n')
        macro_file.write('\\newcommand{\\ThemeLineTitle}{}\n')
        macro_file.write('\\newcommand{\\ThemeLineHead}{}\n')

    if(cfg.get('Variant') != None):
        macro_file.write('\\newcommand{\\Variant}{'+str(cfg['Variant'])+'}\n')        
        macro_file.write('\\newcommand{\\VariantLine}{\\textbf{Вариант \\Variant}}\n')        
    else: 
        macro_file.write('\\newcommand{\\Variant}{}\n')
        macro_file.write('\\newcommand{\\VariantLine}{}\n')

    if(cfg.get('Task') != None):
        macro_file.write('\\newcommand{\\Task}{'+cfg['Task']+'}\n')        
        macro_file.write('\\newcommand{\\TaskLineHead}{\\textbf{Цель работы:}\\Task.}\n')        
    else: 
        macro_file.write('\\newcommand{\\Task}{}\n')
        macro_file.write('\\newcommand{\\TaskLineHead}{}\n')

    if(cfg.get('Group') != None):
        macro_file.write('\\newcommand{\\Group}{'+cfg['Group']+'}\n')        
    else: 
        macro_file.write('\\newcommand{\\Group}{}\n')
        print('ОШИБКА!!! В conf.json отсутствует или неправильно обозначено поле Group.')

    if(cfg.get('AuthorFIO') != None):
        macro_file.write('\\newcommand{\\AuthorFIO}{'+cfg['AuthorFIO']+'}\n')        
    else: 
        macro_file.write('\\newcommand{\\AuthorFIO}{}\n')
        print('ОШИБКА!!! В conf.json отсутствует или неправильно обозначено поле AuthorFIO.')

    if(cfg.get('LecturerFIO') != None):
        macro_file.write('\\newcommand{\\LecturerFIO}{'+cfg['LecturerFIO']+'}\n')        
    else: 
        macro_file.write('\\newcommand{\\LecturerFIO}{}\n')
        print('ОШИБКА!!! В conf.json отсутствует или неправильно обозначено поле LecturerFIO.')

    if(cfg.get('Year') != None):
        macro_file.write('\\newcommand{\\Year}{'+str(cfg['Year'])+'}\n')        
    else: 
        macro_file.write('\\newcommand{\\Year}{}\n')
        print('ОШИБКА!!! В conf.json отсутствует или неправильно обозначено поле Year.')

    macro_file.write('\\newcommand{\\LabLineTitle}{Лабораторная работа \\LabNum \\\\}\n')
    macro_file.write('\\newcommand{\\LabLineHead}{\\section{Лабораторная работа \\LabNum }}\n')
    macro_file.close()
    
if __name__=="__main__":
    generate_tex()