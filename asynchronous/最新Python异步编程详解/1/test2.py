def f():
    for _ in range(3):
        yield _

def g():
    for _ in f():
        yield _

def main():
    gen = g()
    while True:
        try:
            _ = gen.send(None)
            print(_)
        except StopIteration:
            break

if __name__ == '__main__':
    main()