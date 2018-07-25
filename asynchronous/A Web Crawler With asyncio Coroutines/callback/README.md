## 过程

- Fetch(link1): fetch
- Fetch(link1): fetch ---> connected
- Fetch(link1): fetch ---> connected ---> read_response
- Fetch(link1): fetch ---> connected ---> read_response ---> ... ---> read_response
  - Fetch(link2): fetch
  - Fetch(link3): fetch

## 分析

- 同一时刻，只有一个Fetch(link)在执行，且执行下面的一个函数：
  - fetch
  - connected
  - read_response

## 过程

- Fetch(link1).fetch():
- Fetch(link1).fetch(): connected
- Fetch(link1).fetch(): connected ---> read_response
- Fetch(link1).fetch(): connected ---> read_response ---> ... ---> read_response
  - Fetch(link2).fetch():
  - Fetch(link3).fetch():
  
## 分析

- 同一时刻，只有一个Fetch(link)在执行，且执行下面的一个函数：
  - connected
  - read_response

## test.py

- link构成无循环的有向图

### 过程和分析

- 从loop的角度看：
  - 同一时刻，只有一个Fetch(link)在执行
  - 同一时刻，上述Fetch(link)要么在执行过程1`...`，要么在执行过程2

```python
links = self.parse_links()

for link in links:
    urls_todo.add(link)
    Fetcher(link).fetch()

urls_todo.remove(self.url)
if not urls_todo:
    global stopped
    stopped = True
```

### 推论

- 当某个link的过程2结束时，其所有的子link均在urls_todo中
- 当某个link的过程2结束时，该link并不在urls_todo中
- 当某个link的过程2结束时，该link结束后的urls_todo等于上一个link结束后的urls_todo减去该link加上该link的子link

### 结论1：程序将会遍历所有节点

假设urls_todo中的每个url都会被运行到的话，由于每个link的所有子link都会加入urls_todo，因此只需要构造一个从根link到该link的路径即可

### 结论2：程序将会停止

考虑序列{(link, urls_todo)}，假设对任意link，urls_todo非空：

- 如果对任意link，存在某个link之后的urls_todo就不再包含该link，那么可以取所有link的max，矛盾
- 因此存在一个link，及序列{(link, urls_todo)}

## test1.py

- link构成有向图

### 过程和分析

- 从loop的角度看：
  - 同一时刻，只有一个Fetch(link)在执行
  - 同一时刻，上述Fetch(link)要么在执行过程1`...`，要么在执行过程2

```python
links = self.parse_links()

for link in links.difference(seen_urls):
    urls_todo.add(link)
    Fetcher(link).fetch()

seen_urls.update(links)
urls_todo.remove(self.url)
if not urls_todo:
    global stopped
    stopped = True
```

### 推论

- 当某个link的过程2结束时，其所有的子link均在urls_todo中
- 当某个link的过程2结束时，该link并不在urls_todo中
- 当某个link的过程2结束时，该link结束后的urls_todo等于上一个link结束后的urls_todo减去该link加上该link的子link

### 结论1：程序将会遍历所有节点

假设urls_todo中的每个url都会被运行到的话，由于每个link的所有子link都会加入urls_todo，因此只需要构造一个从根link到该link的路径即可

### 结论2：程序将会停止

由于有seen_urls，因此对任意link，存在某个link之后的urls_todo就不再包含该link，那么可以取所有link的max即可