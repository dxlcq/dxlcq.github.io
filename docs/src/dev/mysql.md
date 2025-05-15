## setup

### linux

1. 下载安装
    * `apt install mysql-server`
    * `apt install mysql-client`

2. 初始化
    * `mysql_secure_installation`

3. 启动服务
    * `service mysql start`

4. 登录
    * `mysql -u root -p`

5. 设置密码
    * `use mysql;`
    * `ALTER USER 'root'@'localhost' IDENTIFIED WITH mysql_native_password BY '12345678';`

5. 退出
    * `quit`

### windows

1. [下载](https://dev.mysql.com/downloads/installer/)

2. 默认安装即可


<br>

---

## ues

## 其他

* 导出数据库
    ```shell
    mysqldump -uroot -p1234 --databases db1 --tables t1 >/tmp/db1.sql
    ```

## 库

### 增

* 创建数据库
    ```sql
    create database 库名;
    ```

### 删

* 删除数据库
    ```sql
    drop database 库名;
    ```

### 改

* 切换当前使用的数据库
    ```sql
    use 库名;
    ```

### 查

* 查看所有数据库
    ```SQL
    show databases;
    ```

<br>

---

## 表

### 增

* 创建表 
    ```sql
    CREATE TABLE 表名(
        列名 类型 约束,
        user_id INT AUTO_INCREMENT PRIMARY KEY,
        username VARCHAR(50) NOT NULL,
        birthdate DATE
    );
    ```

### 删

* 删除某张表 
    ```sql
    drop table 表名;
    ```

### 改



### 查

* 查看所有表 
    ```sql
    show tables;
    ```

<br>

---

## 记录

### 增

* 增加一条记录
    ```sql
    INSERT INTO 表名 (列名, 列名)
    VALUES ('Alice', 20);
    ```

### 删

* 删除一条记录
    ```sql
    delete from 表名 where 列名 = 值;
    ```

### 改

### 查

* 查看表中所有数据
    ```sql
    select * from 表名;
    ```