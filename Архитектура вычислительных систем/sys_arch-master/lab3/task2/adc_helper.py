count_of_byte = 17
count_of_word = count_of_byte//4

for i in range(0,count_of_word):
    print('mov eax,dword ptr [a+%d]'%(i*4))
    print('adc eax,dword ptr [b+%d]'%(i*4))
    print('mov dword ptr [r+%d],eax\n'%(i*4))


