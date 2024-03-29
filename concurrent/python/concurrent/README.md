## usage

### basic

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i
            
numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    # no concurrent
    results = list(map(gcd, numbers))
    print results

    # multithread
    with ThreadPoolExecutor(max_workers=2) as pool:
        results = list(pool.map(gcd, numbers))
    print results
    
    # multiprocess
    with ProcessPoolExecutor(max_workers=2) as pool:
        results = list(pool.map(gcd, numbers))
    print results
```

### executor

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i

numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    results = []
    with ProcessPoolExecutor(max_workers=2) as pool:
        for pair in numbers:
            future = pool.submit(gcd, pair)
            results.append(future.result())
    print results
```

### future

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, as_completed, \
    wait, ALL_COMPLETED, FIRST_COMPLETED, FIRST_EXCEPTION

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i

numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    with ProcessPoolExecutor(max_workers=2) as pool:
        futures = [pool.submit(gcd, pair) for pair in numbers]
        for future in futures:
            print '%s, %s' % (future.running(), future.done())
        for future in as_completed(futures, timeout=0.0001):
            print '%s, %s' % (future.running(), future.done())
```

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, as_completed, \
    wait, ALL_COMPLETED, FIRST_COMPLETED, FIRST_EXCEPTION

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i

numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    with ProcessPoolExecutor(max_workers=2) as pool:
        futures = [pool.submit(gcd, pair) for pair in numbers]
        for future in futures:
            print '%s, %s' % (future.running(), future.done())
        for future in as_completed(futures, timeout=1):
            print '%s, %s' % (future.running(), future.done())
```

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, as_completed, \
    wait, ALL_COMPLETED, FIRST_COMPLETED, FIRST_EXCEPTION

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i

numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    with ProcessPoolExecutor(max_workers=2) as pool:
        futures = [pool.submit(gcd, pair) for pair in numbers]
        for future in futures:
            print '%s, %s' % (future.running(), future.done())
        print '###############################################'
        done, unfinished = wait(futures, timeout=2, return_when=ALL_COMPLETED)
        for d in done:
            print '%s, %s' % (d.running(), d.done())
        for u in unfinished:
            print '%s, %s' % (u.running(), u.done())
```

```python
from concurrent.futures import ThreadPoolExecutor, ProcessPoolExecutor, as_completed, \
    wait, ALL_COMPLETED, FIRST_COMPLETED, FIRST_EXCEPTION

def gcd(pair):
    a, b = pair
    low = min(a, b)
    for i in range(low, 0, -1):
        if a % i == 0 and b % i == 0:
            return i

numbers = [
    (1963309, 2265973), (1879675, 2493670), (2030677, 3814172),
    (1551645, 2229620), (1988912, 4736670), (2198964, 7876293)
]

if __name__ == '__main__':
    with ProcessPoolExecutor(max_workers=2) as pool:
        futures = [pool.submit(gcd, pair) for pair in numbers]
        for future in futures:
            print '%s, %s' % (future.running(), future.done())
        print '###############################################'
        done, unfinished = wait(futures, timeout=2, return_when=FIRST_COMPLETED)
        for d in done:
            print '%s, %s' % (d.running(), d.done())
        for u in unfinished:
            print '%s, %s' % (u.running(), u.done())
```

## prepare

### weakref

- [Python弱引用学习](http://python.jobbole.com/85431/)

```python
import sys
import gc
import weakref
gc.set_debug(gc.DEBUG_LEAK)

def f(_):
    print 'dead'

class Man(object):

    def __init__(self, name):
        self.name = name

    def f(self):
        print self.name

o = Man('Jim')
print sys.getrefcount(o)

r = weakref.ref(o, f)
print sys.getrefcount(o)

o2 = r()
print sys.getrefcount(o)

del o
del o2
gc.collect()
print 1
```

```python
import sys
import gc
import weakref
gc.set_debug(gc.DEBUG_LEAK)

def f(_):
    print 'dead'

