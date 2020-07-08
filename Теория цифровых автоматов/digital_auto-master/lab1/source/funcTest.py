from binVectors import gen_bin_vector_5 as gen_bin_vector
from tabulate import tabulate

def truth_table(vector,f,f_min):
    result = []
    for i in range(0,len(vector)):
        result.append([
            i+1,
            vector[i][0],
            int(f(vector[i][0])),
            int(f_min(vector[i][0]))
        ])
    return result


def sknf_function_min(str_val):
    x1 = bool(int(str_val[0]))
    x2 = bool(int(str_val[1]))
    x3 = bool(int(str_val[2]))
    x4 = bool(int(str_val[3]))
    x5 = bool(int(str_val[4]))

    z6 = (not x3) or (not x5)
    z2 = x1 or x2 
    z4 = x1 or x4
    z5 = (not x1) or (not x4)
    z3 = x1 or x5
    z1 = z6 or (not x1)

    #1-111
    u1 = z1 or (not x4)
    #111-1
    u2 = z1 or (not x2)
    #000--
    u3 = z2 or x3
    #00-0-
    u4 = z2 or x4
    #0-00-
    u5 = z4 or x3
    #11-1-
    u6 = z5 or (not x2)
    #00--0
    u7 = z3 or x2
    #0--00
    u8 = z3 or x4

    v1 = u1 and u2
    v2 = u3 and u4
    v3 = u5 and u6
    v4 = u7 and u8
    v5 = v1 and v2
    v6 = v3 and v4
    v7 = v5 and v6

    return v7

def sdnf_function_min(str_val):
    x1 = bool(int(str_val[0]))
    x2 = bool(int(str_val[1]))
    x3 = bool(int(str_val[2]))
    x4 = bool(int(str_val[3]))
    x5 = bool(int(str_val[4]))
    print(x1,x2,x3,x4,x5)
    z2 = x1 and (not x4) 
    z3 = x1 and (not x5)
    z4 = (not x1) and x2
    z5 = x1 and (not x2)
    z6 = (not x1) and x3
    z1 = z6 and x5

    #0-111
    u1 = z1 and x4
    #011-1
    u2 = z1 and x2
    #10-0-
    u3 = z2 and (not x2)
    #1-00-
    u4 = z2 and (not x3)
    #01-1-
    u5 = z4 and x4
    #100--
    u6 = z5 and (not x3)
    #10--0
    u7 = z3 and (not x2)
    #1--00
    u8 = z3 and (not x4)

    v1 = u1 or u2
    v2 = u3 or u4
    v3 = u5 or u6
    v4 = u7 or u8
    v5 = v1 or v2
    v6 = v3 or v4
    v7 = v5 or v6

    return v7

def function(str_val):
    x1 = str_val[0]
    x2 = str_val[1]
    x3 = str_val[2]
    x4 = str_val[3]
    x5 = str_val[4]
    return (
        3 < (int(str_val[3] + str_val[4],2) + int(str_val[0] + str_val[1] + str_val[2],2)) < 8 
    ) 

table_head = ["№","$x_1x_2x_3x_4x_5$","f","f_min"]
table = truth_table(gen_bin_vector(),function,sknf_function_min)
print(tabulate(table,table_head,tablefmt="simple"))

