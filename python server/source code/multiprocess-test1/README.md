## test.py

- [Installing Python 3 on Linux](http://docs.python-guide.org/en/latest/starting/install3/linux/)
- [How do I install Python 3.6 using apt-get?](https://askubuntu.com/questions/865554/how-do-i-install-python-3-6-using-apt-get)

```
$ python3.6 test.py --mac-client=5000
```

## 结果

- part3_1_test.py
  - 出现僵尸进程
  - 个数不满5000
  - fork出错
- part3_2_test.py比cpython_test.py略快
  - cpython_test.py控制了子进程的个数
  - 没有在子进程中关闭父进程的socket副本