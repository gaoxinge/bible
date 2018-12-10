# vim

## vi vs vim

- vim为vi的升级，vim兼容vi的所有命令
- `vi main.c`，`vim main.c`

## 模式

```
             i, o, a
normal mode --------> insert mode
                esc
normal mode <-------- insert mode
                 R
normal mode --------> replace mode
                esc
normal mode <-------- replace mode
                v
normal mode --------> visual mode
                V
normal mode --------> visual line mode
              <c-v>
normal mode --------> visual block mode 
```

## file

- ~/.viminfo: history
- ~/.vimrc: init