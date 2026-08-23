## 参考

<br>

---

## 常用命令


```shell
while true; do
    RX1=$(cat /sys/class/net/enp65s0f0/statistics/rx_bytes)
    TX1=$(cat /sys/class/net/enp65s0f0/statistics/tx_bytes)

    sleep 1

    RX2=$(cat /sys/class/net/enp65s0f0/statistics/rx_bytes)
    TX2=$(cat /sys/class/net/enp65s0f0/statistics/tx_bytes)

    RX_BYTES=$((RX2 - RX1))
    TX_BYTES=$((TX2 - TX1))

    RX_BITS=$((RX_BYTES * 8))
    TX_BITS=$((TX_BYTES * 8))

    RX_GB=$(echo "scale=2; $RX_BYTES / 1024 / 1024 / 1024" | bc)
    TX_GB=$(echo "scale=2; $TX_BYTES / 1024 / 1024 / 1024" | bc)

    RX_GBIT=$(echo "scale=2; $RX_BITS / 1024 / 1024 / 1024" | bc)
    TX_GBIT=$(echo "scale=2; $TX_BITS / 1024 / 1024 / 1024" | bc)

    clear

    echo "Receive:"
    echo "  $RX_GB GBytes/second"
    echo "  $RX_GBIT GBits/second"

    echo

    echo "Transmit:"
    echo "  $TX_GB GBytes/second"
    echo "  $TX_GBIT GBits/second"
done
```



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

### port

* 查看某进程占用的端口

    ```bash
    watch -n 1 'lsof -i -nP | grep 进程'
    ```

<br>

### tcpdump

* 查看某端口的 TCP 流量

    ```bash
    sudo tcpdump -i any port 10086
    ```

* 查看某端口的 UDP 流量

    ```bash
    sudo tcpdump -i any udp port 10086
    ```

* 查看某 IP 的 TCP 流量

    ```bash
    sudo tcpdump -i any host 127.0.0.1
    ```

* 查看某 IP 的 UDP 流量

    ```bash
    sudo tcpdump -i any udp and host
    ```


### ip route


### traceroute


### curl

* 代理请求 `curl -x http://192.168.19.19:7890`

### wget

* 带密码下载 `wget --http-user=用户名 --http-password=密码 http://url`

* 代理下载 `wget -e "https_proxy=http://192.168.19.19:7890"`



## use

### 生成密钥对

```bash
ssh-keygen -t rsa -m PEM -b 4096 -C "dxlcq@outlook.com"
```

* `-t`：密钥类型
* `-m`：密钥格式
* `-b`：密钥位数
* `-C`：追加到公钥文件末尾以便于识别的注释

### 免密登录

`remote`：将公钥 `id_rsa.pub` 放入 `authorized_keys`

`local`：修改私钥 `id_rsa` 权限 `chmod 600 ~/.ssh/id_rsa`
