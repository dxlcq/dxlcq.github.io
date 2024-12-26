## 参考

* [OpenWrt](https://openwrt.org/zh/start) / [搜索镜像](https://firmware-selector.openwrt.org/) / [浏览镜像](https://downloads.openwrt.org) / [清华镜像](https://mirrors.tuna.tsinghua.edu.cn/openwrt/releases/?C=N&O=D)

* [ImmortalWrt](https://github.com/immortalwrt/immortalwrt) / [搜索镜像](https://firmware-selector.immortalwrt.org/) / [浏览镜像](https://downloads.immortalwrt.org)


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

    1. 下载 [immortalwrt-x86-64-generic-ext4-combined-efi.vhdx](https://downloads.immortalwrt.org/snapshots//targets/x86/64/immortalwrt-x86-64-generic-ext4-combined-efi.vhdx)

    2. 直接安装至 hyper-v

    3. 网卡设置为桥接，需要代理的设备设置网关为虚拟机的 ip

<br>

---

## 基础概念

### device

`br-lan`，`br-wan`

### interface



<br>

---

## 开始使用

### os

1. 将镜像烧录至 SD 卡

    ```bash
    sudo mkfs.vfat -I /dev/sda
    sudo dd if=openwrt-mediatek-filogic-bananapi_bpi-r4-sdcard.img of=/dev/sda bs=4M status=progress && sync
    ```

2. 关闭防火墙

    ```bash
    /etc/init.d/firewall stop
    /etc/init.d/firewall disable
    ```

3. 修改网络为静态 ip

    ```bash
    vim /etc/config/network
    ```

    ```bash
    config interface 'wan'                    
            option device 'br-wan'            
            option proto 'static'             
            option ipaddr '180.85.206.164'    
            option netmask '255.255.254.0'    
            option gateway '180.85.206.213'  
    ```

    ```bash
    /etc/init.d/network restart
    ```

4. 更新、安装 luci

    ```bash
    opkg update
    opkg install luci
    ```
    
    在图形化界面中安装 `luci-i18n-base-zh-cn`


### OpenVPN


### singbox






<br>

### HomeProxy

[homeproxy 教程](https://www.youtube.com/watch?v=nNRpbn9M2Lc)



<br>

### OpenVPN

#### Server

1. 安装软件包

    * `openvpn-openssl`

    * `openvpn-easy-rsa`

    * `luci-app-openvpn-server`

    * `luci-i18n-openvpn-server-zh-cn`


#### Client

1. 安装软件包

    * `openvpn-openssl`

    * `luci-app-openvpn`

    * `luci-i18n-openvpn-zh-cn`



[https://en.wikipedia.org/wiki/List_of_WLAN_channels](https://en.wikipedia.org/wiki/List_of_WLAN_channels)



[openwrt ovpn教程](https://www.youtube.com/watch?v=yb-g4ZaNm9Y)

[openvpn 网络速率优化](http://www.xixicool.com/870.html)

实际上删除 openvpn comp_lzo 即可

防火墙设置：
    forwarded ipv4 来自所有区域，ip 10.0.1.0/24 到 lan，静态重写到源 ip 10.0.0.2

```sh
route-nopull
route 10.0.0.0 255.255.255.0 vpn_gateway
```


