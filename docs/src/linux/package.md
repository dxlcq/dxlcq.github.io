
## 软件

### package manager

Debian 系: `ubuntu` `kylinOS` `Deepin` `UOS Desktop`

> 镜像站点: `https://mirrors.aliyun.com/debian/pool/main/`

* dpkg / apt

    ```shell
    dpkg -i *.deb       # i: install
    apt install ./*.deb
    ```

<br>

RedHat 系: `centos` `UOS Server`

> 镜像站点: `https://mirrors.aliyun.com/centos/7/os/x86_64/Packages`

* rpm / yum / dnf (yum 的升级版)

    ```shell
    rpm -ivh *.rpm      # i: install  v: verbose  h: hash
    yum install ./*.rpm
    ```

### apt

参考：[apt 终极指南](https://itsfoss.com/apt-command-guide/)

* 更新软件源、软件，自动删除无关依赖

    ```bash
    sudo apt update && sudo apt full-upgrade && sudo apt autoremove
    ```

* 使用代理

    ```bash
    -o Acquire::http::proxy="http://192.168.19.19:7890/"
    ```

* 删除软件

    ```bash
    sudo apt purge 软件名
    ```

* 查找软件

    ```bash
    sudo apt-cache search 软件名
    ```

* 查看已安装的软件

    ```bash
    sudo apt list --installed | grep 软件名
    ```

* 只下载不安装

    ```bash
    sudo apt install --download-only 软件名
    ```

    > 下载的软件包会保存在 `/var/cache/apt/archives`
    > 
    > 全部安装 `sudo dpkg -i *.deb`
    > 
    > 清理下载的软件包 `sudo apt clean`

* 添加软件源


* 查看软件源


* 删除软件源

<br>


## remote desktop

### other -> linux

直接使用微软的远程桌面协议（RDP）

1. 下载 `sudo apt install xrdp`

2. 打开端口 `sudo ufw allow 3389`

### linux -> other

1. `sudo apt install freerdp2-x11`

2. `xfreerdp /v:10.0.0.6 /u:root /p:password`