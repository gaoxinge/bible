def f():
    for _ in range(3):
        yield _

def g():
    gen = f()
    from_outer = None
    while True:
        from_inner = gen.send(from_outer)
        from_outer = yield from_inner

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