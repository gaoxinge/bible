## prepare

### threading.Event

- 标志位：默认为False
- wait：如果timeout不为None，那么阻塞至timeout或者标志位为True；如果timeout为None，那么阻塞至标志位为True
- set：设置标志位为True
- clear：设置标志位为False
- isSet：判断标志位是否为True

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

- BaseScheduler
- BlockingScheduler
- BackgroundScheduler
- AsyncIOScheduler
- GeventScheduler
- TornadoScheduler
- TwistedScheduler
- QtScheduler