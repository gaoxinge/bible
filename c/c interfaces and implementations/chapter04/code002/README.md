## 对比

```c
void f() {
    TRY
        S
    EXCEPT(e1)
        S1
    EXCEPT(e2)
        S2
    ELSE
        S0
    FINALLY
        S'
    END_TRY
}
```

```c
void g() {
    do {
        volatile int Except_flag;
        Except_Frame Except_frame;
        Except_frame.prev = Except_stask;
        Except_stack = &Except_frame;
        Except_flag = setjmp(Except_frame.env);
        if (Except_flag == Except_entered) {
            S
            if (Except_flag == Except_entered)
                Except_stack = Excpet_stack->prev;
        } else if (Except_frame.excpetion == &(e1)) {
            Except_flag = Except_handled;
            S1
            if (Except_flag == Except_entered)
                Except_stack = Except_stack->prev;
        } else if (Except_frame.excpetion == &(e2)) {
            Except_flag = Except_handled;
            S2
            if (Except_flag == Except_entered)
                Except_stack = Except_stack->prev;
        } else {
            Except_flag = Except_handled;
            S0
            if (Except_flag == Except_entered)
                Except_stack = Except_stack->prev;
        } {
            if (Except_flag == Except_entered)
                Except_flag = Except_finalized;
            S'
            if (Except_flag == Except_entered)
                Except_stack = Except_stack->prev;
        }
        if (Excpet_flag == Except_raised)
            Except_raise(Except_frame.exception, Except_frame.file, Except_frame.line);
    } while (0)
}
```

## 其他

- [Simple try: exp except: exp finally: in C](https://www.pythonsheets.com/notes/python-cstyle.html#simple-try-exp-except-exp-finally-in-c): 里面的switch相当于if-else, 还是使用了setjmp.h
- [Coroutines in C](https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html): 使用switch+static或者switch+ctx的方式构造协程，但是需要多次调用同一个函数，所以无法仅使用switch实现try-except