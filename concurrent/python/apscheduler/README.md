## prepare

### threading.Event

- 标志位：默认为False
- wait：如果timeout不为None，那么阻塞至timeout或者标志位为True；如果timeout为None，那么阻塞至标志位为True
- set：设置标志位为True
- clear：设置标志位为False
- isSet：判断标志位是否为True

### six

## util

## event

## job

## triggers

控制调度逻辑。

- date：在指定时间，调度一次
- interval：相隔指定时间，调度一次
- cron：在指定时间，反复调度

## job stores

## executors

## schedulers

### BaseScheduler

- 配置
  - jobstores：
  - executors：
  - job_defaults：
  - __init__：把参数gconfig，options传入configure
  - configure：先判断state是否为STATE_STOPPED；再处理gconfig，放入config；然后把options更新入config；最后调用_configure
  - _configure：
  - _create_plugin_instance：
  - Method1
  - Method2
  - Method3
  
### BlockingScheduler

### BackgroundScheduler

### GeventScheduler

### AsyncIOScheduler

### TornadoScheduler

### TwistedScheduler

### QtScheduler

## reference

- [User guide](http://apscheduler.readthedocs.io/en/latest/userguide.html)
- [APScheduler 3.0.1浅析](http://www.cnblogs.com/quijote/p/4385774.html)