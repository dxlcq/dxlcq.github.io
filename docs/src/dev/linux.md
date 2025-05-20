参考：[Linux 命令大全](https://www.linuxcool.com/)

## for me

```bash
sudo apt update && sudo apt full-upgrade -y && sudo apt autoremove
sudo apt install -y openssh-server wget apt-transport-https ca-certificates curl gpg
sudo wget -O /root/.ssh/authorized_keys "https://dxlcq.cn/public/authorized_keys"
sudo echo "PasswordAuthentication no" | sudo tee -a /etc/ssh/sshd_config
sudo systemctl restart ssh
```

```bash
sudo apt update && sudo apt full-upgrade -y && sudo apt autoremove
sudo apt install -y openssh-server wget apt-transport-https ca-certificates curl gpg
sudo wget -O /home/jiao/.ssh/authorized_keys "https://dxlcq.cn/public/authorized_keys"
sudo systemctl restart ssh
```

## dir

```shell
└── /
    ├── bin     # binaries 系统运行的基本命令 
    ├── sbin    # system binaries 系统管理员使用的基本命令
    ├── lib     # libraries 上面俩的共享库
    ├── usr     # unix system resource 系统资源（包管理的软件）
    │    ├── bin
    │    ├── sbin
    │    ├── lib
    │    └── local  # 手动安装的软件，避免与包管理器冲突
    ├── etc     # editable text config 配置文件（/etc/netplan）
    ├── dev     # 查看你的设备
    ├── boot    #   
    ├── var     # /var/www
    └── s
```

## 软件

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

* 添加软件源


* 查看软件源


* 删除软件源

<br>

### snap

一托

<br>

---


## 文件

### 文件查找

find，grep


<br>

### 文件管理

* **`ls` 查看**

    * `ls -a` 列出全部文件（含隐藏）

    * `ls -l`
        `文件类型[所属人权限][所属组权限][其他人权限] 硬连接数量 所属人 所属组 文件大小 修改 日期和时间 文件名`
        文件类型：
        * `-` 普通文件
        * `d` 目录
        * `l` 软链接
        * `b` 块设备
        * `c` 字符设备
        * `s` 套接字
        * `p` 管道

* **`cd` 切换目录**

* **`pwd` 输出当前目录**

* **`mkdir ` 创建目录**
    * `mkdir -m 711 dir` 创建目录，权限为 `711`
    * `mkdir -p dir/dir/dir` 创建多层目录

* **`cp` 复制文件**
    * `cp -r dir/ dir.bak/` 递归复制
    * `cp -p file file.bak` 同时复制文件属性

* **`mv` 移动文件**
    * 如果移动目录，建议使用 `cp`，确认后再删除
    * `mv dirOld/ dirNew/`，从旧的目录移动到新的目录

* **`rm `删除文件**
    * `rm -r dir/` 递归删除
    * `rm -f dir/` 忽略不存在的文件


<br>

### 文件权限

每个文件有三种粒度

| 所属人 | 所属组 | 其他人 |
|:-:|:-:|:-:|
| `u` | `g` | `o` |

各自有三种权限

| 读 | 写 | 行 |
|:-:|:-:|:-:|
| `r` `4` | `w` `2` | `x` `1` |

修改

* **`chown` 修改所属人 `u`** 

    * `chmod jiao:jiao file` 修改所属人和所属组

* **`chgrp` 修改所属组 `g`**
* **`chmod` 修改权限**

    * `chmod +x`，给 **全部人 `a`** 添加执行权限，等价于 `chmod a+x`

    * `chmod +r`，给 **全部人 `a`** 添加读权限，等价于 `chmod a+r`

    * `chmod +w`，给 **所属人 `u`** 添加写权限，若想给全部人，`chmod a+w`

    <br>

    * `chmod u+x`，给 **所属人** 添加执行权限

    * `chmod g+r`，给 **所属组** 添加读权限

    * `chmod o+w`，给 **其他人** 添加写权限

    <br>

    * `chmod 777`，给 **全部人** 添加全部权限

    * `chmod 755`，给 **所属人** 添加全部权限，给 **所属组** 和 **其他人** 添加读和执行权限

    * `chmod -R`，递归修改


<br>

### 文件解压缩

tar，zip

* **`tar -zxvf *.tar.gz`**
    * `-z` 解压缩（gz）（有时可以省略）
    * `-x` 解包（tar）
    * `-v` 显示详细的解压过程信息
    * `-f` 指定名称
    * `-C` 指定路径

* **`tar -zcvf *.tar.gz *`**
    * `-c` 打包（tar）

<br>

### 文件备份

dump，rsync

<br>

### scp


<br>

---

## 磁盘

### 磁盘管理

### 挂载普通磁盘

**`mount` 磁盘挂载**

* 挂载
    `mount -t ntfs /dev/sda1 /mnt`
    * `-t` 指定文件系统类型
    * `/dev/sda1` 磁盘分区
    * `/mnt` 挂载点

**`umount` 磁盘卸载**

<br>

### SMB 服务端

> samba 是 SMB 的 linux 实现

1. 下载 `sudo apt install samba`

2. 配置共享目录 `chmod 777 /home/user/Public/ -R`

3. 添加samba用户 `sudo smbpasswd -a 用户名`

4. 提示输入密码 x2

5. 配置samba `sudo vim /etc/samba/smb.conf`
    
    ```sh
    [share name]            # 共享名
        path = /home/user/Public/# 共享路径
        writable = yes      # 可写
    ```

6. 重启samba `sudo samba restart`
    
    * 可能还需要重启一下电脑

7. 开启端口 `sudo ufw allow 445`

### SMB 客户端

参考：[系统启动时自动挂载 SMB 共享](https://docs.redhat.com/zh_hans/documentation/red_hat_enterprise_linux/8/html/managing_file_systems/proc_mounting-an-smb-share-automatically-when-the-system-boots_assembly_mounting-an-smb-share-on-red-hat-enterprise-linux)


1. 下载 `sudo apt install cifs-utils`

2. 添加共享条目 `sudo vim /etc/fstab`

    ```conf
    //ip/public /mnt/public cifs credentials=/root/smb.cred,uid=1000,gid=1000,iocharset=utf8 0 0
    ```

    * `//ip/public` 网络路径
    * `/mnt/public` 本地挂载路径
    * `cifs` 文件系统类型
    * `credentials=/root/smb.cred` 指定了一个包含登录凭据（用户名和密码）的文件
    * `uid=1000,gid=1000` 用户和组 ID，确保挂载后的文件权限正确
    * `iocharset=utf8` 设置字符集为 UTF-8，以支持中文等非 ASCII 字符
    * `0 0` 不要进行 dump 备份，启动时不需要检查


3. 创建登陆凭据 `sudo vim /root/smb.cred`

    ```cred
    username=admin
    password=admin
    ```

4. 修改凭据权限 `sudo chmod 600 /root/smb.cred`

5. 重启验证

### NFS 服务端

1. 下载 `sudo apt install nfs-kernel-server`

2. 添加共享目录 

    * `sudo mkdir -p /mnt/nfs`
    
    * `sudo vim /etc/exports`

        ```conf
        /mnt/nfs *(rw,sync,no_subtree_check,all_squash)
        ```

        > 服务端不要自己添加文件，客户端无法访问
        > 此配置下，所有用户（nobody）都可以访问共享目录

    * `sudo chown nobody:nogroup /mnt/nfs -R`
    
    * `sudo chmod 700 /mnt/nfs -R`

3. 重启nfs `sudo systemctl restart nfs-kernel-server`

### NFS 客户端

1. 下载 `sudo apt install nfs-common`

2. 挂载 `sudo mount 10.0.0.1:/mnt/nfs /mnt/nfs`

```
service rpcbind start
service nfs-common start
```

* 强行卸载

```bash
sudo umount -f -l /mnt/nfs
```

<br>

---

## 系统

**`btop`** 状态总览

**`screenfetch`** 配置

### Process


`ps -aux` 查看所有进程

`ps -aux | grep [关键字]` 查看包含关键字的进程

`ps -p [PID]` 查看指定进程

`ps -u [USER]` 查看指定用户的进程

| USER              | PID        | %CPU    | %MEM    | VSZ(KB)      | RSS(KB)      | TTY      | STAT | START | TIME   | COMMAND              |
|-------------------|------------|---------|---------|----------|----------|----------|------|-------|--------|----------------------|
| 进程所有者的用户名 | 进程 ID    | CPU 使用率 | 内存使用率 | 虚拟内存大小 | 常驻内存集大小 | 终端类型 | 进程状态 | 启动时间 | 进程使用的 CPU 时间 | 启动该进程的命令行  |
    
* `STAT`：

    * `S` 睡眠：等待事件（等待 I/O ）

    * `s` 领导：具有子进程

    * `+` 前台进程

    * `R` 运行

    * `l` 多线程，克隆线程

    * `L` 有些页被固定在内存中，不允许交换到磁盘

    * `D` 不可中断的睡眠：等待事件完成（正在进行 I/O ）

    * `Z` 僵尸：进程已经终止，但是父进程还没有回收

`ps -ef` 多了一个 `ppid` 父进程 ID

`ps -ef --forest` 查看进程树

`pstree` 查看进程树

`kill -9 [PID]` 杀死进程，`-9` 是强制杀死

`pkill -9 [进程名]` 杀死进程

`killall -9 [进程名]` 杀死同名进程

<br>

### MEM



<br>

### IO



<br>

### 其他

查看时间 `date`，修改时区

```bash
sudo cp /usr/share/zoneinfo/Asia/Shanghai /etc/localtime
```

校准时间

```bash
sudo date -s "$(wget -S  "https://www.google.com/" 2>&1 | grep -E '^[[:space:]]*[dD]ate:' | sed 's/^[[:space:]]*[dD]ate:[[:space:]]*//' | head -1l | awk '{print $1, $3, $2,  $5 ,"GMT", $4 }' | sed 's/,//')"
```

<br>

---

## 网络

### net

```bash
sudo vi /etc/netplan/00-installer-config.yaml
```

* 静态 IP

```yaml
network:
  ethernets:
      eth0:
        dhcp4: false
        addresses:
          - 10.0.0.2/24
        routes:
          - to: default
            via: 10.0.0.1
        nameservers:
          addresses: [10.0.0.1,8.8.8.8]
  version: 2
```


<br>

### ping


<br>

### traceroute


<br>


### nextroute


<br>

### ip route


**`ip route show` 查看路由表**

- [destination network]
    - **ip/mask**：目标网络，例如 `10.0.1.0/24`
    - **default**：默认路由，用 `"default"` 表示

- `via` [gateway ip]
    - **gateway ip**：经过的网关 IP 地址。如果没有网关，该字段为空。

- `dev` [interface]
    - **interface**：出口接口，通过哪个接口发送数据包（如 `eth0`、`br-lan`、`tun0` 等）

- `proto` [protocol]
    - **static**：静态路由
    - **kernel**：内核路由（系统自动生成）

- `scope` [scope type]
    - **link**：作用范围为本地链路，数据包不会被转发

- `src` [source ip]
    - **source ip**：指定源地址，用于发送到该目标网络的数据包

```bash
# （备份路由）如果没有匹配的路由，就会使用默认路由，从 eth0 发送
default via 180.85.207.254 dev eth0 proto static src 180.85.207.68
# 180.85.206.0/23 是本地网络，通过 eth0 发送
180.85.206.0/23 dev eth0 proto kernel scope link src 180.85.207.68
# DHCP 分配的本地网络，通过 br-lan 发送
10.0.9.0/24 dev br-lan proto kernel scope link src 10.0.9.1

# 所有流量通过 tun0
0.0.0.0/1 via 10.0.1.1 dev tun0
128.0.0.0/1 via 10.0.1.1 dev tun0
# 到达 27.15.165.202 的流量，通过 eth0（对端 VPN 网络的公网 IP）
27.15.165.202 via 180.85.207.254 dev eth0 
# VPN 网络，通过 tun0 发送
10.0.1.0/24 dev tun0 proto kernel scope link src 10.0.1.3
# 到达 10.0.0.0/24（对端网络）的流量，通过 tun0 发送
10.0.0.0/24 via 10.0.1.1 dev tun0

# 到达 10.10.8.162 的流量，通过 eth0 发送
10.10.8.162 via 180.85.207.254 dev eth0 proto static
```


<br>

### iptables


<br>

### curl

* 代理请求 `curl -x http://192.168.19.19:7890`

### wget

* 带密码下载 `wget --http-user=用户名 --http-password=密码 http://url`

* 代理下载 `wget -e "https_proxy=http://192.168.19.19:7890"`


<br>

### nmap

[官方中文文档](https://nmap.org/man/zh/index.html)

`nmap [ <扫描类型> ...] [ <选项> ] { <扫描目标说明> }`

#### nmap 端口状态

##### open（开放的）

应用程序正在监听端口，或者响应一个请求来自已连接的客户端。接收TCP连接或者UDP报文。

##### closed（关闭的）

没有应用程序监听端口。但是此端口可以被探测到，因为没有应用程序监听，所以会返回一个 RST 包或者 ICMP 端口不可达消息。

##### filtered（屏蔽的）

防火墙或者 ACL 屏蔽了端口，所以无法确定端口是否开放。目标端口可能有以下几种情况：
* 未响应，屏蔽器丢弃了探测包，此举会让 nmap 误认为探测包丢失，导致扫描时间变长。
* 丢弃了探测包，但是返回了 ICMP 错误消息。

##### unfiltered（未屏蔽的）

防火墙或者 ACL 没有屏蔽端口，但是 nmap 无法确定端口开放或者关闭。用其它类型的扫描，如窗口扫描，SYN 扫描，或者 FIN 扫描可以帮助确定端口是否开放。

##### open|filtered（开放或者屏蔽的）

开放的端口不响应探测包，屏蔽的端口也不响应探测包。所以无法确定端口是否开放。

##### closed|filtered（关闭或者屏蔽的）

只可能出现在 IPID Idle 扫描中，因为此扫描类型需要发送两个探测包，如果两个探测包都没有响应，那么就无法确定端口是否开放。

---

#### nmap 扫描技术


##### 1 默认扫描

`nmap dxll.love`

默认扫描是 nmap 的最基本的扫描方式，它会扫描 1000 个最常用的端口，扫描方式是 SYN 扫描。

```sh
nmap -T0 dxll.love
nmap -T1 dxll.love
nmap -T2 dxll.love
nmap -T3 dxll.love
nmap -T4 dxll.love
nmap -T5 dxll.love
```

`-T0` 是最慢的扫描方式，`-T5` 是最快的扫描方式，`-T3` 是默认的扫描方式，`-T4` 是常用的扫描方式。

`nmap -6 dxll.love`

开启 IPv6 扫描。

`nmap -v dxll.love`

开启详细模式，显示扫描过程。

`nmap -A dxll.love`

全面扫描，包括 1-10000 端口扫描，服务版本探测，操作系统探测，脚本扫描等。

##### 2 扫描多个 IP

```sh
nmap spacex.com dxll.love   # 扫描多个域名
nmap 192.168.31.100,101,102 # 扫描同一网段的多个 IP，可以用逗号分隔
nmap 192.168.31.*           # 扫描同一网段的多个 IP，可以用通配符
nmap 192.168.31.1/24        # 扫描同一网段的多个 IP，可以用 CIDR 表示法
```

##### 3 扫描指定端口

```sh
nmap -p 80 dxll.love        # 扫描单个端口
nmap -p 80,443 dxll.love    # 扫描多个端口
nmap -p 1-100 dxll.love     # 扫描端口范围
nmap -p-                    # 扫描所有端口 等价于 nmap -p 1-65535
```

##### 4 TCP扫描

###### TCP SYN 扫描

`nmap -sS dxll.love`

此方式不完成 TCP 三次握手，而是发送一个 SYN 包，如果目标端口开放，那么会返回一个 SYN/ACK 包，如果端口关闭，那么会返回一个 RST 包。

###### TCP Connect 扫描

`nmap -sT dxll.love`

此方式完成 TCP 三次握手，如果目标端口开放，那么会返回一个 SYN/ACK 包，如果端口关闭，那么会返回一个 RST 包。
目标主机可能会记录下连接，所以此方式不太隐蔽。

###### TCP 隐秘扫描

如果收到 RST 响应，则端口关闭，否则判定端口开放或被屏蔽。

`nmap -sN dxll.love`

不设置任何标志位。

`nmap -sF dxll.love`

只设置TCP FIN标志位。

`nmap -sX dxll.love`

flags的FIN、URG、PUSH都为1的包。

###### TCP ping 扫描

`nmap -sP dxll.love`

通过发送ICMP Echo请求（也称为Ping请求）到目标主机，命令将检测主机是否响应了请求并返回IP地址。如果主机响应，则表示主机是在线的。在这个扫描中，Nmap只检查是否有响应，而不扫描主机的任何端口。

##### 5 UDP 扫描

`namp -sU dxll.love`

UDP 扫描需要发送 UDP 包，如果目标端口开放，那么会返回一个 ICMP 端口不可达消息，如果端口关闭，那么会返回一个 ICMP 端口不可达消息或者没有响应。


##### 6 路由跟踪

`nmap --traceroute dxll.love`

查出从本地计算机到目标之间所经过的网络节点，并可以看到通过各个节点的时间。

##### 7 操作系统探测

`nmap -O dxll.love`

nmap 会发送一系列的 TCP 和 UDP 包，然后分析返回的包，从而判断目标主机的操作系统。



<br>


### telnet


<br>

### iperf3


<br>

---

## tmux

[终端复用](https://dczcq.cn/note/linux/tmux/)

<br>

---

## 守护进程

[Systemd](https://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-part-two.html)



<br>

---

## 计划作业

`crontab`

* 查看计划作业 `crontab -l`
* 编辑计划作业 `crontab -e`
* 删除计划作业 `crontab -r`

<br>

---

## UFW

* **`ufw enable`** 启动防火墙 
* **`ufw disenable`**  关闭防火墙 
* **`ufw allow 22`** 打开端口
* **`ufw delete allow 22`** 关闭端口
* **`ufw status`** 防火墙状态

<br>

---

## 远程桌面

### other -> linux

直接使用微软的远程桌面协议（RDP）

1. 下载 `sudo apt install xrdp`

2. 打开端口 `sudo ufw allow 3389`

### linux -> other

1. `sudo apt install freerdp2-x11`

2. `xfreerdp /v:10.0.0.6 /u:root /p:password`