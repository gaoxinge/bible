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

## 存储过程

## 数据类型

MySQL主要有三种数据类型：数值，日期和时间，以及字符串。对于`null`，要用`is null`和`is not null`来判断

## 索引

索引主要分为一般索引，唯一索引以及主键。他们都可由`create`创建，`alter`修改

## 其他

- 事务管理
- 游标