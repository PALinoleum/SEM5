import random
import math 

result_arr = []
for i in range(0,10):
    power = random.randint(1,10) 
    num = random.triangular(1,20) 
    data = (power,num,math.pow(num,power))
    result_arr.append(data)

for i in result_arr:
    print(i)