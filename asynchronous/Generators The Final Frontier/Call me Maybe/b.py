from concurrent.futures import ThreadPoolExecutor


def func(x, y):
    import time
    time.sleep(5)
    return x + y


def result_handler(fut):
    result = fut.result()
    print('Got:', result)


pool = ThreadPoolExecutor(max_workers=8)
fut = pool.submit(func, 2, 3)
fut.add_done_callback(result_handler)
