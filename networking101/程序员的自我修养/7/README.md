## 第7章 动态链接

### 7.3 地址无关代码

#### 命令

- `-shared`：共享对象
- `-fpic`，`-fPIC`：position independent code
- `-fpie`，`-fPIE`：position independent executable

#### 指令

- [指令存储在外存中还是内存？](https://www.zhihu.com/question/57522333)
- [程序的机器级表示<CSAPP>](https://blog.csdn.net/qq_20183489/article/details/53856926)
- [csapp chapter3:程序的机器级表示](http://ju.outofmemory.cn/entry/107328)

##### 观察1

|类型|格式|地址|值|
|----|----|----|--|
|立即数|$Imm|-|Imm|
|存储器|Imm|M[Imm]|V(M[Imm])|
|寄存器|E_e|E_e|V(E_e)|
|存储器|(E_e)|M[V(E_e)]|V(M[V(E_e)])|

|指令|S|D|
|----|-|-|
|mov|值|地址|
|add|值|地址|