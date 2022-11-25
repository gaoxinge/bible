## 数据类型

- 数值
- 日期和时间
- 字符串
- null
  - is null
  - is not null

## 约束

- 主键约束（Primary Key Constraint）
- 唯一约束（Unique Constraint）
- 检查约束（Check Constraint）
- 默认约束（Default Constraint）
- 外键约束（Foreign Key Constraint）

### 参考

- [数据库中的五种约束及其添加方法](http://blog.csdn.net/shuohuameijiang/article/details/7275716)
- [数据库的约束简介](https://www.cnblogs.com/netsql/archive/2010/05/06/1729162.html)
- [数据库的三大范式以及五大约束](https://www.cnblogs.com/waj6511988/p/7027127.html)

## 索引

- 一般索引
- 唯一索引
- 主键索引
- 聚集索引

### 参考

- [SQL索引一步到位](https://www.cnblogs.com/AK2012/archive/2013/01/04/2844283.html)
- [mysql索引总结----mysql 索引类型以及创建](http://blog.csdn.net/xluren/article/details/32746183)
- [数据库索引的实现原理](http://blog.csdn.net/kennyrose/article/details/7532032)
- [MySQL索引原理及慢查询优化](http://blog.jobbole.com/86594/)

## select

```sql
/* 
 * basic select sql
 */
select * from Products; # select all
select prod_name from Products;
select prod_id, prod_name, prod_price form Products;
select distinct vend_id from Products;
select prod_name from Products limit 5;
select prod_name from Products limit 5 offset 5;
```

### order by

```sql
select prod_name from Products order by prod_name;
select prod_id, prod_price, prod_name from Products order by prod_price, prod_name;
select prod_id, prod_price, prod_name from Products order by prod_price desc, prod_name;
```

### where 

```sql
select prod_name, prod_price from Products where prod_price = 3.49;
select vend_id, prod_name from Products where vend_id != 'DLL01';
select cust_name from Customers where cust_email is null;
```

### and, or

```sql
select prod_id, prod_price, prod_name from Products where vend_id = 'DLL01' and prod_price <=4;
select prod_name, prod_price from Products where vend_id = 'DLL01' or vend_id = 'BRS01';
```

### like

```sql
select prod_id, prod_name from Products where prod_name like 'Fish%';
select prod_id, prod_name from Products where prod_name like '__ inch teddy bear';
```

### calculate field

```sql
select vend_name + '(' + vend_country + ')' from Vendors order by vend_name;
select vend_name || '(' || vend_country || ')' from Vendors order by vend_name;
select Concat(vend_name, '(',  vend_country, ')') from Vendors order by vend_name;
select prod_id, quantity, item_price, quantity*item_price as expanded_price from OrderItems where order_num =20008;
```

### function

- text
  - left
  - length
  - lower
  - ltrim
  - right
  - rtrim
  - soundex
  - upper
- date
  - datepart
  - date_part
  - to_char
  - to_number
  - to_date
  - year
  - strftime
- value
  - abs
  - cos
  - exp
  - pi
  - sin
  - sqrt
  - tan
- aggregate
  - avg
  - count
  - sum
  - max
  - min 

```sql
select count(daybudget) from zs_campaign_meta;
select count(*) from zs_campaign_meta;
select avg(daybudget) from zs_campaign_meta;
select avg(daybudget, daybudget) from zs_campaign_meta; # error
select avg(*) from zs_campaign_meta; # error
```

### group by

- order
  - select
  - from
  - where
  - group by
  - having
  - order by

```sql
select vend_id, count(*) as num_prods from Products where prod_price >= 4 group by vend_id having count(*) >= 2;
select order_num, count(*) as items from OrderItems group by order_num hanving count(*) >= 3 order by items, order_num;
```

### subquery

```sql
select cust_name, cust_contact from Customers where cust_id in ('1000000004', '1000000005');
select cust_name, cuct_state 
       (select count(*) from Orders where Orders.cust_id = Customers.cust_id) as orders
from Customers where order by cust_name;
select campaignid, transid, targetid, 
       item->>'logDate' as logdate, 
       (item->>'campaignModel')::int as campaignmodel,
       sum((item->>'adPv')::double precision) as pv ,
       sum((item->>'charge')::double precision) as charge,
       sum((item->>'click')::double precision)as click,
       current_timestamp as updatetime 
from (select distinct on (campaignid, transid, targetid)
      campaignid, transid, targetid, json_array_elements(content::json) as item
      from zs_target_hourlist where queuets >= '11111111111' and queuets <= '11111111111'
      order by campaignid, transid, targetid,requestts desc) t
group by campaignid, transid, targetid, item->>'logDate', item->>'campaignModel';
```

### join

```sql
# 笛卡儿积联结，cross join
select vend_name, prod_name, prod_price from Vendors, Products;

# 等值联结，inner join
select vend_name, prod_name, prod_price from Vendors, Products where Venders.vend_id = Products.vend_id;
select vend_name, prod_name, prod_price from Vendors inner join Products on Venders.vend_id = Products.vend_id;

# outer join
SELECT Websites.name, access_log.count, access_log.date
FROM Websites
LEFT JOIN access_log
ON Websites.id=access_log.site_id
ORDER BY access_log.count DESC;

SELECT Websites.name, access_log.count, access_log.date
FROM Websites
LEFT OUTER JOIN access_log
ON Websites.id=access_log.site_id
ORDER BY access_log.count DESC;

SELECT Websites.name, access_log.count, access_log.date
FROM access_log
RIGHT JOIN Websites
ON access_log.site_id=Websites.id
ORDER BY access_log.count DESC;

SELECT Websites.name, access_log.count, access_log.date
FROM access_log
RIGHT OUTER JOIN Websites
ON access_log.site_id=Websites.id
ORDER BY access_log.count DESC;

SELECT Websites.name, access_log.count, access_log.date
FROM Websites
FULL OUTER JOIN access_log
ON Websites.id=access_log.site_id
ORDER BY access_log.count DESC;
```

### union

```sql
SELECT cust_name, cust_contact, cust_email
FROM Customers
WHERE cust_state IN ('IL', 'IN', 'MI')
UNION
SELECT cust_name, cust_contact, cust_email
FROM Customers
WHERE cust_name = 'Fun4All';

SELECT cust_name, cust_contact, cust_email
FROM Customers
WHERE cust_state IN ('IL', 'IN', 'MI')
UNION ALL
SELECT cust_name, cust_contact, cust_email
FROM Customers
WHERE cust_name = 'Fun4All';

SELECT cust_name, cust_contact, cust_email
FROM Customers
WHERE cust_state IN ('IL', 'IN', 'MI')
UNION ALL
SELECT cust_name, cust_contact, cust_email
FROM Customers
WHERE cust_name = 'Fun4All'
ORDER BY cust_name, cust_contact;
```

## insert

```sql
INSERT INTO Websites (name, url, country)
VALUES ('stackoverflow', 'http://stackoverflow.com/', 'IND');

INSERT INTO Websites (name, country)
SELECT app_name, country FROM apps;
```

## update

```sql
UPDATE Websites 
SET alexa='5000', country='USA' 
WHERE name='菜鸟教程';
```

## delete

```sql
DELETE FROM Websites
WHERE name='百度' AND country='CN';
```

## table

```sql
create table runoob_tb(
id int not null auto_increment,
title varchar(100) not null,
author varchar(40) not null,
date date,
primary key (id)
);

create table runoob_tb2(
title varchar(100) not null,
author varchar(40) not null,
);       

show columns from runoob_tb2;

alter table runoob_tb2 add id int;
alter table runoob_tb2 drop id;
alter table runoob_tb2 modify id char(10);
alter table runoob_tb2 change id ide char(10);
alter table runoob_tb2 modify ide bigint not null default 100;
alter table runoob_tb2 alter ide set default 1000;
alter table runoob_tb2 alter ide drop default;
alter table runoob_tb2 rename to tcount_tb;

drop table runoob_tb;
```

## view

```sql
CREATE VIEW OrderItemsExpanded AS
SELECT order_num,
       prod_id,
       quantity,
       item_price,
       quantity * item_price AS expanded_price
From OrderItems
```

## 其他

- 函数
- 存储过程
- 事务管理
- 游标
- 触发器
- 数据库安全