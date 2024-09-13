# Ethernet Protocol

## 是什么

* **以太网协议（IEEE 802.3）**

* 位于 OSI 模型的数据链路层（第 2 层）和物理层（第 1 层）

* 在 OSI **数据链路层** 中，定义了帧的基本结构、MAC 地址等，以及如何在 **同一网络** 中传输数据等

* 在 OSI **物理层** 中，定义了传输介质和接口标准，包括以太网线缆的类型和传输速率

* 常见于交换机，网卡

## 不是什么

* 不是 **Ethernet II framing**，这是一个具体帧格式，**IEEE 802.3** 的具体实现

* 不是 **Wi-Fi（IEEE 802.11）**
    
    > 值得一提，IEEE 802.11 规范了无线局域网的具体帧格式，这与 IEEE 802.3 不同

* 不是 **互联网协议（IP）**



<br>

---

## Ethernet II framing

参考：[以太网帧](https://en.wikipedia.org/wiki/Ethernet_frame)

<center>

| 目标 MAC 地址 | 源 MAC 地址 | 以太类型 | 有效载荷 | 帧检验序列 |
|:-:|:-:|:-:|:-:|:-:|
| 6 | 6 | 2 | 46-1500 | 4 |

</center>

* **目标 MAC 地址**
    * 接收帧的网络适配器的物理地址，6 个字节（48 bit）
    * 当接收到一个以太帧时，首先会检查该帧的目的地址，是否与当前适配器的物理地址相同，相同，进一步处理，不同，直接丢弃

* **源 MAC 地址**
    * 发送帧的网络适配器的物理地址，6 个字节（48 bit）

* **以太类型**
    * 上层协议的类型，2 个字节（16 bit）
    * 由于上层协议众多，所以在处理数据的时候必须设置该字段，标识数据交付哪个协议处理

        > 字段为 `0x0800` 时，将数据交付给 **网络层的 [IP](./ipv4.md)** 协议
    
    * [常见以太类型](https://en.wikipedia.org/wiki/EtherType#Values)

* **有效载荷**
    * 交付给上层的数据，最小为 46 字节（不足填充），最大为 1500 字节，最大值也叫最大传输单元（[MTU](./mtu.md)）

* **帧检验序列** 
    * FCS，检测该帧是否出现差错，4 个字节（32 bit）
    * 发送方计算帧的 **循环冗余码校验（CRC）**，把这个值写到 FCS 里，接收方重新计算 CRC，如果两个值不相同，则表示传输过程中发生了数据丢失或改变，此时，需要重新传输这一帧
        > 网卡在校验正确后，会丢弃 FCS