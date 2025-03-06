## 参考

* [硬核翻墙系列](https://www.youtube.com/playlist?list=PLqybz7NWybwUgR-S6m78tfd-lV4sBvGFG) 扫盲

* 机场 [赔钱](https://xn--mes358aby2apfg.com/#/register?code=00VpsSlX) / [飞鸟](https://feiniaoyun.top/#/register?code=MfZSDsfM) / [魔戒](https://mojie.me/#/register?code=H6CrDt7x)




<br>

---

## openwrt

* [OpenWrt](https://openwrt.org/zh/start) / [搜索镜像](https://firmware-selector.openwrt.org/) / [浏览镜像](https://downloads.openwrt.org) / [清华镜像](https://mirrors.tuna.tsinghua.edu.cn/openwrt/releases/?C=N&O=D)

* [ImmortalWrt](https://github.com/immortalwrt/immortalwrt) / [搜索镜像](https://firmware-selector.immortalwrt.org/) / [浏览镜像](https://downloads.immortalwrt.org) / [北大镜像](https://mirrors.pku.edu.cn/immortalwrt/releases/)


```
src/gz openwrt_core https://downloads.openwrt.org/releases/24.10.0-rc5/targets/mediatek/filogic/packages
src/gz openwrt_base https://downloads.openwrt.org/releases/24.10.0-rc5/packages/aarch64_cortex-a53/base
src/gz openwrt_kmods https://downloads.openwrt.org/releases/24.10.0-rc5/targets/mediatek/filogic/kmods/6.6.69-1-83c6d4e14f7353564d3cadaf38a15bef
src/gz openwrt_luci https://downloads.openwrt.org/releases/24.10.0-rc5/packages/aarch64_cortex-a53/luci
src/gz openwrt_packages https://downloads.openwrt.org/releases/24.10.0-rc5/packages/aarch64_cortex-a53/packages
src/gz openwrt_routing https://downloads.openwrt.org/releases/24.10.0-rc5/packages/aarch64_cortex-a53/routing
src/gz openwrt_telephony https://downloads.openwrt.org/releases/24.10.0-rc5/packages/aarch64_cortex-a53/telephony
```

```
src/gz immortalwrt_core https://mirrors.vsean.net/openwrt/releases/24.10.0-rc3/targets/mediatek/filogic/packages
src/gz immortalwrt_base https://mirrors.vsean.net/openwrt/releases/24.10.0-rc3/packages/aarch64_cortex-a53/base
src/gz immortalwrt_kmods https://mirrors.vsean.net/openwrt/releases/24.10.0-rc3/targets/mediatek/filogic/kmods/6.6.67-1-cde7aa5ae483611d69bd37bac0c68bf8
src/gz immortalwrt_luci https://mirrors.vsean.net/openwrt/releases/24.10.0-rc3/packages/aarch64_cortex-a53/luci
src/gz immortalwrt_packages https://mirrors.vsean.net/openwrt/releases/24.10.0-rc3/packages/aarch64_cortex-a53/packages
src/gz immortalwrt_routing https://mirrors.vsean.net/openwrt/releases/24.10.0-rc3/packages/aarch64_cortex-a53/routing
src/gz immortalwrt_telephony https://mirrors.vsean.net/openwrt/releases/24.10.0-rc3/packages/aarch64_cortex-a53/telephony
```

<br>

---


<div class="container"> 🛩
    <div class="item">
        <a href="https://www.duyaoss.com/archives/3/" target="_blank"> 机场测速 </a> 
    </div>
    <div class="item">
        <a href="https://xn--mes358aby2apfg.com/#/register?code=00VpsSlX" target="_blank"> 赔钱机场 </a> 
    </div>
    <div class="item">
        <a href="https://feiniaoyun.top/#/register?code=MfZSDsfM" target="_blank"> 飞鸟云 </a> 
    </div>
    <div class="item">
        <a href="https://mojie.me/#/register?code=H6CrDt7x" target="_blank"> 魔戒 </a> 
    </div>
</div>


<br>

---


## 我的设备


### FriendlyElec NanoPi Zero2

> 可能是 2024 年最小的 **无线** 路由器了

* [文档](https://wiki.friendlyelec.com/wiki/index.php/Main_Page)

### Banana Pi BPI-R4

> **wifi7 + 双10G**，可能是 2024 年最强的无线路由器了

* [文档](https://docs.banana-pi.org/zh/home) / [论坛](https://forum.banana-pi.org/)

### x86_64

> 抛开无线，无疑无敌

* 一种无需额外硬件的最佳 OpenWrt 安装方法

    1. 下载 [immortalwrt-x86-64-generic-ext4-combined-efi.vhdx](https://downloads.immortalwrt.org/snapshots/targets/x86/64/)

    2. 直接安装至 hyper-v

    3. 网卡设置为桥接，需要代理的设备设置网关为虚拟机的 ip

<br>

---

## 开始使用

### cfdisk

1. 看看分区

    ```bash
    ls /dev/
    fdisk /dev/mmcblk0
    ```

2. 切换到 `Free Space`

    `New` -> `Primary` -> `Enter` -> `Write` -> `yes` -> `Quit`

    这时候我生成了一个新的分区 `/dev/mmcblk0p8`

3. 格式化

    ```bash
    mkfs.ext4 /dev/mmcblk0p8
    ```

4. 在 `web` -> `System` -> `Mount Points`

    生成配置 -> 选择刚才的分区 -> 启用 -> 挂载点 `/` -> 保存

5. 保存，执行刚才生成的命令

    **注意！！！`/dev/sda1` 改为 `/dev/mmcblk0p8`**

    ```bash
    mount /dev/mmcblk0p8 /mnt
    ```

    重启




### interface

* `terminal`
    
    按需修改 ip

    ```bash
    vim /etc/config/network
    ```
    
    ```network
    config interface 'wan'
        option device 'br-wan'
        option proto 'static'
        option ipaddr '192.168.1.2'
        option netmask '255.255.255.0'
        option gateway '192.168.1.1'
    ```

    ```bash
    /etc/init.d/network restart
    ```

    如果修改之后无法连接，则需要关闭防火墙

    ```bash
    /etc/init.d/firewall stop
    # /etc/init.d/firewall disable
    ```

#### br-lan

1. IP 地址

2. 使用自定义的 DNS 服务器

#### br-wan

1. DHCP 客户端

<br>

---

### device

#### br-lan

1. 禁用 IPv6

#### br-wan

1. 禁用 IPv6


<br>

---

### luci

```bash
opkg update
opkg install luci
opkg install luci-i18n-base-zh-cn
```

<br>

---


### HomeProxy

[homeproxy 教程](https://www.youtube.com/watch?v=nNRpbn9M2Lc)

安装包位置：

* `/immortalwrt/releases` `/packages-版本` `/在 opkg 中看架构` `/luci`

* `/immortalwrt/releases` `/版本/packages` `/在 opkg 中看架构` `/luci`



<br>

---

### OpenVPN

#### Server

1. 安装软件包

    * `openvpn-openssl`

    * `openvpn-easy-rsa`

    * `luci-app-openvpn-server` **仅使用 terminal 下载这一个，前两个自动下**

    * `luci-i18n-openvpn-server-zh-cn`

2. 添加 NAT 规则

    * `ovpn_server`
    
        Forwarded `IPv4`；来自 `所有区域`，IP `10.0.1.0/24`；到 `所有区域`；自动重写源 IP

3. `/etc/config/openvpn`

    ```bash
    config openvpn 'myvpn'
        option enabled '1'
        option proto 'tcp-server'
        option port '1194'
        option ddns 'dxlcq.com'
        option dev 'tun'
        option topology 'subnet'
        option server '10.0.1.0 255.255.255.0'
        option comp_lzo 'no'
        option ca '/etc/openvpn/pki/ca.crt'
        option dh '/etc/openvpn/pki/dh.pem'
        option cert '/etc/openvpn/pki/server.crt'
        option key '/etc/openvpn/pki/server.key'
        option persist_key '1'
        option persist_tun '1'
        option user 'nobody'
        option group 'nogroup'
        option max_clients '10'
        option keepalive '10 120'
        option verb '3'
        option status '/var/log/openvpn_status.log'
        option log '/tmp/openvpn.log'
        option duplicate_cn '1'
        option client_to_client 
        list push 'comp-lzo no'
        list push 'redirect-gateway def1 bypass-dhcp'
        list push 'route 10.0.0.0 255.255.255.0'
        list push 'dhcp-option DNS 10.0.0.1'
    ```

#### Client

1. 安装软件包

    * `openvpn-openssl`

    * `luci-app-openvpn`

    * `luci-i18n-openvpn-zh-cn`

2. 添加 NAT 规则

    * `ovpn_client`

        Forwarded `IPv4`；来自 `所有区域`；到 `所有区域`，IP `10.0.0.0/24`；自动重写源 IP

3. 在 `.ovpn` 文件中添加，只有特定网络流量通过 vpn

    ```ovpn
    route-nopull
    route 10.0.0.0 255.255.255.0 vpn_gateway
    ```

<br>

---


### firewall

#### NAT

* 如需要平级设备通过此设备（旁路由）上网，添加 `NAT` 规则

    * 以 `cqu` 为例

        Forwarded `IPv4`；来自 `所有区域`，IP `180.85.206.0/24`；到 `所有区域`；自动重写源 IP

        Forwarded `IPv4`；来自 `所有区域`；到 `所有区域`，IP `180.85.206.0/24`；自动重写源 IP

<br>

---


[https://en.wikipedia.org/wiki/List_of_WLAN_channels](https://en.wikipedia.org/wiki/List_of_WLAN_channels)

[openwrt ovpn教程](https://www.youtube.com/watch?v=yb-g4ZaNm9Y)

[openvpn 网络速率优化](http://www.xixicool.com/870.html)



## 路由器


**WAN**

* `PPPoE`

    1. 光猫改桥接，默认模式拨号

**LAN**

* `DHCPv4` 

    1. `DNS` 与网关 `10.0.0.3`

    2. 地址范围

        * 保留 `.2 - .100`

        * 动态 `.101 - .200` `DHCP`

        * 隔离 `.201 - .254`

* `static IP`

    * 长期 `.1 - .20`

    * 短期 `.21 - .100`


**定时重启**

* 每天 `2:00`，重新上电 POE

* 每天 `2:20`，本机清理

* 每天 `2:40`，射频调优

* 每天 `3:00`，设备重启


**安全管理**

* `ARP` 防护

* 攻击防护

**VPN-PPTP**

* [L2TP VPN 企业应用配置实例](https://smb.tp-link.com.cn/service/detail_article_4464.html)

* 创建 IP 地址池

    * `10.0.2.2 - 10.0.2.10`

* 创建用户

    * 本地地址 `10.0.2.1`

    * 设置用户名密码

* 创建 l2tp 服务

    * 设置预共享密钥








**端口映射**

非必要不做端口映射，尽量使用 `VPN`

<center>

| 设备 | IP | 外部端口 | 内部端口 |
|:-:|:-:|:-:|:-:|
| 网站 | 10.0.0.6 | 2025 | 2025 |

</center>

**DDNS**

* TP-Link（更新很快，但解析效果不行）

* 科迈（解析效果很好，但是更新很慢）

**网络唤醒**

* windows 关闭 `快速启动`

**云管理-TP商云**

> 当 `VPN` 失效时的唯一管理手段