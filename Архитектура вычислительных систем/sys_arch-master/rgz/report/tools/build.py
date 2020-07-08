#!/usr/bin/env python
# -*- coding: utf-8 -*-

import json
import sys 
import re

def generate_config():
    cfg_file = open("conf.json", "r", encoding='utf-8')
    cfg = json.load(cfg_file)
    cfg_file.close()
    
    macro_file = open("tex_files/config.tex", "w", encoding='utf-8')
    
    if(cfg.get('PicScale') != None):
        macro_file.write('\\newcommand{\\PicScale}{'+str(cfg['PicScale'])+'}\n')        
    else: 
        macro_file.write('\\newcommand{\\PicScale}{0.5}\n')

    if(cfg.get('LabNum') != None):
        macro_file.write('\\newcommand{\\LabNum}{№'+str(cfg['LabNum'])+'}\n')        
    else: 
        macro_file.write('\\newcommand{\\LabNum}{}\n')

    if(cfg.get('Subject') != None):
        macro_file.write('\\newcommand{\\Subject}{'+cfg['Subject']+'}\n')        
        macro_file.write('\\newcommand{\\SubjectLineTitle}{по дисциплине <<\\Subject>>\\\\}\n')        
    else: 
        macro_file.write('\\newcommand{\\Subject}{}\n')
        macro_file.write('\\newcommand{\\SubjectLineTitle}{}\n')

    if(cfg.get('Theme') != None):
        macro_file.write('\\newcommand{\\Theme}{'+cfg['Theme']+'}\n')        
        macro_file.write('\\newcommand{\\ThemeLineTitle}{\n<<\\Theme>>\\\\}\n')        
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

    macro_file.write('\\newcommand{\\LabLineTitle}{\\\\}\n')
    macro_file.write('\\newcommand{\\LabLineHead}{\\section{Расчетно-графическое задание}}\n')
    macro_file.close()

def generate_body():
    body_tex = open("tex_files/body.tex", "w", encoding='utf-8')
    
    latex_tag_rule = r'(@latex[\s\d\S]*?@\/latex)'
    latex_start_tag_rule = r'@latex'
    latex_end_tag_rule = r'@/latex'
    
    current_part_task = 1
    current_part_work = 1

    with open("task.md", "r", encoding='utf-8') as task_md_file:
        task_md_str = task_md_file.read()
    task_body_parts = re.split(latex_tag_rule,task_md_str)
    
    for part in task_body_parts:
        if part.find(latex_start_tag_rule) !=-1:
            part = re.sub(latex_start_tag_rule,' ',part)
            if part.find(latex_end_tag_rule) !=-1:
                part = re.sub(latex_end_tag_rule,' ',part)                
                part_name = 'tex_files/task_part'+str(current_part_task)
                if(len(part) != 0):
                    with open(part_name+'.tex','w',encoding='utf-8') as part_file:
                        part_file.write(part)
                    body_tex.write('\\input{'+part_name+'}\n')
                    current_part_task = current_part_task+1
            else:
                print('Синтаксическая ошибка. Проверьте теги @latex.')
        else:
            part_name = 'tex_files/task_part'+str(current_part_task)
            if(len(part) != 0):
                with open(part_name+'.md','w',encoding='utf-8') as part_file:
                    part_file.write(part)
                body_tex.write('\\input{'+part_name+'}\n')
                current_part_task = current_part_task+1

    with open("work_progress.md", "r", encoding='utf-8') as work_md_file:
        work_md_str = work_md_file.read()
    work_body_parts = re.split(latex_tag_rule,work_md_str)
    

    for part in work_body_parts:
        if part.find(r'@latex') !=-1:
            part = re.sub(latex_start_tag_rule,' ',part)
            if part.find(r'@/latex') !=-1:
                part = re.sub(latex_end_tag_rule,' ',part)                
                part_name = 'tex_files/work_part'+str(current_part_work)
                if(len(part) != 0):
                    with open(part_name+'.tex','w',encoding='utf-8') as part_file:
                        part_file.write(part)
                    body_tex.write('\\input{'+part_name+'}\n')
                    current_part_work = current_part_work+1
            else:
                print('Синтаксическая ошибка. Проверьте теги @latex.')
        else:
            part_name = 'tex_files/work_part'+str(current_part_work)
            if(len(part) != 0):
                with open(part_name+'.md','w',encoding='utf-8') as part_file:
                    part_file.write(part)
                body_tex.write('\\input{'+part_name+'}\n')
                current_part_work = current_part_work+1
    body_tex.close()
    

if __name__=="__main__":
    generate_body()
    generate_config()
