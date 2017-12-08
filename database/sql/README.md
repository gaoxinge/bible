## select

```sql
select id from runoob_tb;
select * from runoob_tb;
select * from runoob_tb where id>1 and date!="2007-05-06";
select * from runoob_tb where author like "%jay";
select * from runoob_tb where author regexp "jay";
select * from runoob_tb order by date;
select date,count(*) from runoob_tb group by date;
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

### 函数

- 内建函数
  - count
  - sum
  - avg
  - max
  - min 

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