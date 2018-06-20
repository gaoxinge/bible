def gen():
    var = 0
    while True:
        var += 1
        yield var
        
g = gen()

for _ in range(3):
    print next(g),