from binVectors import gen_bin_vector_5 as gen_bin_vector
from tabulate import tabulate

def del_dup(list):
    res = [] 
    for i in list: 
        if i not in res: 
            res.append(i) 
    return res

def diff_pos(str_a,str_b):
    list_a=list(str_a)    
    list_b=list(str_b)
    i=0
    while(i<len(list_a)):
        if(list_a[i]!=list_b[i]):
            return i
        i = i + 1
        
def hamming_dist(s1, s2):
    assert len(s1) == len(s2)
    return sum(ch1 != ch2 for ch1, ch2 in zip(s1, s2)) 

def truth_table(vector,f,f1):
    result = []
    for i in range(0,len(vector)):
        if(f1(vector[i][0])):
            def_flag = False
        else:
            def_flag = True
        if def_flag:
            f_result = int(f(vector[i][0]))
        else:
            f_result = int(True)
        result.append([
            i+1,
            vector[i][0],
            f_result,
            def_flag
        ])
    return result

def sknf(table):
    result = []
    for i in table:
        if(not i[2]):
            result.append([
                [i[0]],
                i[1],
                "*"
            ])
    return result

def sdnf(table):
    result = []
    for i in table:
        if(i[2]):
            result.append([
                [i[0]],
                i[1],
                "*"
            ])
    return result

def to_next_imp(table):
    result = []
    flag = False
    for i in range(0,len(table)):
        for j in range(i,len(table)):
            if(hamming_dist(table[i][1],table[j][1]) == 1):
                flag = True
                table[j][2] = ""
                table[i][2] = ""
                pos = diff_pos(table[i][1],table[j][1])
                
                result_str = list(table[i][1])
                result_str[pos] = '-'
                result_index_list = table[i][0] + table[j][0]
                result_index_list.sort()
                
                result.append([
                    result_index_list,
                    "".join(result_str),
                    "*"
                ])
    if(flag):
        return [table,del_dup(result)]
    else:
        return None

def impl_combination(table):
    impl_list = []
    result = []
    steps = 0
    impl_list.append(table)
    while True:
        result = to_next_imp(impl_list[steps])
        if(result == None):
            break
        impl_list[steps] = result[0]
        impl_list.append(result[1])
        steps = steps + 1
    print("Склейка закончилась на импликантах "+str(steps)+" порядка.")
    return impl_list

def simple_impl(impl_list):
    result = []
    for i in impl_list:
        for j in i:
            if (j[2] == "*"):
                result.append(j)
    return result

def implicant_table(impl_list,table):
    #заполнение заголовка
    table_head = []
    for i in impl_list:
        table_head = table_head + i[0]
    table_head = del_dup(table_head)
    table_head.sort()
    table_head.insert(0,"Простая импликанта")
    #заполнение тела
    table_body = []
    for i in impl_list:
        table_str = []
        table_str.append(i[1])
        for j in range(1,len(table_head)):
            if table_head[j] in i[0]:
                table_str.append("*")
            else:
                table_str.append("")
        table_body.append(table_str)
    list_to_remove = []
    for index,i in enumerate(table,start=0):
        if(i[3]==False):
            list_to_remove.append(index+1)
    for i in list_to_remove:
        for index,j in enumerate(table_head,start=0):
            if(i==j):
                del table_head[index]
                for k in table_body:
                    del k[index]
    return (table_head,table_body)

def latex_sdnf_func(impl_list):
    result_str = ""
    for i in impl_list:
        result_str = result_str+"( "
        pos = 1
        for j in i[1]:
            if (j == '1'):
                result_str = result_str + 'x_' + str(pos)
            elif(j == '0'):
                result_str = result_str + r'\overline '+'x_'+str(pos)
            pos = pos + 1
        result_str = result_str + r" ) \lor "
    return result_str[0:-6]

def latex_sknf_func(impl_list):
    result_str = ""
    for i in impl_list:
        result_str = result_str+"( "
        pos = 1
        for j in i[1]:
            if (j == '1'):
                result_str = result_str + r'\overline '+'x_'+str(pos) + ' \lor '
            elif(j == '0'):
                result_str = result_str + 'x_' + str(pos) + ' \lor '
            result_str = result_str[0:-5]
            pos = pos + 1
        result_str = result_str + r" ) \land "
    return result_str[0:-7]

def factor_sdnf_table(simple_impl_list):
    table_head = ['']
    table_body = []
    for i in range(0,len(simple_impl_list[0][1])):
        table_head.append(r'$'+r'x'+str(i+1)+r'$')
        table_head.append(r'$'+r'\overline x'+str(i+1)+r'$')
    for i in simple_impl_list:
        temp_list = [i[1]]
        for j in i[1]:
            if (j =='0'):
                temp_list.append('')
                temp_list.append('*')
            elif (j =='1'):
                temp_list.append('*')
                temp_list.append('')
            else:
                temp_list.append('')
                temp_list.append('')
        table_body.append(temp_list)
    return (table_head,table_body)