class Man(object):

    def __init__(self, name):
        self.name = name

    def f(self):
        print self.name

o = Man('Jim')
print sys.getrefcount(o)

r = weakref.ref(o, f)
print sys.getrefcount(o)

del o
gc.collect()
o2 = r()
print o2
```

```python
import weakref
import gc
import sys
gc.set_debug(gc.DEBUG_LEAK)

class Man(object):

    def __init__(self, name):
        self.name = name

    def __repr__(self):
        return 'Man(name=%s)' % repr(self.name)

    def __del__(self):
        print 'deleting %s' % self

def demo(cache_factory):
    all_refs = {}
    cache = cache_factory()
    for name in ['Jim', 'Tom', 'Green']:
        man = Man(name)
        all_refs[name] = man
        cache[name] = man
        del man

    for k, v in cache.iteritems():
        print k, '=', sys.getrefcount(v)
    del v
    del all_refs
    gc.collect()
    for k, v in cache.iteritems():
        print k, '=', sys.getrefcount(v)

demo(dict)
print
demo(weakref.WeakValueDictionary)
```

### atexit

- [Python模块学习：atexit](http://python.jobbole.com/81473/)

```python
import atexit

def f():
    print 1
    
atexit.register(f)
    
def g():
    print 2
    
if __name__ == '__main__':
    g()
```

### sys

- [Maximum and Minimum values for ints](https://stackoverflow.com/questions/7604966/maximum-and-minimum-values-for-ints)
- [What is sys.maxint in Python 3](https://stackoverflow.com/questions/13795758/what-is-sys-maxint-in-python-3)
- [How to save traceback / sys.exc_info() values in a variable](https://stackoverflow.com/questions/8238360/how-to-save-traceback-sys-exc-info-values-in-a-variable)

### thread

- [Queue.get([block[, timeout]])](https://docs.python.org/2/library/queue.html#Queue.Queue.get)
- [Python守护线程](http://blog.csdn.net/u012063703/article/details/51601579)
- [Python主线程结束为什么守护线程还在运行？](https://www.zhihu.com/question/26826953)
- 在交互式环境里，由于python主进程没有退出，导致守护线程在主线程结束后，任然会运行
- [关于python多线程编程中join()和setDaemon()的一点儿探究](https://www.cnblogs.com/cjyfff/p/3662355.html)
- 非守护线程：主线程结束了，会等待子线程
- 子线程调用join：直接阻塞主线程

```python
import time
import threading

def fun():
    print "start fun"
    time.sleep(2)
    print "end fun"

print "main thread start"
t = threading.Thread(target=fun,args=())
# t.setDaemon(False)
# t.daemon = False
t.start()
time.sleep(1)
print "main thread end"
```

```python
import time
import threading

def fun():
    print "start fun"
    time.sleep(2)
    print "end fun"

