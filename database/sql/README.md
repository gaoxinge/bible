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
group by campaignid, transid, targetid, item->>'logDate', item->>'campaignModel'
```

### join

```sql
select a.id,a.author,b.count from runoob_tb a inner join tcount_tb b on a.author=b.author;
select a.id,a.author,b.count from runoob_tb a left join tcount_tb b on a.author=b.author;
select b.id,b.author,a.count from tcount_tb a right join runoob_tb b on a.author=b.author;
```

## insert

```sql
insert into runoob_tb (title,author,date) values ("PHP","John Poul",NOW());
insert into runoob_tb (title,author,date) values ("MySQL","Abdul S",NOW());
insert into runoob_tb (title,author,date) values ("JAVA","Sanjay","2007-05-06");
insert into runoob_tb (title,author,date) values ("HTML","gaoxinge","2016-07-24"), ("C++","xinge","2016-07-24"), ("Python","ge","2016-07-23");
insert into runoob_tb2 select title,author from runoob_tb;
```

## update

```sql
update runoob_tb set title="HTML" where id=4;
```

## delete

```sql
delete from runoob_tb where id=4;
```

### 数据类型

MySQL主要有三种数据类型：数值，日期和时间，以及字符串。对于`null`，要用`is null`和`is not null`来判断

### 数据表

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

drop table runoob_tb;
```

### 字段

```
字段：show columns from runoob_tb2;

添加：alter table runoob_tb2 add id int;

删除：alter table runoob_tb2 drop id;

修改：alter table runoob_tb2 modify id char(10);
      alter table runoob_tb2 change id ide char(10);
      alter table runoob_tb2 modify ide bigint not null default 100;
      alter table runoob_tb2 alter ide set default 1000;
      alter table runoob_tb2 alter ide drop default;

表名：alter table runoob_tb2 rename to tcount_tb;
```

### 索引

索引主要分为一般索引，唯一索引以及主键。他们都可由`create`创建，`alter`修改