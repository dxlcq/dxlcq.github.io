# Maximum Transmission Unit

参考：

* [华为：什么是 MTU](https://info.support.huawei.com/info-finder/encyclopedia/zh/MTU.html)

* [锐捷：MTU 是什么](https://www.ruijie.com.cn/jszl/90149/)

* [cloudflare：什么是 MTU](https://www.cloudflare.com/zh-cn/learning/network-layer/what-is-mtu/)

> MTU 定义并不唯一，我个人倾向于 **IP MTU**，即 [以太网帧](./ethernet.md#ethernet-ii-framing) 中的有效载荷

> 下文所有的 MTU == **IP MTU**，单位均为 byte（8 bit）


<br>

---

## 1480

中间有一个 [PPPoE](./pppoe.md)，据说还会出现二次拨号

<center>

| 目标 MAC  | 源 MAC  | 以太类型 | PPPoE | 二次拨号 | MTU | 帧检验序列 |
|:-:|:-:|:-:|:-:|:-:|:-:|:-:|
| 6 | 6 | 2 | **8** | **12** | **1480** | 4 |

以太网帧：1518

</center>

<br>

---

## 1492

中间有一个 [PPPoE](./pppoe.md)，其介于以太网和 IP 之间，大小为 8

<center>

| 目标 MAC  | 源 MAC  | 以太类型 | PPPoE | MTU | 帧检验序列 |
|:-:|:-:|:-:|:-:|:-:|:-:|
| 6 | 6 | 2 | **8** | **1492** | 4 |

以太网帧：1518

</center>

<br>

---

## 1500

最正常的 MTU，如果都这样定是极好的

<center>

| 目标 MAC  | 源 MAC  | 以太类型 | MTU | 帧检验序列 |
|:-:|:-:|:-:|:-:|:-:|
| 6 | 6 | 2 | **1500** | 4 |

以太网帧：1518

</center>

<br>

---

## 1518

以太网帧的大小为 1518，MTU 仍然为 1500