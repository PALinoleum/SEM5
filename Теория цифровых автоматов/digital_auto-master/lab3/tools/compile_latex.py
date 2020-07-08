import os,json,re

cfg_file = open("conf.json", "r", encoding='utf-8')
cfg = json.load(cfg_file)
filename = cfg['AuthorFIO']+' '+'Лабораторная работа №'+str(cfg['LabNum'])+' '+cfg['Subject']+'.pdf';
tex_dir ="./tex_files"
os.system(r'pdflatex --shell-escape --halt-on-error ./tex_files/lab.tex')
os.system(r'pdflatex --shell-escape --halt-on-error ./tex_files/lab.tex')
os.remove("./"+filename)
os.rename("./lab.pdf","./"+filename)
