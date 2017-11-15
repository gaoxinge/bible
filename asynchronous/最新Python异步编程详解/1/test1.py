def f():
    for _ in range(3):
        yield _

def g():
    yield from f()

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