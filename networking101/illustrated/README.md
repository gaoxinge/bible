## RFC

可以在[RFC search](http://www.rfc-editor.org/search/rfc_search.php)中搜索RFC文档。

## 网卡

## windows

### ipconfig

ipconfig命令用于显示网卡的配置，可以自动刷新DHCP和DNS设置。例如

```
> ipconfig
```

仅显示有配置的网卡，而

```
> ipconfig /all
```

显示所有网卡。

### netstat

netstat用于查看各个协议的信息。例如

```
> netstat -s
```

显示各个协议的数据。

```
> netstat -e
```

显示总数据。

```
> netstat -r
```

显示路由表的信息。

```
> netstat -a
```

显示各个协议的连接状态。

### ping

ping命令通过发送ICMP回声请求报文来检测与另一台主机的连接。例如

```
> ping 127.0.0.1
```

### tracert

tracert命令通过增加TTL字段，向目标主机ICMP回声请求报文，来确认路径。例如

```
> tracert 127.0.0.1
```

### arp

arp命令用于显示和修改本地arp缓存表。例如

```
> arp -a
```

显示本地arp缓存表。

### route

route命令用于显示和修改本地路由表。例如

```
> route print
```

显示本地路由表。

### nslookup

nslookup命令用于显示DNS查询信息。例如

```
> nslookup
```

## linux