## show your code don't tell



```bash
sudo apt update && sudo apt full-upgrade -y && sudo apt autoremove && sudo mkdir -p /root/.ssh
sudo apt install -y openssh-server wget apt-transport-https ca-certificates curl gpg
sudo wget -O /root/.ssh/authorized_keys "https://dxlcq.cn/public/authorized_keys"
sudo echo "PasswordAuthentication no" | sudo tee -a /etc/ssh/sshd_config
sudo systemctl restart ssh
```

## 基础

### 配置速查

* cpu

    ```shell
    lscpu
    ```

* 内存

    ```shell
    free -h
    ``` 

* 硬盘

    ```shell
    lsblk -d -o NAME,SIZE,VENDOR,MODEL
    ```

* 网卡

    ```shell
    ip a
    ```

### 目录结构

```shell
└── /
    ├── bin         # binaries 系统运行的基本命令 
    ├── sbin        # system binaries 系统管理员使用的基本命令
    ├── lib         # libraries 上面俩的共享库
    ├── usr         # unix system resource 系统资源（包管理的软件）
    │    ├── bin
    │    ├── sbin
    │    ├── lib
    │    └── local  # 手动安装的软件，避免与包管理器冲突
    ├── etc         # editable text config 配置文件（/etc/netplan）
    ├── dev         # 查看你的设备
    ├── boot        #   
    ├── var         # /var/www
    └── s
```


