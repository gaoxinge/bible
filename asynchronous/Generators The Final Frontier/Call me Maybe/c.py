from concurrent.futures import ThreadPoolExecutor


def func(x, y):
    import time
    time.sleep(5)
    return x + y


def result_handler(fut):
    try:
        result = fut.result()
        print('Got:', result)
    except Exception as e:
        print('Failed: %s: %s' % (type(e).__name__, e))

pool = ThreadPoolExecutor(max_workers=8)
fut = pool.submit(func, 2, 'Hello')
fut.add_done_callback(result_handler)
