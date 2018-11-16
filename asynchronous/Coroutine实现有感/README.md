## symmetric, asymmetric

- symmetric：协程可以把控制转移给任意其他协程
- asymmetric：被调用者协程只可以把控制转移给调用者协程

## stackfull, stackless

- stackfull：栈式协程可以在嵌套调用中挂起并恢复
- stackless：非栈式协程只可以在同级调用中挂起并恢复
- stackfull：it means that the coroutines hanve own stack, so they map on native thread
- stackless：it means that the coroutines don't have own stack, so they don't map on native thread

## other

- c
- python：非对称，非栈式（asyncio，curio）
- greenlet：对称，非栈式（evenlet，gevent）
- java
- go
- lua：非对称，非栈式
- c#：非对称，非栈式

## python

- lua|yield + callback
- lua|yield + no callback
- c#|async/await + callback
- c#|async/await + no callback

## callback

- reactor + future + yield/async/await
- asyncio/tornado/twisted
- asyncio
  - AbstractEventLoop (events.py) 
    - BaseEventLoop (base_events.py)
      - BaseSelectorEventLoop (selector_events.py)
        - UnixSelectorEventLoop (unix_events.py)
        - WindowsSelectorEventLoop (windows_events.py)
      - BaseProactorEvetnLoop (proactor_events.py)
        - ProactorEventLoop (windows_events.py)
  - AbstractEventLoopPolicy (events.py)
    - BaseDefaultEventLoopPolicy (events.py)
      - DefaultEventLoopPolicy (unix_events.py)
      - DefaultEventLoopPolicy (winddows_events.py)
  - uvloop
  
## no callbcak

- round-robin schedule + yield