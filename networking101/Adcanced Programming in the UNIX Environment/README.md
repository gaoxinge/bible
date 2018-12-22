```
# cd lib
# gcc -c *.c -I ../include
# ar rsc apue.a *.o
```

```
# gcc -o main -I include prog/chapter1/prog1.c lib/apue.a
```