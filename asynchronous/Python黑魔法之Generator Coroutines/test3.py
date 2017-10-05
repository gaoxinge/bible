#######################
# send(None) is equal #
# to next()           #
#######################
# None is the only    #
# available value in  #
# the first send      #
# otherwise there     #
# will be a TypeError #
#######################

def f(x):
    y = yield x
    return x + y

gen = f(3)

try:
    print(gen.send(None))
except StopIteration as e:
    print(e.value)

try:
    print(gen.send(1))
except StopIteration as e:
    print(e.value)