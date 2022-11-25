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
    END_TRY;
}
```

```c
void f() {
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
    } while (0);
}
```

## 疑问

### 模型

```
f1 ------> f2 ------> f3 ------> f4
        TRY-EXCEPT <----------- RAISE
```

```
f1 --------------> f2 ------> f3 ------> f4
TRY-EXCEPT <--- TRY-EXCEPT-RERAISE <--- RAISE
```

### volatile和多线程

假设volatile是用于多线程，Except_stack是线程共享的。由于线程的并发性，无法控制Except_stack的push是有序的。个人认为Except_stack无法做到线程安全，同时volatile是无用的，应该把Except_stack做成TLS比较合适。

### Except_Frame和Except_stack

Excetp_Frame是局部的，Except_stack是全局的。如何协调矛盾？关键在于一定要保证Except_Frame的push在对应的栈建立之后，Except_Frame的pop在对应的栈销毁之前。即Except_Frame和对应的栈存活周期一致。

### Except_raise

`p == NULL`的判断是为了保证对应的Except_Frame已经初始化过了，即必须保持和模型一致。

### RAISE

- 对最近的Except_Frame设置e，file，line
- 从Except_stack中pop出最近的Except_Frame
- 使用longjmp设置最近的Except_Frame的env的值为Except_raised

### RERAISE

- 对最近的Except_Frame设置当前Except_Frame的e，当前Excpet_Frame的file，当前Except_Frame的line
- 从Except_stack中pop出最近的Except_Frame
- 使用longjmp设置最近的Except_Frame的env的值为Except_raised

### if的`if (Except_flag == Except_entered) Except_stack = Except_stack->prev;`

- 只需要`Except_stack = Except_stack->prev;`就行了

### else if的`if (Except_flag == Except_entered) Except_stack = Except_stack->prev;`

- 可以移除

### else的`if (Except_flag == Except_entered) Except_stack = Except_stack->prev;`

- 可以移除

### 最后的`if (Except_flag == Except_entered) Except_flag = Except_finalized;`

- 如果`Except_flag == Except_entered`，那么`Except_flag = Except_finalized`
- 如果`Except_flag == Except_raised`，那么`Except_flag = Except_raised`：最后的最后会RERAISE
- 如果`Except_flag == Except_handled`，那么`Except_flag = Except_handled`

### 最后的`if (Except_flag == Except_entered) Except_stack = Except_stack->prev;`

- 可以移除

### 最后

- 并不能解决多个RAISE和RERAISE的情形

## 其他

- [Simple try: exp except: exp finally: in C](https://www.pythonsheets.com/notes/python-cstyle.html#simple-try-exp-except-exp-finally-in-c): 里面的switch相当于if-else, 还是使用了setjmp.h
- [Coroutines in C](https://www.chiark.greenend.org.uk/~sgtatham/coroutines.html): 使用switch+static或者switch+ctx的方式构造协程，但是需要多次调用同一个函数，所以无法仅使用switch实现try-except