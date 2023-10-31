---
html:
    toc: true   # 打开侧边目录
export_on_save:
    html: true  # 自动保存
---

* ubuntu

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