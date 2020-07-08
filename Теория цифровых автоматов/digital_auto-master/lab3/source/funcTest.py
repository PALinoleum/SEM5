from binVectors import gen_bin_vector_5 as gen_bin_vector
from tabulate import tabulate

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
            def_flag,
            f_result,
            int(sdnf_function_min(vector[i][0])),
            int(sknf_function_min(vector[i][0]))
        ])
    return result

def sdnf_function_min(str_val):
    x1 = bool(int(str_val[0]))
    x2 = bool(int(str_val[1]))
    x3 = bool(int(str_val[2]))
    x4 = bool(int(str_val[3]))
    x5 = bool(int(str_val[4]))
    print(x1,x2,x3,x4,x5)
    z1 = x1 and (not x2)
    z2 = x1 and (not x5) 
    z3 = (not x1) and x3
    z4 = x2 and x4
    z5 = (not x3) and (not x4)

    u1 = z3 and x5
    u2 = z4 and (not x1)
    u7 = z2 and (not x4)
    u4 = z1 and (not x4)
    u5 = z5 and x1
    u6 = z2 and (not x2)
    u3 = z1 and (not x3)

    v1 = u1 or u2
    v2 = u3 or u4
    v3 = u5 or u6
    v4 = v1 or u7
    v5 = v2 or v3
    f = v4 or v5

    return f

def sknf_function_min(str_val):
    x1 = bool(int(str_val[0]))
    x2 = bool(int(str_val[1]))
    x3 = bool(int(str_val[2]))
    x4 = bool(int(str_val[3]))
    x5 = bool(int(str_val[4]))

    z5 = (not x1) or (not x3)
    z1 = z5 or (not x5)
    z2 = x1 or x3 
    z3 = x1 or (not x2)
    z6 = x4 or x5
    z4 = (not x1) or (not x2)

    u1 = z1 or (not x4)
    u2 = z1 or (not x2)
    u3 = z2 or x2
    u4 = z2 or x4
    u5 = z3 or z6
    u6 = z4 or (not x4)

    v1 = u1 and u2
    v2 = u3 and u4
    v3 = u5 and u6
    v4 = v1 and v2
    v5 = v4 and v3

    return v5


def function(str_val):
    x1 = str_val[0]
    x2 = str_val[1]
    x3 = str_val[2]
    x4 = str_val[3]
    x5 = str_val[4]
    return (
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

table_head = ["№","$x_1x_2x_3x_4x_5$","f определена?","f","ДНФ","КНФ"]
table = truth_table(gen_bin_vector(),function,def_func)
print(tabulate(table,table_head,tablefmt="simple"))

