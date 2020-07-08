import os,glob,re

tex_dir ="./tex_files"
md_list = glob.glob(tex_dir+'/*.md')
for md_filename in md_list:
    tex_filename = md_filename
    tex_filename= re.sub('.md','.tex',tex_filename)
    print(tex_filename)
    os.system(r'pandoc -o '+tex_filename+' '+md_filename)
    os.remove(md_filename)
