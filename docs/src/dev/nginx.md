## 编译安装

1. 下载依赖

    ```sh
    sudo apt update
    sudo apt install build-essential libpcre3 libpcre3-dev libssl-dev zlib1g zlib1g-dev
    ```

2. 下载源码
    ```sh
    wget https://nginx.org/download/nginx-1.*.tar.gz
    tar -zxvf nginx*
    cd nginx*
    ```

3. 下载 `rtmp` 模块（可选）
    ```sh
    git clone https://github.com/arut/nginx-rtmp-module.git
    ```

4. 编译安装
    ```sh
    ./configure --add-module=./nginx-rtmp-module
    make
    sudo make install
    ```

5. 验证
    ```sh
    sudo /usr/local/nginx/sbin/nginx -V
    ```

<br>

---

## 普通安装及操作

1. 安装

    ```shell
    sudo apt install nginx
    ```

2. 重新加载配置文件

    ```shell
    sudo systemctl reload nginx
    ```

3. 重启服务

    ```shell
    sudo systemctl restart nginx
    ```

---

### 反向代理




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
    listen 80;
    listen 1314 ssl;
    server_name xn--e6q212bhn0c.xn--6qq986b3xl;
    
    # http:80 -> https:1314
    error_page 497 https://$server_name:1314$request_uri;

    # 证书文件、私钥绝对路径
    ssl_certificate /etc/letsencrypt/live/xn--e6q212bhn0c.xn--6qq986b3xl/fullchain.pem;
    ssl_certificate_key /etc/letsencrypt/live/xn--e6q212bhn0c.xn--6qq986b3xl/privkey.pem;
 
    # ssl 相关配置
    ssl_session_cache shared:SSL:1m;
    ssl_session_timeout 5m;
    ssl_ciphers ECDHE-RSA-AES128-GCM-SHA256:ECDHE:ECDH:AES:HIGH:!NULL:!aNULL:!MD5:!ADH:!RC4;
    ssl_protocols TLSv1.1 TLSv1.2 TLSv1.3;
    ssl_prefer_server_ciphers on;

    location / {                # 网站根目录
        root	/usr/share/nginx/html;
        index   index.html index.htm;
    }

    location /down {            # 文档根目录
        alias   /usr/share/nginx/down;
        charset utf-8;              # 文档编码
        autoindex on;               # 自动索引
	    autoindex_exact_size off;   # 关闭计算文件确切大小
        autoindex_localtime on;     # 显示本机时间而非 GMT 时间
        sendfile on;                # 高效传输，零拷贝

        # 鉴权
        auth_basic_user_file /usr/share/nginx/htpwd;
    }

    error_page  404               /404.html;
    error_page   500 502 503 504  /50x.html; # 错误页面
    location = /50x.html {
        root   /usr/share/nginx/html;
    }
}
```

<br>

---

## 获取 SSL 证书

参考：

[为没有80、443端口的域名申请SSL证书](https://www.fisheryung.top:9002/%E4%B8%BA%E6%B2%A1%E6%9C%8980%E3%80%81443%E7%AB%AF%E5%8F%A3%E7%9A%84%E5%9F%9F%E5%90%8D%E7%94%B3%E8%AF%B7ssl%E8%AF%81%E4%B9%A6.html)

[阿里云：Nginx或Tengine服务器配置SSL证书](https://help.aliyun.com/zh/ssl-certificate/user-guide/install-ssl-certificates-on-nginx-servers-or-tengine-servers)

1. 下载 `certbot`

    ```bash
    sudo snap install --classic certbot
    sudo ln -s /snap/bin/certbot /usr/bin/certbot
    ```

2. 申请

    ```bash
    sudo certbot certonly --preferred-challenges dns -d "dxlcq.cn" --manual --cert-name dxlcq.cn
    ```

    * 此时会让你，给你的域名，添加一个txt解析
    * 域名是带前缀的，看仔细咯
    * 输出证书保存的位置

<br>

---

## 站点加密


`sudo apt install apache2-utils`

`htpasswd -c /home/admin/htpwd admin`



<br>

---


## For Docker

启动脚本：`runNginx.sh`

```bash
sudo docker run \
-p 80:80 \
-p 1314:1314 \
--name nginx \
-v /.../site/:/usr/share/nginx/html \
-v /.../doc/:/usr/share/nginx/down \
-v /.../htpwd:/usr/share/nginx/htpwd \
-v /.../NGINX/:/etc/nginx/conf.d \
-v /usr/share/zoneinfo/Asia/Shanghai:/etc/localtime \
-v /etc/letsencrypt/live/xn--e6q212bhn0c.xn--6qq986b3xl/fullchain.pem:/etc/letsencrypt/live/xn--e6q212bhn0c.xn--6qq986b3xl/fullchain.pem \
-v /etc/letsencrypt/live/xn--e6q212bhn0c.xn--6qq986b3xl/privkey.pem:/etc/letsencrypt/live/xn--e6q212bhn0c.xn--6qq986b3xl/privkey.pem \
--restart unless-stopped \
-d nginx:latest
```

热重载配置文件：`sudo docker exec [CONTAINER ID] nginx -s reload`



**反向代理（自用）**

1. `sudo apt install nginx`

2. `/etc/nginx/conf.d` 下添加配置文件 `reverse.conf`

3. SSL 证书

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

    * 查看证书剩余时长 `certbot certificates`

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

    location /.well-known { # 用于验证域名所有权
        root /;
    }

    resolver 8.8.8.8 valid=6s;  # dns 解析 6 秒刷新一次

    location / {            # 反向代理到后端服务器
        proxy_pass http://xxxxxxx;                     # 后端服务器地址和端口
        proxy_set_header Host $host;                                # 保持主机头不变
        proxy_set_header X-Forwarded-Proto $scheme;                 # 转发协议
    }
}
```