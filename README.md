个人网站

**如何使用**

1. 安装 `python`

    ```shell
    sudo apt install python3 python3-pip
    ```

2. 安装 `mkdocs` 及 `mkdocs-material`

    ```shell
    python3 -m pip install mkdocs mkdocs-material
    ```

3. 拉取本项目

    ```shell
    git clone https://github.com/dxlcq/dxlcq.github.io.git
    ```

4. 生成

    ```shell
    python3 -m mkdocs build
    ```

5. 生成并提交

    ```shell
    python3 -m mkdocs build && git add . && git commit -m "🥳" && git push
    ```

**服务部署**

1. SSL 证书

    * 首次申请

        ```shell
        sudo snap install --classic certbot
        sudo ln -s /snap/bin/certbot /usr/bin/certbot
        sudo certbot certonly --preferred-challenges dns -d "dxlcq.cn" --manual --cert-name dxlcq.cn
        ```

    * 测试更新

        ```shell
        sudo certbot renew --dry-run
        ```

    * 每 6 天自动更新

        ```shell
        sudo crontab -e
        ```

        ```shell
        0 0 */6 * * sudo certbot renew && sudo docker exec nginx nginx -s reload
        ```

2. `sudo apt install nginx`

3. 添加 `vim /etc/nginx/nginx.conf`

    ```
    include '/var/www/dxlcq.github.io/default.conf';
    ```

4. 重载配置

    ```shell
    sudo nginx -s reload
    ```


**参考**

* [Mkdocs配置文件说明(mkdocs.yml)](https://blog.csdn.net/m0_63203517/article/details/129765689)

* [如何在Mkdocs里自定义字体（霞鹜文楷）](https://blog.csdn.net/m0_63203517/article/details/131946304)

* [Mkdocs Material使用记录](https://shafish.cn/blog/mkdocs/)

* [Material for Mkdocs 個人網站搭建](https://herointene.github.io/tech/mkdocsbuild/)

* [mkdocs教程](https://wcowin.work/tag.html#mkdocs)
