## usage

### basic

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i
            
numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    # no concurrent
    results = list(map(gcd, numbers))
    print results

    # multithread
    with ThreadPoolExecutor(max_workers=2) as pool:
        results = list(pool.map(gcd, numbers))
    print results
    
    # multiprocess
    with ProcessPoolExecutor(max_workers=2) as pool:
        results = list(pool.map(gcd, numbers))
    print results
```

### executor

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i

numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    results = []
    with ProcessPoolExecutor(max_workers=2) as pool:
        for pair in numbers:
            future = pool.submit(gcd, pair)
            results.append(future.result())
    print results
```

### future

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, as_completed, \
    wait, ALL_COMPLETED, FIRST_COMPLETED, FIRST_EXCEPTION

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i

numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    with ProcessPoolExecutor(max_workers=2) as pool:
        futures = [pool.submit(gcd, pair) for pair in numbers]
        for future in futures:
            print '%s, %s' % (future.running(), future.done())
        for future in as_completed(futures, timeout=0.0001):
            print '%s, %s' % (future.running(), future.done())
```

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, as_completed, \
    wait, ALL_COMPLETED, FIRST_COMPLETED, FIRST_EXCEPTION

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i

numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    with ProcessPoolExecutor(max_workers=2) as pool:
        futures = [pool.submit(gcd, pair) for pair in numbers]
        for future in futures:
            print '%s, %s' % (future.running(), future.done())
        for future in as_completed(futures, timeout=1):
            print '%s, %s' % (future.running(), future.done())
```

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, as_completed, \
    wait, ALL_COMPLETED, FIRST_COMPLETED, FIRST_EXCEPTION

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i

numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    with ProcessPoolExecutor(max_workers=2) as pool:
        futures = [pool.submit(gcd, pair) for pair in numbers]
        for future in futures:
            print '%s, %s' % (future.running(), future.done())
        print '###############################################'
        done, unfinished = wait(futures, timeout=2, return_when=ALL_COMPLETED)
        for d in done:
            print '%s, %s' % (d.running(), d.done())
        for u in unfinished:
            print '%s, %s' % (u.running(), u.done())
```

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, as_completed, \
    wait, ALL_COMPLETED, FIRST_COMPLETED, FIRST_EXCEPTION

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i

numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    with ProcessPoolExecutor(max_workers=2) as pool:
        futures = [pool.submit(gcd, pair) for pair in numbers]
        for future in futures:
            print '%s, %s' % (future.running(), future.done())
        print '###############################################'
        done, unfinished = wait(futures, timeout=2, return_when=FIRST_COMPLETED)
        for d in done:
            print '%s, %s' % (d.running(), d.done())
        for u in unfinished:
            print '%s, %s' % (u.running(), u.done())
```

## prepare

### weakref

- [Python弱引用学习](http://python.jobbole.com/85431/)

### atexit

- [Python模块学习：atexit](http://python.jobbole.com/81473/)

### sys

### thread

## reference

- [Compulsory usage of if __name__==“__main__” in windows while using multiprocessing](https://stackoverflow.com/questions/20360686/compulsory-usage-of-if-name-main-in-windows-while-using-multiprocessi)
- [python concurrent.futures](https://www.cnblogs.com/kangoroo/p/7628092.html)
- [使用python的并发库concurrent.futures实现异步](http://xiaorui.cc/2014/11/15/%E4%BD%BF%E7%94%A8python%E7%9A%84%E4%B8%8A%E5%B1%82%E5%B0%81%E8%A3%85%E5%B9%B6%E5%8F%91%E5%BA%93concurrent-futures%E5%AE%9E%E7%8E%B0%E5%BC%82%E6%AD%A5/)
- [python并发库：concurrent.futures的使用](http://blog.csdn.net/drdairen/article/details/69487643)
- [python并发之concurrent.futures](http://blog.csdn.net/dutsoft/article/details/54728706)
- [concurrent.futures — Asynchronous computation](http://pythonhosted.org//futures/)
- [concurrent.futures — Launching parallel tasks](https://docs.python.org/3/library/concurrent.futures.html)