def factor_sknf_table(simple_impl_list):
    table_head = ['']
    table_body = []
    for i in range(0,len(simple_impl_list[0][1])):
        table_head.append(r'$'+r'x'+str(i+1)+r'$')
        table_head.append(r'$'+r'\overline x'+str(i+1)+r'$')
    for i in simple_impl_list:
        temp_list = [i[1]]
        for j in i[1]:
            if (j =='0'):
                temp_list.append('*')
                temp_list.append('')
            elif (j =='1'):
                temp_list.append('')
                temp_list.append('*')
            else:
                temp_list.append('')
                temp_list.append('')
        table_body.append(temp_list)
    return (table_head,table_body)

def factorisation(table_tuple):
    table_head = table_tuple[0]
    table_body = table_tuple[1]
    #поиск строки с наибольшим вхождением
    def find_max_str(list):
        max_value = 0
        max_index = 0
        for index,i in enumerate(list,start=0):
            if(max_value<i.count('*')):
                max_index = index
                max_value = i.count('*')
        if max_value == 2:
            return None
        return max_index
    def max_sim(list,row):
        max_index = 0
        max_sim_count = 0
        for index,i in enumerate(list,start=0):
            if list[row] == i:
                continue
            else:
                sim_count = 0
                for j in range(1,len(i)):
                    if i[j]==list[row][j]:
                        sim_count = sim_count+1
                if(sim_count>max_sim_count):
                    max_sim_count = sim_count
                    max_index = index
        return max_index
    current_rows_count = len(table_body)
    current_columns_count = len(table_body[0])

    max_str_index = find_max_str(table_body) 
    max_sim_index = max_sim(table_body,max_str_index)
    for step in range(1,10):
        new_list = ['z'+str(step)]
        table_head.append('u'+str(step))
        #заполнение новой строки
        for j in range(1,len(table_body[max_str_index])):
            if (table_body[max_str_index][j] == '*') and (table_body[max_sim_index][j] == '*'):
                table_body[max_str_index][j] = ''
                table_body[max_sim_index][j] = ''
                new_list.append('*')
            else:
                new_list.append('')
        table_body.append(new_list)
        #заполнение нового столбца
        for index,i in enumerate(table_body,start=0):
            if index == max_str_index:
                table_body[index].append('*')
            elif index == max_sim_index:
                table_body[index].append('*')
            else:
                table_body[index].append('')
    return (table_head,table_body)

def function(str_val):
    x1 = str_val[0]
    x2 = str_val[1]
    x3 = str_val[2]
    x4 = str_val[3]
    x5 = str_val[4]
    return (
        #(3 < (int(x1+x2+x3,2)+int(x4+x5,2)) < 8) and (4<=(int(x1+x2+x3,2)+int(x4+x5,2))<=6)
        #(2 <= abs((int(x1+x2,2)-int(x3+x4+x5,2))) <= 4) and (4<=(int(x1+x2+x3,2)+int(x4+x5,2))<=6)
        3 < (int(str_val[3] + str_val[4],2) + int(str_val[0] + str_val[1] + str_val[2],2)) < 8 
    ) 

def def_func(str_val):
    x1 = str_val[0]
    x2 = str_val[1]
    x3 = str_val[2]
    x4 = str_val[3]
    x5 = str_val[4]
    return (
        int(x1+x2+x3) == 1 
    ) 

table_head = ["№","$x_1x_2x_3x_4x_5$","f","def_func"]
table = truth_table(gen_bin_vector(),function,def_func)
print(tabulate(table,table_head,tablefmt="simple"))

sknf_table = sknf(table)
sdnf_table = sdnf(table)

impl_list = impl_combination(sknf_table)
impl_list_head = ["№","$x_1x_2x_3x_4x_5$","Простая импликанта?"]
for i in impl_list:
    print(tabulate(i,impl_list_head,tablefmt="simple"))

simple_impl_list = simple_impl(impl_list)
print('Список простых импликант')
print(tabulate(simple_impl_list,impl_list_head,tablefmt="simple"))

print('\nТаблица простых импликант')
impl_table = implicant_table(simple_impl_list,table)
print(tabulate(impl_table[1],impl_table[0],tablefmt="latex"))

print(latex_sknf_func(simple_impl_list))
result = factor_sknf_table(simple_impl_list)
print(tabulate(result[1],result[0],tablefmt="fancy_grid"))
