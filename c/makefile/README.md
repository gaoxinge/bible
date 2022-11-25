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

## pwd

```makefile
exec:
    cd /home/hchen
    pwd
```

```
$ make
cd /home/hchen
pwd
/home
```

```makefile
exec:
    cd /home/hchen; pwd
```

```
$ make
cd /home/hchen
pwd
/home/hchen
```