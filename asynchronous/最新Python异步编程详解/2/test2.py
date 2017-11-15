def inner_generator():
    i = 0
    while True:
        i = yield i
        if i > 10:
            break

def outer_generator():
    g = inner_generator()
    g.send(None)
    from_outer = 1
    while True:
        from_inner = g.send(from_outer)
        from_outer = yield from_inner

def main():
    g = outer_generator()
    g.send(None)
    i = 0
    while True:
        try:
            i = g.send(i+1)
            print(i)
        except StopIteration:
            break

if __name__ == '__main__':
    main()