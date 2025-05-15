**参考**

* [WebRTC 使用入门](https://web.dev/articles/webrtc-basics?hl=zh-cn#signaling_session_control_network_and_media_information)
* [WebRTC samples](https://webrtc.github.io/samples/)
* [扩展 WebRTC 的 3 种关键方法：SFU、MCU 和 XDN](https://www.red5.net/blog/3-key-approaches-for-scaling-webrtc-sfu-mcu-and-xdn/)

* [WebRTC 基础知识](https://getstream.io/resources/projects/webrtc/basics/)

* [WebRTC 简单教程](https://www.scaledrone.com/blog/webrtc-tutorial-simple-video-chat/)

## offer sdp

> `SDP`（会话描述协议 Session Description Protocol）是描述点对点连接的标准，`SDP` 包含音视频的编解码器、源地址和时序信息

使用 `createOffer()` 创建 `offer sdp`

```json
sdp:
    v=0
    o=- 7093805778388360368 2 IN IP4 127.0.0.1
    s=-
    t=0 0
    a=extmap-allow-mixed
    a=msid-semantic: WMS
type:
    offer
```


* `v`
    * `SDP` 版本号：`0` 表示使用 `SDP` 的第一个版本
* `o`
    * 用户名字段：`-` 表示没有指定用户名
    * 会话的唯一标识符（Session ID）：`7093805778388360368`
    * 会话版本号：`2`，每当会话信息改变时，这个版本号会增加
    * 网络类型：`IN`，表示 `Internet`
    * 地址类型：`IP4` 表示 `IPv4`
    * 本机 `IP` 地址：`127.0.0.1`
* `s`
    * 会话名称: `-` 表示未指定具体名称
* `t`
    * 时间：`0 0` 没有时间限制
* `a`
    * 允许 `RTP` 扩展的混合使用：`extmap-allow-mixed`
    * 标识符语义：`msid-semantic: WMS`，`WMS` 通常是 `WebRTC` 中使用的标识符

<br>

---

## answer sdp



<br>

---

## ice candidate


<br>

---

## signaling

将所有消息无差别转发给所有人

```go
package main

import (
    "log"
    "net/http"
    "github.com/gorilla/websocket"
)

type Message struct {
    Id  string  `json:"id"`
    Type string `json:"type"`
    Sdp string  `json:"sdp"`
    Ice string  `json:"ice"`
}

var cs = make(map[*websocket.Conn]bool)  // 1. 连接的集合

func handleConnection(w http.ResponseWriter, r *http.Request) {
    upgrader := websocket.Upgrader{
        CheckOrigin: func(r *http.Request) bool {
            return true
        },
    }
    conn, err := upgrader.Upgrade(w, r, nil)
    if err != nil {
        log.Println("升级为 websocket 失败:", err)
        return
    }
    cs[conn] = true

    defer conn.Close()          // 连接关闭时删除连接
    log.Println("连接成功:", conn.LocalAddr())

    for {
        var msg Message
        err := conn.ReadJSON(&msg)
        if err != nil {
            log.Println("读取消息失败:", err)
            return
        }

        log.Println("收到消息:", msg.Type)

        for c := range cs {
            if c != conn {
                c.WriteJSON(msg)
            }
        }
    }
}

func main() {
    http.HandleFunc("/", handleConnection)
    http.ListenAndServeTLS(":3002", "/etc/letsencrypt/live/xn--e6q212bhn0c.xn--6qq986b3xl/fullchain.pem", "/etc/letsencrypt/live/xn--e6q212bhn0c.xn--6qq986b3xl/privkey.pem", nil)
}
```

<br>

---

## 1c1s

```js
const signaling = new WebSocket('wss://xn--e6q212bhn0c.xn--6qq986b3xl:3002')            // 信令服务器
let PC = null                                                                           // 连接

signaling.onopen = () => {
    console.log('信令服务器：成功连接！')
    navigator.mediaDevices.getUserMedia({ video: true, audio: true}).then(stream => {   // 1. 获取流
        document.getElementById('local_H').srcObject = stream                           // 2. 将流绑定到标签
        PC = new RTCPeerConnection()                                                    // 3. 创建连接
        PC.onicecandidate = (e) => {                                                    // 4. 发送 ice
            if (e.candidate) {                                                          // 一定，一定，一定要在 new 完 RTCPeerConnection 后马上设置 onicecandidate
                signaling.send(JSON.stringify({
                    type: 'ice',
                    ice: JSON.stringify(e.candidate)
                }))
            }
            console.log('发送 ice candidate', e.candidate)
        }
        stream.getTracks().forEach((track) => PC.addTrack(track, stream))               // 5. 将流添加到连接
        PC.createOffer().then(offer => {                                                // 6. 创建 offer sdp
            PC.setLocalDescription(offer)                                               // 7. 设置本地 sdp
            signaling.send(JSON.stringify(offer))                                       // 8. 发送 offer sdp
            console.log('发送 offer sdp', offer)
        })})
}

signaling.onmessage = async (event) => {                                                // 9. 接收 answer sdp
    const msg = JSON.parse(event.data)                                                  
    if (msg.type === 'answer') {
        console.log('收到 answer sdp', msg)
        PC.setRemoteDescription(msg)                                                    // 10. 设置远程 sdp
    }
}

signaling.onclose = () => {console.log('信令服务器：关闭连接！')}
signaling.onerror = (error) => {console.log('信令服务器：错误连接！', error)}
```

```js
const signaling = new WebSocket('wss://xn--e6q212bhn0c.xn--6qq986b3xl:3002')            // 信令服务器
let PC = null                                                                           // 连接

signaling.onmessage = async (event) => {
    const msg = JSON.parse(event.data)
    if (msg.type === 'offer') {                                                         // 1. 收到 offer sdp
        console.log('收到 offer sdp', msg)
        PC = new RTCPeerConnection()                                                    // 2. 创建连接
        PC.ontrack = (e) => {                                                           // 3. 监听连接上的流
            document.getElementById('remote_H').srcObject = e.streams[0]
        }
        PC.setRemoteDescription(msg)                                                    // 4. 设置远程 sdp
        const answer = await PC.createAnswer()                                          // 5. 创建 answer sdp
        PC.setLocalDescription(answer)                                                  // 6. 设置本地 sdp
        signaling.send(JSON.stringify(answer))                                          // 7. 发送 answer
        console.log('发送 answer sdp', answer)
    } else if (msg.type === 'ice') {
        console.log('收到 ice candidate', JSON.parse(msg.ice))
        PC.addIceCandidate(JSON.parse(msg.ice))                                         // 8. 添加 ice
    }
}

signaling.onopen = () => {console.log('信令服务器：成功连接！')}
signaling.onclose = () => {console.log('信令服务器：关闭连接！')}
signaling.onerror = (error) => {console.log('信令服务器：错误连接！', error)}
```

<br>

---

## nc1s

```js
const signaling = new WebSocket('wss://xn--e6q212bhn0c.xn--6qq986b3xl:3002')            // 信令服务器
let PC = {}                                                                             // 连接
let STREAM = null                                                                       // 流

let kill = {}
setInterval(() => {
    let dddd = {}

    for (let id in PC) {
        if (PC[id].iceConnectionState === 'connected' || PC[id].iceConnectionState === 'completed') {
            if(kill[id] !== 1) console.log('正常连接', id, kill[id])
            kill[id] = 1
        }else{
            console.log('异常连接', id, kill[id])
            kill[id]++
            if (kill[id] > 3) {
                dddd[id] = 1
            }
        }
    }

    for (let id in dddd) {
        console.log('断开连接', id)
        // 删除连接     
        PC[id].getSenders().map(sender => PC[id].removeTrack(sender))
        PC[id].onicecandidate = null
        PC[id].oniceconnectionstatechange = null;
        PC[id].ontrack = null
        PC[id].close()
        PC[id] = null
        delete kill[id]
        delete PC[id]
    }
}, 2000)

signaling.onopen = () => {
    console.log('信令服务器：成功连接！')
    navigator.mediaDevices.getDisplayMedia({ video: true, audio: true}).then(stream => {// 1. 获取流
        document.getElementById('local_H').srcObject = stream                           // 2. 将流绑定到标签
        STREAM = stream                                                                 // 3. 保存流
    })
}

signaling.onmessage = async (event) => {                                                
    const msg = JSON.parse(event.data)
    if(msg.type === 'join') {
        console.log('收到 join', msg.id)
        
        PC[msg.id] = new RTCPeerConnection()                                            // 4. 创建连接
        PC[msg.id].onicecandidate = (e) => {                                            // 5. 发送 ice
            if (e.candidate) {                                                          // 一定，一定，一定要在 new 完 RTCPeerConnection 后马上设置 onicecandidate
                signaling.send(JSON.stringify({
                    type: 'ice',
                    id: msg.id,
                    ice: JSON.stringify(e.candidate)
                }))
            }
            console.log('发送 ice candidate 到', msg.id, e.candidate)
        }
        STREAM.getTracks().forEach((track) => PC[msg.id].addTrack(track, STREAM))       // 6. 将流添加到连接
        PC[msg.id].createOffer().then(offer => {                                        // 7. 创建 offer sdp
            PC[msg.id].setLocalDescription(offer)                                       // 8. 设置本地 sdp
            signaling.send(JSON.stringify({
                type: 'offer',
                id: msg.id,
                sdp: offer.sdp
            }))                                                                         // 9. 发送 offer sdp
            console.log('发送 offer sdp 到', msg.id, offer)
        })

    } else if (msg.type === 'answer') {                                                 // 10. 接收 answer sdp
        console.log('收到 answer sdp 来自', msg.id, msg)
        PC[msg.id].setRemoteDescription(msg)                                            // 11. 设置远程 sdp
    }
}

signaling.onclose = () => {console.log('信令服务器：关闭连接！')}
signaling.onerror = (error) => {console.log('信令服务器：错误连接！', error)}
```

```js
const signaling = new WebSocket('wss://xn--e6q212bhn0c.xn--6qq986b3xl:3002')            // 信令服务器
let PC = null                                                                           // 连接
let ID = null                                                                           // ID

signaling.onmessage = async (event) => {
    const msg = JSON.parse(event.data)
    if (msg.id !== ID) return
    
    if (msg.type === 'offer') {                                                         // 1. 收到 offer sdp
        console.log('收到 offer sdp', msg)
        PC = new RTCPeerConnection()                                                    // 2. 创建连接
        PC.ontrack = (e) => {                                                           // 3. 监听连接上的流
            document.getElementById('remote_H').srcObject = e.streams[0]
        }
        PC.setRemoteDescription({                                                       // 4. 设置远程 sdp
            type: msg.type,
            sdp: msg.sdp
        })
        const answer = await PC.createAnswer()                                          // 5. 创建 answer sdp
        PC.setLocalDescription(answer)                                                  // 6. 设置本地 sdp
        signaling.send(JSON.stringify({                                                 // 7. 发送 answer sdp
            id: msg.id,
            type: answer.type,
            sdp: answer.sdp
        }))                                                                             
        console.log('发送 answer sdp', answer)
    } else if (msg.type === 'ice') {
        console.log('收到 ice candidate', JSON.parse(msg.ice))
        PC.addIceCandidate(JSON.parse(msg.ice))                                         // 8. 添加 ice
    }
}

signaling.onopen = () => {
    console.log('信令服务器：成功连接！')
    // 创建唯一 ID
    ID = Date.now().toString(36) + Math.random().toString(36).slice(2)
    // 发送 请求 到信令服务器
    signaling.send(JSON.stringify({type: 'join', id: ID}))
}
signaling.onclose = () => {console.log('信令服务器：关闭连接！')}
signaling.onerror = (error) => {console.log('信令服务器：错误连接！', error)}
```

<br>

---

## 1cs1cs

```js
const signaling = new WebSocket('wss://xn--e6q212bhn0c.xn--6qq986b3xl:3002')            // 信令服务器
let local_PC = null                                                                     // 本地连接
let remote_PC = null                                                                    // 远程连接

const config = {
    iceServers: [
        {urls: 'stun:daixll.tpddns.cn:3478'},
        {urls: 'turn:daixll.tpddns.cn:3478', username: 'admin', credential: '123456'}
    ]
}

signaling.onopen = () => {
    console.log('信令服务器：成功连接！')
    navigator.mediaDevices.getUserMedia({ video: true, audio: true}).then(stream => {   // 1. 获取流
        document.getElementById('local_H').srcObject = stream                           // 2. 将流绑定到标签
        //local_PC = new RTCPeerConnection()                                            // 3. 创建连接
        local_PC = new RTCPeerConnection({iceServers: [{urls: 'stun:xn--e6q212bhn0c.xn--6qq986b3xl:3478'},{urls: 'turn:xn--e6q212bhn0c.xn--6qq986b3xl:3478',username: 'admin',credential: '123456'}]})

        document.getElementById('call_H').onclick = () => {
            local_PC.onicecandidate = (e) => {                                          // 4. 发送 ice
                if (e.candidate) {                                                      // 一定，一定，一定要在 new 完 RTCPeerConnection 后马上设置 onicecandidate
                    signaling.send(JSON.stringify({
                        type: 'ice',
                        ice: JSON.stringify(e.candidate)
                    }))
                }
                console.log('local_PC 发送 ice candidate', e.candidate)
            }

            stream.getTracks().forEach((track) => local_PC.addTrack(track, stream))     // 5. 将流添加到连接
        
            local_PC.createOffer().then(offer => {                                      // 6. 创建 offer sdp
                local_PC.setLocalDescription(offer)                                     // 7. 设置本地 sdp
                signaling.send(JSON.stringify(offer))                                   // 8. 发送 offer sdp
                console.log('local_PC 发送 offer sdp', offer)
            })
        }
    })
}

signaling.onmessage = async (event) => {
    const msg = JSON.parse(event.data)
    if (msg.type === 'offer') {                                                         // 1. 收到 offer sdp
        console.log('remote_PC 收到 offer sdp', msg)
        //remote_PC = new RTCPeerConnection()                                           // 2. 创建连接
        remote_PC = new RTCPeerConnection({iceServers: [{urls: 'stun:xn--e6q212bhn0c.xn--6qq986b3xl:3478'},{urls: 'turn:xn--e6q212bhn0c.xn--6qq986b3xl:3478',username: 'admin',credential: '123456'}]})
        remote_PC.ontrack = (e) => {                                                    // 3. 监听连接上的流
            document.getElementById('remote_H').srcObject = e.streams[0]
        }
        remote_PC.setRemoteDescription(msg)                                             // 4. 设置远程 sdp
        const answer = await remote_PC.createAnswer()                                   // 5. 创建 answer sdp
        remote_PC.setLocalDescription(answer)                                           // 6. 设置本地 sdp
        signaling.send(JSON.stringify(answer))                                          // 7. 发送 answer
        console.log('remote_PC 发送 answer sdp', answer)
    } else if (msg.type === 'ice') {
        console.log('remote_PC 收到 ice candidate', JSON.parse(msg.ice))
        remote_PC.addIceCandidate(JSON.parse(msg.ice))                                  // 8. 添加 ice
    } else if (msg.type === 'answer') {
        console.log('local_PC 收到 answer sdp', msg)
        local_PC.setRemoteDescription(msg)                                              // 10. 设置远程 sdp
    }
}

signaling.onclose = () => {console.log('信令服务器：关闭连接！')}
signaling.onerror = (error) => {console.log('信令服务器：错误连接！', error)}
```