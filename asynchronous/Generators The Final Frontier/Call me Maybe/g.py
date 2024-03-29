from concurrent.futures import ThreadPoolExecutor


def func(x, y):
    import time
    time.sleep(1)
    return x + y


def do_many(n):

    def callback(fut):
        nonlocal n
        result = fut.result()
        print('Got: ', result)
        n -= 1
        if n > 0:
            future = pool.submit(func, n, n)
            future.add_done_callback(callback)

    if n > 0:
        future = pool.submit(func, n, n)
        future.add_done_callback(callback)

pool = ThreadPoolExecutor(max_workers=8)
do_many(10)
