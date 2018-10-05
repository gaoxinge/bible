## symmetric, asymmetric

- symmetric：协程可以把控制转移给任意其他协程
- asymmetric：被调用者协程只可以把控制转移给调用者协程

## stackfull, stackless

- stackfull：栈式协程可以在嵌套调用中挂起并恢复
- stackless：非栈式协程只可以在同级调用中挂起并恢复