## 初始化

- 运行

```
> gcc -o main main.c Set.c
> main.exe
```

- heap的变化

```
          0         1         2         3        4        5        6        7        8        9
new             (s, 10)
new             (s, 10)   (a, 10)
add             (s, 10)   (a, 1)
new             (s, 10)   (a, 1)    (b, 10)
add             (s, 10)   (a, 1)    (b, 1)
new             (s, 10)   (a, 1)    (b, 1)   (c, 10)
add             (s, 10)   (a, 1)    (b, 1)   (c, 10)
drop            (s, 10)   (a, 10)   (b, 1)   (c, 10)
drop            (s, 10)   (a, 10)   (b, 10)  (c, 10)
delete          (s, 10)   (a, 10)            (c, 10)
drop            (s, 10)   (a, 10)            (c, 10)
delete          (s, 10)   (a, 10)
```

## main能否有两个set

## set能否包含set

## 限制

- object stores no information
- every object belongs to at most one set
- each set is small