print "main thread start"
t = threading.Thread(target=fun,args=())
t.setDaemon(True) # t.daemon(True)
t.start()
time.sleep(1)
print "main thread end"
```

## _base

### as_completed

- _Waiter
  - _AsCompletedWaiter
- _AcquireFutures
- _create_and_install_waiters
- _yield_finished_futures

### wait

- _Waiter
  - _FirstCompletedWaiter
  - _AllCompletedWaiter
- _AcquireFutures
- _create_and_install_waiters

### Future

- 状态
  - PENDING
  - RUNNING
  - CANCELLED
  - CANCELLED_AND_NOTIFIED
  - FINISHED
- 用于编写Executor
  - set_running_or_nofity_cancel：CANCELLED ---> CANCELLED_AND_NOTIFIED，PENDING --> RUNNING 
  - set_result：RUNNING ---> FINISHED
  - set_exception_info：RUNNING --> FINISHED
- 用于调用Future
  - cancel：PENDING --> CANCELLED
  - result：__get_result
  - exception_info
  - cancelled：判断future状态是否属于CANCELLED或者CANCELLED_AND_NOTIFIED
  - running：判断future状态是否属于RUNNING
  - done：判断future状态是否属于CANCELLED或者CANCELED_AND_NOTIFIED或者FINISHED
- 回调
  - add_done_callback：当future的状态为CANCELLED或者CANCELLED_AND_NOTIFIED或者FINISHED时，把fn放入_done_callbacks；否则，运行fn
  - _invode_callbacks：cancel，set_result，set_exception_info
- _waiter：主要提供了与as_completed，wait的互动

### Executor

- 消费者
  - submit：需要重写，用于消费者向消息队列传入任务
  - map：基于submit
  - shutdown：需要重写，用于停止工作
- 上下文管理器
  - __enter__：返回实例
  - __exit__：自动调用shutdown

## thread

```
ThreadPoolExecutor ---> _work_queue ---> _worker
```

- ThreadPoolExecutor通过submit向_work_queue传入_workItem，并启动_worker子线程
- ThreadPoolExecutor通过调用shutdown，或在进程结束时调用_python_exit，或者当ThreadPoolExecutor被删除时，通过其弱引用来停止工作

### _workItem

- 用于包装future，函数，参数，传入_work_queue
- run：通过future判断是否任务被取消。如果是，返回；如果不是，则将函数作用在参数上。如果报错，对future设置错误信息；如果正确运行，对future设置值
- 注：将_worker改造成thread类，将run放入_worker中更佳

### _worker

- 消费者：传入ThreadPoolExecutor的弱引用和_work_queue
- 从_work_queue中阻塞的拿去_workItem，这样_worker不会作无用功，并且编程比较简单
- 判断_workItem是否为None。如果不是，运行_workItem.run，并continue；如果是，则执行下面的操作
- 使用弱引用生成executor，判断
  - _shutdown为True：The interpreter is shutting down
  - executor为None：The executor that owns the worker has been collected
  - executor._shutdown为True：The executor that owns the worker has been shutdown
- 手动删除executor，避免占用内存

### ThreadPoolExecutor

- 生产者：继承_base.Executor
- submit：向_work_queue传入_workItem，并通过_adjust_thread_count启动_worker子线程，并返回future
- shutdown：参见停止工作
- 注：将_worker改造成thread类，将向_work_queue传入_workItem，返回future和启动_worker子线程分离更佳

### 停止工作

- shutdown
  - 通过_adjust_thread_count中的`self._thread.add(t)`监测线程池，设置`self._shutdown=True`，_work_queue中放入一个None，然后join
  - 一个_worker中的_workItem为None且executor._shutdown为True，并通过`work_queue.put(None)`Notice other workers
  - 注：如果_work_queue中放入线程个数的None，不需要Notice other workers
- _python_exit
  - 通过_adjust_thread_count中的`_threads_queues[t]=self._worker_queue`监测线程池和消息队列，设置`_shutdown=True`，_work_queues中放入线程个数的None，然后join
  - _worker_中的_workItem为None且_shutdown为True
- ThreadPoolExecutor被删除
  - 通过_weakref_cb，_work_queue中放入线程个数的None
  - _worker中的_workItem为None且executor为None
  
### lock

- ThreadPoolExecutor中有一个_shutdown_lock，目的是为了防止submit和shutdown同时使用_shutdown
- 注：一般submit和shutdown都在主线程里执行，两者是同步的，不需要锁

## process

```
+----------+     +----------+       +--------+     +-----------+    +---------+
|          |  => | Work Ids |    => |        |  => | Call Q    | => |         |
|          |     +----------+       |        |     +-----------+    |         |
|          |     | ...      |       |        |     | ...       |    |         |
|          |     | 6        |       |        |     | 5, call() |    |         |
|          |     | 7        |       |        |     | ...       |    |         |
| Process  |     | ...      |       | Local  |     +-----------+    | Process |
|  Pool    |     +----------+       | Worker |                      |  #1..n  |
| Executor |                        | Thread |                      |         |
|          |     +----------- +     |        |     +-----------+    |         |
|          | <=> | Work Items | <=> |        | <=  | Result Q  | <= |         |
|          |     +------------+     |        |     +-----------+    |         |
|          |     | 6: call()  |     |        |     | ...       |    |         |
|          |     |    future  |     |        |     | 4, result |    |         |
|          |     | ...        |     |        |     | 3, except |    |         |
+----------+     +------------+     +--------+     +-----------+    +---------+
```

- _work_ids：线程安全的消息队列，记录还未从thread出去的work
- _pending_work_items：字典，记录还未进入thread的result
- _call_queue：进程安全的消息队列，最大长度为workers的个数
- _result_queue：进程安全的消息队列
- ProcessPoolExecutor通过submit向_work_ids，_pending_work_items添加work，并启动thread，process
- ProcessPoolExecutor通过调用shutdown，或在进程结束时调用_python_exit，或者当ProcessPoolExecutor被删除时，通过其弱引用来停止工作
- 注：任意时刻_pending_work_items的个数不小于_work_ids的个数

### _WorkItem, _ResultItem, _CallItem

- _WorkItem：用于包装future，函数，参数
- _ResultItem：用于包装函数返回的结果，传入_WorkItem的计数，函数运行的exception，result
- _CallItem：用于包装需要运行的函数和参数，传入_WorkItem的计数，函数，参数

### _process_worker

- 消费者：传入
  - _call_queue：_CallItem消息队列
  - _result_queue：_ResultItem消息队列
- 从_call_queue中阻塞的拿取_CallItem，这样_worker不会作无用功，并且编程比较简单
- 判断_CallItem是否为None。如果是，wake up queue management thread，并返回；如果不是，则执行如下操作
- 将函数作用在参数上。如果报错，对_ResultItem设置错误信息；如果正确运行，对_ResultItem设置值。同时，把_ResultItem传入_result_queue
- 注：当_CallItem为None时，意味着_queue_manangement_work调用了shutdonw_one_process，需要结束子进程
- 注：wake up queue manangement参见wake up queue manangement

### _queue_management_worker

- 代理：传入
  - ProcessPoolExecutor的弱引用
  - _processes：进程池
  - _pending_work_items：_WorkItem的计数到_WorkItem的映射表
  - _work_ids：_WorkItem的计数消息队列
  - _call_queue：_CallItem消息队列
  - _result_queue：_ResultItem消息队列
- _add_call_item_to_queue：不断把_WorkItem包装成_CallItem，传入_call_queue，直到_call_queue已满，或者_work_ids为空
  - 判断_call_queue是否已满。如果满了，返回；如果不满，执行如下操作
  - 判断_work_ids是否有。如过没有，返回；如果有，执行如下操作
  - 取出WorkId，通过_pending_work_items获取对应_WorkItem，并通过future判断是否任务被取消。如果是，删除_pending_work_items；如果不是，则把_WorkItem包装成_CallItem，传入_call_queue
- 处理_result_queue
  - 从_result_queue中阻塞的拿取_ResultItem，这样_worker不会作无用功，并且编程比较简单
  - 判断_ResultItem是否为None。如果是，执行如下操作
  - 从_pending_work_items取出对应_WorkItem，设置future
  - 从_pending_work_items删除对应_WorkItem
- 使用弱引用生成executor，判断
  - _shutdown为True：The interpreter is shutting down
  - executor为None：The executor that owns the worker has been collected
  - executor._shutdown为True：The executor that owns the worker has been shutdown
  - 判断_pending_work_items是否为空。如果是，执行如下操作：
    - 通过shutdown_one_process关闭所有process
- 手动删除executor，避免占用内存
- 注：由于thread不再通过_ResultItem为None来判断是否结束，所以处理_request_queue里没有continue
- 注：起进程放在代理里面起更佳
  
### ProcessPoolExecutor

- 生产者：继承_base.Executor
- submit：向_work_ids，_pending_work_items添加work，并通过_start_queue_management_thread启动_queue_management_worker子线程，通过_adjust_process_count启动_process_worker子进程，并返回future
- shutdown：参见停止工作

### 停止工作

- shutdown
  - 通过self._queue_management_thread监测线程，设置`self._shutdown_thread=True`，_result_queue中放入None，然后join
- _python_exit
  - 通过_start_queue_management_thread中的`_threads_queues[t]=self._result_queue`监测线程和消息队列，设置`_shutdown=True`，_result_queue中放入None，然后join
- ThreadPoolExecutor被删除
  - 通过_weakref_cb，_work_queue中放入None

### wake up queue management thread

- _python_exit：提示queue thread停止工作
- _process_worker：没用
- weakref：提示queue thread停止工作
- submit：当有新的worker进入时，防止queue thread阻塞在`result_item = result_queue.get(block=True)`
- shutdown：提示queue thread停止工作
- 注：当pending_work_item为空时，结束依赖_result_queue获取_python_exit，_weakref，shutdown传入的None
- 注：当pending_work_item不为空时，结束依赖_result_queue获取非None的_ResultItem

### 例子

- submit向_result_queue传入None
- shutdown向_request_queue传入None
- _process_worker向_request_queue传入_ResultItem
- 停止工作

```python
from concurrent.futures import ProcessPoolExecutor
import time

