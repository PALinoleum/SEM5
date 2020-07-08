def f(x,y):
	if(x>10):
		result = abs(x)+y
	else:
		result = 1000/(x-y)
	return result

print(f(2,4))
