# makefile

## echo

```makefile
OBJ = a.o b.o c.o

exec:
    echo $(OBJ)
```

```
$ make
echo a.o b.o c.o
a.o b.o c.o
```

```
$ make -n
echo a.o b.o c.o
```

```
$ make -s
a.o b.o c.o
```