## 参考

* [docker manuals](https://docs.docker.com/manuals/)

<br>

---

## 引子

**Virtual Machines** 

* **更强的隔离性**：在硬件层面上实现虚拟化
* **文件特性**：硬盘文件、快照都是文件，可以持久化

**Docker**

* **轻量化**：在操作系统层面上实现虚拟化
* **分布式**：可以在同一台机器上运行多个容器，每个容器之间相互隔离
* **无状态**：容器每次创建都是全新的，容器内的进程也是全新的，容器内的内容不可持久化

<br>

---

## Install Docker

1. 使用 [apt](https://docs.docker.com/engine/install/ubuntu/#install-using-the-repository) 安装 docker engine



2. 安装并配置 [NVIDIA CTK](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html#with-apt-ubuntu-debian)

3. 验证

    ```sh
    sudo docker run --rm --gpus all nvidia/cuda:12.3.0-base-ubuntu22.04 nvidia-smi
    ```

<br>

---

## 镜像 IMAGE

是一个只读模板，用来创建容器，类似于：

* 面向对象中的类，容器是对象
* 虚拟机中的 `.iso`，容器是虚拟机

### 下载镜像

[Docker Hub](https://hub.docker.com/explore)

```sh
sudo docker pull IMAGE_NAME[:TAG]
```

* `IMAGE_NAME` 镜像名称
* `TAG` 可选，镜像版本或标签，默认为 `latest`

**代理加速**（[参考文档](https://www.lfhacks.com/tech/pull-docker-images-behind-proxy/#practice)）:

* `sudo mkdir -p /etc/systemd/system/docker.service.d`

* `sudo vim /etc/systemd/system/docker.service.d/http-proxy.conf`

    ```bash
    [Service]
    Environment="HTTP_PROXY=http://127.0.0.1:7897"
    Environment="HTTPS_PROXY=http://127.0.0.1:7897"
    ```

* `sudo systemctl daemon-reload && sudo systemctl restart docker`

* `sudo systemctl show --property=Environment docker`

### 查看镜像

```sh
sudo docker images
```

* `REPOSITORY` 镜像名称
* `TAG` 镜像版本或标签
* `IMAGE ID` 镜像 ID：**唯一标识**
* `CREATED` 创建时间
* `SIZE` 镜像大小

### 删除镜像

```sh
sudo docker rmi IMAGE_NAME[:TAG]
```

<br>

---

## 容器 CONTAINER

### 查看容器

```sh
sudo docker ps [-a]
```

### 增删容器

**删除容器**

* 删除容器前需要先停止容器

```sh
sudo docker rm [CONTAINER_ID]
```

* 删除所有已停止容器

```sh
sudo docker container prune
```

**创建容器**

```sh
docker run [OPTIONS] IMAGE [COMMAND] [ARG...]
```

```sh
docker run \ 
    --name [c_name] \           # 容器名
    --rm \                      # 退出时删除容器

    -it \                       # 台前运行，容器在没有指定长时间运行的进程时会立即退出
    -d, --detach \              # 后台运行
    --restart=unless-stopped \  # 非手动停止自动重启

    --privileged \              # root 权限

    --net=host \                # 使用主机网络
    --ipc=host \                # 使用主机的 IPC

    -p 10086:80 \               # 主机 10086 <- 容器内 80
    -P \                        # 容器公开的所有端口随机映射到主机的可用端口

    -v /host/path:/c/path \     # 映射目录
    -v /host/file:/c/file:ro \  # 映射文件 [:ro] 只读

    -w /c/path \                # 工作目录

    [image_name]                # 镜像名
```

### 进出容器

**进入容器**

```sh
sudo docker exec -it [CONTAINER_ID] /bin/bash
```

**执行命令**

```sh
sudo docker exec [CONTAINER_ID] [COMMAND] [ARG...]
```

**退出容器**

```sh
exit
```

### 启停容器

**重启容器**

```sh
sudo docker restart [CONTAINER_ID]
```

**启动容器**

```sh
sudo docker start [CONTAINER_ID]
```

**停止容器**

```sh
sudo docker stop [CONTAINER_ID]
```

<br>

---

## 自建镜像

### 0 准备

```txt
myapp/
├── Dockerfile
├── go.mod
├── main.go
└── static/
    └── index.html
```

<details><summary>code</summary>

```bash
go mod init web_server
```

```go
package main

import (
    "fmt"
    "net/http"
)

func main() {
    http.Handle("/", http.FileServer(http.Dir("./static")))
    fmt.Println("Server is running on port 80...")
    http.ListenAndServe(":80", nil)
}
```

```html
hello docker
```
</details>


### 1 编写 Dockerfile

```Dockerfile
# 第一阶段：构建阶段
FROM golang AS builder
# 设置工作目录
WORKDIR /web_server

# 复制 go.mod 和 go.sum 文件并下载依赖
COPY go.mod go.sum ./
RUN go mod download
# 复制源代码
COPY . .
# 编译 Go 代码
RUN go build -o web_server .

# 第二阶段：生产阶段
FROM ubuntu
# 设置工作目录
WORKDIR /root/

# 从构建阶段复制编译好的二进制文件
COPY --from=builder /web_server/web_server .
COPY --from=builder /web_server/static ./static

# 暴露端口
EXPOSE 8080
# 运行应用程序
CMD ["./web_server"]
```

### 2 构建镜像

```bash
sudo docker buildx build -t web_server .
```

* `-t` 指定名称
* `.` 在当前目录构建

### 3 推送到 dockerhub


```bash
sudo docker login
sudo docker tag web_server dxlcq/web_server
sudo docker push dxlcq/web_server
```

<br>

---

## docker compose

### 


### 常用命令

* 启动容器组

    ```bash
    sudo docker compose up -d
    ```

    * `-d` 后台运行

* 停止容器组

    ```bash
    sudo docker compose down
    ```

* 查看容器组

    ```bash
    sudo docker compose ps
    ```

* 查看日志

    ```bash
    sudo docker compose logs -f
    ```

    * `-f` 实时查看


<br>

---


## 网络

### 查看所有的 