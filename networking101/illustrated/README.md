## RFC

可以在[RFC search](http://www.rfc-editor.org/search/rfc_search.php)中搜索RFC文档。

## 网卡

```
                                                                  |--->  IP
                 |--->  有线网卡（MAC地址，硬件地址，物理地址） --|--->  IP
主机（主机名） --|
                 |--->  无线网卡（MAC地址，硬件地址，物理地址） --|--->  IP
                                                                  |--->  IP
```

### 一个网卡可以绑定几个MAC地址

- 一个

### 一个网卡可以绑定几个IP

- 多个

### MAC地址

- [怎么查询电脑mac地址](https://jingyan.baidu.com/article/84b4f56529f2dc60f7da325c.html)

### IP地址

- ipconfig：查看网卡绑定的IP（使用无线路由器上网，对应的是无线网卡 ）
- baidu：查看运营商提供的IP（NAT）

### get

- `getaddrinfo`
- `getnameinfo`
- `gethostname`
  - `socket.gethostname()` -> `'TR-XGGAO'`
- `gethostbyaddr` 
  - `socket.gethostbyaddr('localhost')` -> `('TR-XGGAO.tianrang-inc.com', [], ['::1'])`
  - `socket.gethostbyaddr('127.0.0.1')` -> `('TR-XGGAO.tianrang-inc.com', [], ['127.0.0.1'])`
- `gethostbyname`
  - `socket.gethostbyname('localhost')` -> `'127.0.0.1'`
  - `socket.gethostbyname('baidu.com')` -> `'123.125.115.110'`
- `gethostbyname_ex`
  - `socket.gethostbyname_ex('localhost')` -> `('TR-XGGAO.tianrang-inc.com', [], ['127.0.0.1'])`
  - `socket.gethostbyname_ex('baidu.com')` -> `('baidu.com', [], ['123.125.115.110', '220.181.57.216'])`

### dns

- 主机名：host name
- 域：domain
- 全限定域名：FQDN，host name + domain
- 域名：domain name
- HOST文件：域名到IP的映射
- 一个主机只有一个主机名
- 一个域名对应一个IP
- [What is the difference between a hostname and a domain name](https://support.suso.com/supki/What_is_the_difference_between_a_hostname_and_a_domain_name)
- [Difference between host name and domain name](https://superuser.com/questions/59093/difference-between-host-name-and-domain-name/59094)
- [What Is A Hostname?](https://dyn.com/blog/what-is-a-hostname/)
- [IP、主机名和域名](https://blog.csdn.net/houjixin/article/details/52604941)
- [厘清几个概念：互联网/WWW/Web 、URI/URL、主机名/域名](https://blog.csdn.net/SuperYuHuoFei/article/details/77159444)
- [域名、主机名、网站名以及 URL 基础概念](http://www.cnblogs.com/yaolin1228/p/8590533.html)
- [主机名和域名之间的区别——关于域名和主机名的…](http://www.west.cn/info/html/fuwuqijishu/Webfuwuqi/20180713/4323229.html)
- [一个域名可以绑定多个主机吗？](https://zhidao.baidu.com/question/680379305436741852.html)

## windows

### ipconfig

ipconfig命令用于显示网卡的配置，可以自动刷新DHCP和DNS设置。例如

```
> ipconfig
```

仅显示网卡的部分配置，而

```
> ipconfig /all
```

显示网卡的所有配置。

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

tracert命令通过增加TTL字段，向目标主机发送ICMP回声请求报文，来确认路径。例如

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
> nslookup 127.0.0.1
```

### netsh

```
> netsh interface ipv4 show subinterfaces
```

显示系统上接口及其MTU。

### telnet

- [telnet用法测试端口号](http://jingyan.baidu.com/article/a3aad71aa9e6efb1fb009694.html)

### ftp

- [通过cmd命令到ftp上下载文件](http://jingyan.baidu.com/article/6525d4b1300912ac7d2e941b.html)

## linux

- [你必须了解的基础的Linux网络命令](http://os.51cto.com/art/201609/518048.htm)
- [Linux网络配置和网络诊断命令介绍](http://jingyan.baidu.com/article/c1465413b694d90bfcfc4c97.html)

### ifconfig

```
> ifconfig
> ifconfig -a
> ifconifg lo
```

查看网卡和ip信息。

### arp

```
> arp -a
```

显示本地arp缓存表。

### netstat

```
> netstat -in
> netstat -i
```

显示系统上的接口及其MTU。