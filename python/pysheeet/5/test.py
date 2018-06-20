def func_1():
    print("Hello")
    
def func_2():
    print("World")
    
def func_3():
    print("!!!")
    
s = [func_1, func_2, func_3]
for _ in s: _()