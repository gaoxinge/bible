def inner_generator():
    i = 0
    while True:
        i = yield i
        if i > 10:
            raise StopIteration


def outer_generator():
    print("do something before yield")
    yield from inner_generator()


def main():
    g = outer_generator()
    g.send(None)
    i = 0
    while 1:
        try:
            i = g.send(i + 1)
            print(i)
        except StopIteration:
            break

if __name__ == '__main__':
    main()
