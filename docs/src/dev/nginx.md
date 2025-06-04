## 参考

* [为没有80、443端口的域名申请SSL证书](https://www.fisheryung.top:9002/%E4%B8%BA%E6%B2%A1%E6%9C%8980%E3%80%81443%E7%AB%AF%E5%8F%A3%E7%9A%84%E5%9F%9F%E5%90%8D%E7%94%B3%E8%AF%B7ssl%E8%AF%81%E4%B9%A6.html)

* [阿里云：Nginx或Tengine服务器配置SSL证书](https://help.aliyun.com/zh/ssl-certificate/user-guide/install-ssl-certificates-on-nginx-servers-or-tengine-servers)

<br>

---

## 安装及使用

1. 安装

    ```shell
    sudo apt install nginx
    ```

2. 卸载

    ```shell
    sudo apt purge nginx nginx-common
    sudo apt autoremove
    ```

2. 热重载

    ```shell
    sudo nginx -s reload
    ```

3. 重启服务

    ```shell
    sudo systemctl restart nginx
    ```

<br>

---

## /etc/nginx/nginx.conf

* 主配置文件：用于定义全局配置和基本设置
* 包含指令：包含服务器级别的设置、全局变量、工作进程数、日志文件位置、用户权限、加载模块等
* 包含其他文件：通常会使用include指令将其他配置文件包含进来，如/etc/nginx/conf.d/*.conf，从而组织和管理配置文件

<br>

---

## /etc/nginx/conf.d/*.conf

* 虚拟主机配置文件：用于定义具体的虚拟主机（服务器）配置的文件，通常用于设置特定域名的服务器块
* 作用范围：这个文件主要包含HTTP服务器块（server block），定义了具体的域名、监听端口、根目录、日志路径、反向代理设置等
* 从属关系：这个文件通常被主配置文件 nginx.conf 通过 include 指令包含进来，使得Nginx能够加载这些虚拟主机配置

```conf
server {
    listen 80;                    # IPv4 80端口
    
    server_name example.com;      # 域名
    
    root /var/www/example.com;    # 网站根目录
    index index.html;             # 默认首页
    
    location / {
        try_files $uri $uri/ =404;# 文件查找规则
    }
}
```


<br>

---

## SSL 证书

```conf
server {
    listen 80;                              # 将 http 重定向到 https
    server_name dxlcq.cn;
    return 301 https://$host$request_uri;
}

server {
    listen 443 ssl;
    server_name dxlcq.cn;

    ssl_certificate     /etc/letsencrypt/live/dxlcq.cn/fullchain.pem;   # SSL 完整证书
    ssl_certificate_key /etc/letsencrypt/live/dxlcq.cn/privkey.pem;     # SSL 私钥
    ssl_session_cache   shared:SSL:1m;                                  # 缓存 SSL 会话
    ssl_ciphers         HIGH:!aNULL:!MD5;                               # 支持的密码套件
    ssl_protocols       TLSv1.2 TLSv1.3;                                # 支持的协议版本
    ssl_prefer_server_ciphers on;                                       # 优先使用服务器密码套件

    location /.well-known {                                             # 用于验证域名所有权
        root /;
    }
}
```

* 安装 `certbot`

    ```shell
    sudo snap install --classic certbot
    sudo ln -s /snap/bin/certbot /usr/bin/certbot
    ```

* 首次申请

    ```shell
    sudo certbot certonly --webroot -w / -d dxlcq.cn
    ```

* 测试更新

    ```shell
    sudo certbot renew --dry-run
    ```

* 每周更新 `sudo crontab -e`

    ```shell
    0 0 * * 1 certbot renew && nginx -s reload
    ```

* 查看证书剩余时长 

    ```shell
    sudo certbot certificates
    ```

<br>

---

## 下载站点与加密

```conf
server {
    location /private {         # 文档根目录
        alias   /usr/share/nginx/private;
        autoindex on;           # 自动索引

        # 鉴权
        auth_basic "password";
        auth_basic_user_file /usr/share/nginx/htpwd;
    }
}
```

* [htpwd 在线生成](https://tool.oschina.net/htpasswd)

<br>

---

## 使用 docker 快速部署 Nginx

```shell
sudo docker run --rm -d -p 80:80 \
    -v /www:/usr/share/nginx/html nginx
```

<br>

---

## 反向代理

```conf
server {
    resolver 119.29.29.29 valid=6s;                                     # dns 解析 6 秒刷新一次

    location / {                                                        # 反向代理到后端服务器
        proxy_pass http://dxlcq.cn;                                     # 后端服务器地址和端口
        proxy_set_header Host $host;                                    # 保持主机头不变
        proxy_set_header X-Forwarded-Proto $scheme;                     # 转发协议
    }
}
```