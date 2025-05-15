[github](https://github.com/coturn/coturn)

[测试](https://webrtc.github.io/samples/src/content/peerconnection/trickle-ice/)

[docker搭建](https://blog.csdn.net/yjkhtddx/article/details/110117862)


## STUN 

* Session Traversal Utilities for NAT，用于 NAT 的会话穿越协议
* 功能: STUN 协议用于帮助客户端确定其在 NAT 环境中的公共 IP 地址和端口，这对于穿越 NAT 或防火墙并建立对等连接是必要的
* 原理: 客户端向 STUN 服务器发送请求，STUN 服务器返回客户端的公共 IP 地址和端口。客户端然后使用这些信息与其他客户端建立连接

## TURN

* Traversal Using Relays around NAT，使用中继服务器绕过 NAT
* 功能: TURN 协议在 STUN 无法直接建立对等连接时，提供了一个中继服务，它允许客户端将其数据通过 TURN 服务器中继到其他客户端，从而避免 NAT 或防火墙阻塞
* 原理: 客户端连接到 TURN 服务器，TURN 服务器分配一个公共 IP 地址和端口，客户端将数据发送到 TURN 服务器，TURN 服务器再将数据转发到目标客户端


简单来说，STUN 是用来帮助发现和配置 NAT 环境的，而 TURN 则是在 STUN 无法建立直接连接时提供数据中继服务






