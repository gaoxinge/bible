########################
# f is not a generator #
# without yield        #
########################
# generator can has    #
# return when python > #
# 3.3                  #
########################

def f(x, y):
    yield x - y
    return x + y

gen = f(3, 1)

try:
    print(gen.send(None))
except StopIteration as e:
    print(e.value)

try:
    print(gen.send(None))
except StopIteration as e:
    print(e.value)