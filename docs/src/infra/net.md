## 参考

* [华为 IP 知识百科](https://info.support.huawei.com/info-finder/encyclopedia/zh/index.html)
* [华为 IP 报文格式大全](https://support.huawei.com/enterprise/zh/doc/EDOC1100174722)
* [cloudflare 学习中心](https://www.cloudflare.com/zh-cn/learning/)
* [以太网帧](https://en.wikipedia.org/wiki/Ethernet_frame)
* [华为：什么是 MTU](https://info.support.huawei.com/info-finder/encyclopedia/zh/MTU.html)
* [锐捷：MTU 是什么](https://www.ruijie.com.cn/jszl/90149/)
* [cloudflare：什么是 MTU](https://www.cloudflare.com/zh-cn/learning/network-layer/what-is-mtu/)

> MTU 定义并不唯一, 我个人倾向于 **IP MTU**, 即 [以太网帧](#ethernet-ii-framing) 中的有效载荷

> 下文所有的 MTU == **IP MTU**, 单位均为 byte (8 bit)


<br>

---

## AS 号码

```shell
# 检测服务器回程脚本
curl https://raw.githubusercontent.com/zhucaidan/mtr_trace/main/mtr_trace.sh|bash
```

**电信**

* `AS4809` `59.43.x.x` `CN2` 中国电信下一代承载网

    * 👍 `CN2 GIA` 全程走 `CN2`

    * `CN2 GT` 只有出口走 `CN2`

* 🥵 `AS4134` `202.97.x.x` 163 骨干网

**联通**

* 👍 `AS9929` `CU VIP` 联通A网

* `AS10099` 出口

* 🥵 `AS4837`  169 网


**教育网**

* `AS4538` `202.112.x.x` 教育网骨干网

<br>

---

## 各种网络

* LAN (局域网)
    
    * 以太网 (Ethernet, 802.3)协议是有线 LAN 的标准

    * 太牛逼了, 几乎取代了所有有线局域网标准

* WAN (广域网)
    
* MAN (城域网)

* WLAN (无线局域网)
    
    * Wi-Fi 是基于 802.11 标准的无线网络技术, 广泛用于实现 WLAN
    
    * [不同的 Wi-Fi 协议和数据速率](https://www.intel.cn/content/www/cn/zh/support/articles/000005725/wireless/legacy-intel-wireless-products.html)

* WWAN (无线广域网)

    * 如 5G (NR)与 4G (LTE) 

* WPAN (无线个域网)

    * 如蓝牙 (之前 802.15.1)


<br>

---

## Ethernet Protocol

是什么

* **以太网协议 (IEEE 802.3)**

* 位于 OSI 模型的数据链路层 (第 2 层) 和物理层 (第 1 层) 

* 在 OSI **数据链路层** 中, 定义了帧的基本结构、MAC 地址等, 以及如何在 **同一网络** 中传输数据等

* 在 OSI **物理层** 中, 定义了传输介质和接口标准, 包括以太网线缆的类型和传输速率

* 常见于交换机, 网卡

不是什么

* 不是 **Ethernet II framing**, 这是一个具体帧格式, **IEEE 802.3** 的具体实现

* 不是 **Wi-Fi (IEEE 802.11)**
    
    > 值得一提, IEEE 802.11 规范了无线局域网的具体帧格式, 这与 IEEE 802.3 不同

<br>

---

## Ethernet II framing


| 目标 MAC 地址 | 源 MAC 地址 | 以太类型 | 有效载荷 | 帧检验序列 |
|:-:|:-:|:-:|:-:|:-:|
| 6 | 6 | 2 | 46-1500 | 4 |


* **目标 MAC 地址**
    * 接收帧的网络适配器的物理地址, 6 个字节 (48 bit) 
    * 当接收到一个以太帧时, 首先会检查该帧的目的地址, 是否与当前适配器的物理地址相同, 相同, 进一步处理, 不同, 直接丢弃

* **源 MAC 地址**
    * 发送帧的网络适配器的物理地址, 6 个字节 (48 bit) 

* **以太类型**
    * 上层协议的类型, 2 个字节 (16 bit) 
    * 由于上层协议众多, 所以在处理数据的时候必须设置该字段, 标识数据交付哪个协议处理

        > 字段为 `0x0800` 时, 将数据交付给 **网络层的 [IP](./ipv4.md)** 协议
    
    * [常见以太类型](https://en.wikipedia.org/wiki/EtherType#Values)

* **有效载荷**
    * 交付给上层的数据, 最小为 46 字节 (不足填充) , 最大为 1500 字节, 最大值也叫最大传输单元 ([MTU](./mtu.md)) 

* **帧检验序列** 
    * FCS, 检测该帧是否出现差错, 4 个字节 (32 bit) 
    * 发送方计算帧的 **循环冗余码校验 (CRC) **, 把这个值写到 FCS 里, 接收方重新计算 CRC, 如果两个值不相同, 则表示传输过程中发生了数据丢失或改变, 此时, 需要重新传输这一帧
        > 网卡在校验正确后, 会丢弃 FCS

<br>

---

## 1480

中间有一个 [PPPoE](./pppoe.md)，据说还会出现二次拨号


| 目标 MAC  | 源 MAC  | 以太类型 | PPPoE | 二次拨号 | MTU | 帧检验序列 |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 6 | 6 | 2 | **8** | **12** | **1480** | 4 |

以太网帧：1518


<br>

---

## 1492

中间有一个 [PPPoE](./pppoe.md)，其介于以太网和 IP 之间，大小为 8


| 目标 MAC  | 源 MAC  | 以太类型 | PPPoE | MTU | 帧检验序列 |
|:-:|:-:|:-:|:-:|:-:|:-:|
| 6 | 6 | 2 | **8** | **1492** | 4 |

以太网帧：1518


<br>

---

## 1500

最正常的 MTU，如果都这样定是极好的


| 目标 MAC  | 源 MAC  | 以太类型 | MTU | 帧检验序列 |
|:-:|:-:|:-:|:-:|:-:|
| 6 | 6 | 2 | **1500** | 4 |

以太网帧：1518


<br>

---

## 1518

以太网帧的大小为 1518，MTU 仍然为 1500