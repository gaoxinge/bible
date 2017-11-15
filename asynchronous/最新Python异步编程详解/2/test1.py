def inner_generator():
    i = 0
    while True:
        i = yield i
        if i > 10:
            break

def outer_generator():
    yield from inner_generator()

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