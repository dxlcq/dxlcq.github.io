## 参考

* [In Search of an Understandable Consensus Algorithm](https://www.usenix.org/system/files/conference/atc14/atc14-paper-ongaro.pdf)

* [In Search of an Understandable Consensus Algorithm 译文](https://arthurchiao.art/blog/raft-paper-zh/)

<br>

---

## 引子

> 单台服务器的性能是有限的，而多台服务器的性能与钱包呈正相关性。

广为人知且经典的分布式系统是 `DNS`。

* `ip`

    在互联网早期，直接通过 `ip` 进行通信，当 `ip` 数量增多时，谁还能记得这个 `IP` 后面是漂亮妹妹还是美丽姐姐？

    于是乎，有了像电话簿一样的 `hosts` 文件：

* `hosts` 文件

    ```hosts
    1.1.1.1     Desktop_Dragon
    ```

    当 `Desktop_Dragon` 的 `ip` 发生变化时，修改一下 `hosts` 文件即可。

    当联系人过多，事情就变得复杂了。

* `DNS`

    首先分析 `hosts` 文件的问题：

    1. 命名冲突：世界上可能存在多个 `Desktop_Dragon`；

    2. 难以维护：`Desktop_Dragon` 的 `ip` 发生变化时，需要告知所有电脑，这是不现实的。

    如何解决？

    1. 引入域名 + 充值，`Desktop_Dragon` 变成 `wwww.Desktop_Dragon.com`。

    2. 分层设计：

        * 权威服务器：主要负责维护域名与 `ip` 的映射关系。

        * 递归服务器：负责查询权威服务器，缓存域名与 `ip` 的映射关系，如果超过 `TTL`，则重新查询权威服务器。


> 值得一提，以 `8.8.8.8` 为例，`8.8.8.8` 本身如何做到高可用？[Anycast](https://www.cloudflare.com/zh-cn/learning/cdn/glossary/anycast-network/)

<br>

---

## CAP

一个分布式系统最多只能同时满足一致性（Consistency）、可用性（Availability）和分区容错性（Partition tolerance）这三项中的两项。

* 容错性：一台机器挂了，不影响整个系统。因此数据需要多台机器存储。

* 一致性：多台机器存储数据，如何保证数据一致性？

* 可用性：通过聪明的操作，保证数据一致性，但如何保证性能？

