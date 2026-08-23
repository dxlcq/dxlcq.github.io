## 文件

### 文件查找

find，grep

<br>

### 文件大小

* **`du -h --max-depth=1`** 查看当前目录下各文件和文件夹的大小



### 文件管理

* **`rsync` 高效复制**

    ```bash
    rsync -avhP /source/dir /destination/dir
    rsync -avhP /source/dir user@remote:/destination/dir
    ```

    * `-a` 归档模式，保留文件属性
    * `-v` 详细输出
    * `-h` 以人类可读的格式显示文件大小
    * `-P` 显示进度条，并支持断点续传
    

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

---





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
        /mnt/nfs *(rw,async,no_subtree_check,all_squash,insecure)
        ```

        > 服务端不要自己添加文件，客户端无法访问
        >
        > 此配置下，所有用户（nobody）都可以访问共享目录
        > 
        > `rw` 读写权限
        >
        > `async` 异步写入
        >
        > `no_subtree_check` 禁止子目录检查
        >
        > `all_squash` 所有用户都映射为 nobody 用户
        >
        > `insecure` 允许非特权端口访问

    * `sudo chown nobody:nogroup /mnt/nfs -R`
    
    * `sudo chmod 700 /mnt/nfs -R`

3. 重启nfs `sudo systemctl restart nfs-kernel-server`

### NFS 客户端

1. 下载 `sudo apt install nfs-common`

    ```
    service rpcbind start
    service nfs-common start
    ```

2. 挂载 `sudo mount 10.0.0.15:/mnt/nfs /mnt/nfs`

3. 持久化

    ```bash
    10.0.0.15:/mnt/nfs /mnt/nfs nfs nfsvers=4.1,noresvport 0 0
    ```

* 强行卸载

    ```bash
    sudo umount -f -l /mnt/nfs
    ```

* 测试

    ```bash
    sudo docker run --rm -it --privileged ubuntu:latest bash -c "
        export DEBIAN_FRONTEND=noninteractive &&
        ln -fs /usr/share/zoneinfo/Asia/Shanghai /etc/localtime &&
        apt update && apt install -y nfs-common && mkdir -p /mnt/nfs &&
        mount -t nfs 10.0.0.15:/mnt/nfs /mnt/nfs &&
        ls -la /mnt/nfs"
    ```

<br>

---