def f(x):
    time.sleep(10)
    return x

if __name__ == '__main__':
    pool = ProcessPoolExecutor(max_workers=2)
    result = pool.map(f, [1])
    pool.shutdown()
    print result
```

- submit向_result_queue传入None
- _process_worker向_request_queue传入_ResultItem
- shutdown向_request_queue传入None
- 停止工作

```python
from concurrent.futures import ProcessPoolExecutor
import time

def f(x):
    time.sleep(10)
    return x

if __name__ == '__main__':
    pool = ProcessPoolExecutor(max_workers=2)
    result = list(pool.map(f, [1]))
    pool.shutdown()
    print result
```

- 注：两个程序的运行顺序不同是因为使用list将触发future中的result代码，进一步触发wait，等待set_result的notify。而set_result必须等到_result_queue非空才行。此时由于shutdown被阻塞，因此_result_queue只能等待process运行的结果
- 注：future：
  - wait：result，exception_info
  - notify_all：cancel，set_result，set_exception_info

```python
from concurrent.futures import ProcessPoolExecutor

def f(x):
    return x

if __name__ == '__main__':
    pool = ProcessPoolExecutor(max_workers=2)
    f = pool.submit(f, [1])
    pool.shutdown()
    print f.result()
    print f.result()
```

- 注：两个`f.result()`运行的future中的result代码是不同的：
  - 第一次，运行的是wait之后的
  - 第二次，运行的是wait之前的

## reference

- [Compulsory usage of if __name__==“__main__” in windows while using multiprocessing](https://stackoverflow.com/questions/20360686/compulsory-usage-of-if-name-main-in-windows-while-using-multiprocessi)
- [python concurrent.futures](https://www.cnblogs.com/kangoroo/p/7628092.html)
- [使用python的并发库concurrent.futures实现异步](http://xiaorui.cc/2014/11/15/%E4%BD%BF%E7%94%A8python%E7%9A%84%E4%B8%8A%E5%B1%82%E5%B0%81%E8%A3%85%E5%B9%B6%E5%8F%91%E5%BA%93concurrent-futures%E5%AE%9E%E7%8E%B0%E5%BC%82%E6%AD%A5/)
- [python并发库：concurrent.futures的使用](http://blog.csdn.net/drdairen/article/details/69487643)
- [python并发之concurrent.futures](http://blog.csdn.net/dutsoft/article/details/54728706)
- [concurrent.futures — Asynchronous computation](http://pythonhosted.org//futures/)
- [concurrent.futures — Launching parallel tasks](https://docs.python.org/3/library/concurrent.futures.html)