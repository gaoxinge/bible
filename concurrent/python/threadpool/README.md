## structure

使用消息队列和putRequest高度解耦WorkerThread和WorkRequest

```
+-------------+                                 +----------------+
|             |  ------ _requests_queue ------> |                |
| threadpool  |                                 |  workerthread  |
|             | <------ _results_queue  ------  |                |
+-------------+                                 +----------------+
```

## example

```python
from threadpool import ThreadPool, makeRequests

def f(a):
    return a

def g(request, a):
    print a + 1
    
pool = ThreadPool(3)
requests = makeRequests(f, [1, 2, 3], g)
[pool.putRequest(req) for req in requests]
pool.wait()
```

## WorkRequest

用于包装任务

- callable_：目标函数
- args：参数
- kwds：参数
- requestID：任务id
- callback：回调函数
- exc_callback：错误处理

## WorkerThread

消费者

- run：需要注意
```python
if self._dismissed.isSet():
    self._requests_queue.put(request)
    break
```
- dismiss：设置threading.Event()，使WorkerThread退出

## ThreadPool

生产者

- workers
  - createWorkers：创建WorkerThread
  - dismissWorkers：dismiss WorkerThread。若do_join为True，则join dismiss_list；否则把dismiss_list加入dismissedWorkers
  - joinAllDismissedWorkers：join dismissedWorkers
- schedule
  - poll：先查看还有没有未处理的workRequest，再查看有没有可用的workers。如没有问题，开始调度直到_results_queue为空，其中会将处理完的request从workRequests中删除
  - wait：轮询直到没有未处理的workRequest
- putRequest：把WorkRequest传入_requests_queue

## makeRequest

用于把任务包装成WorkRequest