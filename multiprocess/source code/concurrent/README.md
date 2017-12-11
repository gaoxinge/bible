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

## reference

- [python concurrent.futures](https://www.cnblogs.com/kangoroo/p/7628092.html)