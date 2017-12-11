## basic

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

## executor

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

## reference

- [Compulsory usage of if __name__==“__main__” in windows while using multiprocessing](https://stackoverflow.com/questions/20360686/compulsory-usage-of-if-name-main-in-windows-while-using-multiprocessi)
- [python concurrent.futures](https://www.cnblogs.com/kangoroo/p/7628092.html)