import os

def spam(a, b):
    try:
        os.listdir('.')
    except OSError:
        print("listdir get error")
        return
    
    try:
        a / b
    except ZeroDivisionError:
        print("zero division")
        return