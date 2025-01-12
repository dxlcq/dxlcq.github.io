## 参考

* [Kubernetes一小时轻松入门](https://www.youtube.com/watch?v=SL83f7Nzxr0/)

* [Kubernetes 进阶训练营(第3期)](https://www.qikqiak.com/k3s/)

* [Kubernetes 基础教程](https://jimmysong.io/book/kubernetes-handbook/)

* [Kubernetes 中文社区](http://docs.kubernetes.org.cn/)

* [Kubernetes 官方教程](https://kubernetes.io/zh-cn/docs/tutorials/)

* [k8s 1.29 教程](https://www.bilibili.com/video/BV1PbeueyE8V)

<br>

---

## 架构

```
├── remote
│   ├── kubectl
│   └── kubectl-convert
│
│
├── Master Node (主节点，也称为 Control Plane 控制平面)
│   ├── kube-apiserver          (API 服务器)
│   ├── apiextensions-apiserver (API 扩展)
│   ├── kube-aggregator         (API 聚合器)
│   ├── kube-log-runner         (日志调试)
│   ├── kube-scheduler          (调度器，选择 pod 所在 node)
│   └── kube-controller-manager (控制器，管理 Container)
│
├── etcd                        (分布式键值存储)
│
├── Worker Node (工作节点，一台物理/虚拟机上可以有多个工作节点)
│   │
│   ├── Kubeadm                 (初始化集群)
│   ├── Kubelet                 (管理节点上的 Pod)
│   ├── kube-proxy              (网络代理, 负载均衡)
│   ├── mounter                 (挂载器, 管理存储卷的挂载和卸载)
│   └── Container-Runtime       (容器运行时, 如 Docker)
│       ├── Pod                 (k8s 最小部署单元，逻辑概念)
│       │   └── Container       (容器, 建议一个 Pod 一个 Container)
│       ├── Pod
│       └── Pod
│
└── Worker Node (工作节点)
```

<br>

---

## Getting Started

[文档](https://kubernetes.io/zh-cn/docs/setup/production-environment/tools/kubeadm/install-kubeadm/)

1. 禁用交换空间，以提高性能，启用 IPv4 转发，以便 `kubeadm` 可以正确的配置 `iptables` 链

    ```shell
    sudo su

    sed -i '/\bswap\b/ s/^/#/' /etc/fstab
    swapoff -a

    cat <<EOF | sudo tee /etc/sysctl.d/k8s.conf
    net.ipv4.ip_forward = 1
    EOF
    
    sysctl --system

    free -h

    sysctl net.ipv4.ip_forward
    ```

    > 在 `/etc/fstab` 文件中查找所有包含 `swap` 的行，并在行首添加 `#`，将这些行注释掉，然后关闭交换空间

    > 在 `/etc/sysctl.d/` 目录下创建一个 `k8s.conf` 文件，写入 `net.ipv4.ip_forward = 1`
    
    > 重新加载配置

    > 交换空间成功关闭后，应该是 `0`

    > 检查转发是否启用成功，应该是 `1`
    

3. 安装并配置 Container Runtime

    * 使用 [Docker](./docker.md)

        ```shell
        sudo su

        apt install docker.io unzip -y

        wget https://github.com/Mirantis/cri-dockerd/archive/refs/tags/v0.3.16.zip
        wget https://github.com/Mirantis/cri-dockerd/releases/download/v0.3.16/cri-dockerd-0.3.16.amd64.tgz

        unzip v0.3.16.zip
        cp cri-dockerd/cri-dockerd /usr/local/bin
        
        tar -zxvf cri-dockerd-0.3.16.amd64.tgz
        cd cri-dockerd-0.3.16
        install packaging/systemd/* /etc/systemd/system
        sed -i -e 's,/usr/bin/cri-dockerd,/usr/local/bin/cri-dockerd,' /etc/systemd/system/cri-docker.service
        systemctl daemon-reload
        systemctl enable --now cri-docker.socket
        ```

        > 下载容器运行时

        > 下载垫片，用于将 `cri-dockerd` 作为 `CRI` 运行时，下载源码

        > 解压垫片，复制二进制文件到 `/usr/local/bin` 目录下

        > 解压源码，安装 `systemd` 服务，修改 `cri-docker.service` 文件，重新加载 `systemd`，启用 `cri-docker` 服务

        初始化和加入集群时，都需要指定 `--cri-socket=unix:///var/run/cri-dockerd.sock`

    <br>

    * 使用 [Containerd](./containerd.md)

        ```shell
        apt install containerd -y
        mkdir -p /etc/containerd
        containerd config default | sudo tee /etc/containerd/config.toml
        vim /etc/containerd/config.toml
        systemctl restart containerd
        ```

        > ```toml
        > [plugins."io.containerd.grpc.v1.cri".containerd.runtimes.runc]
        >   runtime_type = "io.containerd.runc.v2"
        >   [plugins."io.containerd.grpc.v1.cri".containerd.runtimes.runc.options]
        >     SystemdCgroup = true
        > ```
        > 
        > > 1. 确保 `SystemdCgroup` 为 `true`
        >
        > ```toml
        > disabled_plugins = []
        > ```
        >
        > > 2. 确保 `disabled_plugins` 中没有 `cri` 插件
        > 
        > 重启 `containerd` 服务

4. 安装 `kubeadm` `kubelet` 和 `kubectl`

    ```shell
    curl -fsSL https://pkgs.k8s.io/core:/stable:/v1.31/deb/Release.key | sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-apt-keyring.gpg
    echo 'deb [signed-by=/etc/apt/keyrings/kubernetes-apt-keyring.gpg] https://pkgs.k8s.io/core:/stable:/v1.31/deb/ /' | sudo tee /etc/apt/sources.list.d/kubernetes.list
    sudo apt-get update
    sudo apt-get install -y kubelet kubeadm kubectl
    sudo apt-mark hold kubelet kubeadm kubectl
    sudo systemctl enable --now kubelet
    systemctl enable kubelet
    ```

    > 官网的脚本，只增加了一个开机自启

5. 初始化 / 加入集群

    ```shell
    kubeadm init
    ```

    ```shell
    mkdir -p $HOME/.kube
    sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
    sudo chown $(id -u):$(id -g) $HOME/.kube/config
    ```

    ```shell
    kubeadm token create --print-join-command
    ```

    > 在 **控制平面** 上执行上述命令会初始化一个 Kubernetes 集群，输出的最后会有一个 `kubeadm join` 命令，用于将其他节点加入集群

    > 在 **控制平面** 上执行上述命令，以便使用 `kubectl` 命令

    > **控制平面** 生成 join 命令，其他节点执行该命令加入集群

    ```shell
    kubeadm join <control-plane-host>:<control-plane-port> --token <token> --discovery-token-ca-cert-hash sha256:<hash>
    ```

    > 在 **工作节点** 上执行上述命令，将节点加入集群

6. 在 **控制平面** 上安装 `CNI` 网络插件

    ```shell
    kubectl create -f https://raw.githubusercontent.com/projectcalico/calico/v3.29.1/manifests/calico.yaml
    ```


7. 在 **控制平面** 上启用 Kubernetes 中的 GPU 支持

    * [NVIDIA device plugin for Kubernetes](https://github.com/NVIDIA/k8s-device-plugin)

        ```shell
        kubectl create -f https://raw.githubusercontent.com/NVIDIA/k8s-device-plugin/v0.17.0/deployments/static/nvidia-device-plugin.yml
        ```

7. 在控制平面上查看集群状态

    ```shell
    kubectl get nodes
    kubectl get pod -A
    kubectl get nodes -o jsonpath="{range .items[*]}{.metadata.name}{': '}{.status.allocatable.nvidia\.com/gpu}{'\n'}{end}"
    ```

    > 查看节点状态，以及节点上 GPU 的数量

8. 创建一个 `vim nginx-deployment.yaml`

    ```yaml
    apiVersion: apps/v1         # 版本             Kubernetes API 版本
    kind: Deployment            # 资源类型         资源类型是 Deployment
    metadata:                   # 元数据           包含资源的名称和标签
      name: nginx-deployment
    spec:                       # 规范             定义资源的规范
      replicas: 2               #   副本数量        指定运行多少个 Pod 实例
      selector:                 #   选择器          用于选择要管理的 Pod
        matchLabels:            #       匹配标签    选择具有指定标签的 Pod
          app: nginx
      template:                 #   模板            定义创建的 Pod 的元数据和规范
        metadata:               #       元数据      定义 Pod 的元数据
          labels:               #           标签    给 Pod 添加标签
            app: nginx
        spec:                   #       规范        定义 Pod 的规范
          containers:           #           容器    定义 Pod 中的容器
          - name: nginx
            image: nginx:latest
            ports:
            - containerPort: 80
    ```

    ```shell
    kubectl apply -f nginx-deployment.yaml
    ```

9. 创建一个 `vim nginx-service.yaml`

    ```yaml
    apiVersion: v1              # 版本
    kind: Service               # 资源类型
    metadata:                   # 元数据
      name: nginx-service       #   名称
    spec:                       # 规范
      selector:                 #   选择器          选择要暴露的 Pod
        app: nginx              #       匹配标签
      ports:                    #   端口
        - protocol: TCP         #       协议
          port: 80              #       端口        Service 端口
          targetPort: 80        #       目标端口     Pod 端口
      externalIPs:              #   外部 IP         暴露到外部的 IP
        - 10.0.0.31
    ```

    ```shell
    kubectl apply -f nginx-service.yaml
    ```

10. 查看服务

    ```shell
    kubectl get service nginx-service
    ```

11. 访问服务

    ```shell
    curl 10.0.0.31
    ```
    


<br>

---


## RESOURCE

资源清单，一切皆资源

```yaml
apiVersion: v1                      # 资源的 API 版本
kind: Pod | Service | Deployment    # kubectl api-resources 查看资源的版本和类型

metadata:                           # 元数据
  name: name                        # 这个资源的名称
  namespace: default                # 命名空间，用于隔离资源
  labels:                           # 标签，用于标识和组织资源
    key: value                      # 键值对，可以有多个

spec:
  # 每个资源都有自己的规范
```


<br>

---

## Pod

```yaml
apiVersion: v1
kind: Pod

metadata:
  name: ubuntu

spec:
  containers:
  - name: ubuntu
    image: ubuntu:latest
    command: ["sleep", "infinity"]
    volumeMounts:
      - name: nfs
        mountPath: /mnt/nfs  # 挂载路径

  volumes:
    - name: nfs
      persistentVolumeClaim:
        claimName: nfs.pvc  # 引用 PVC 名称
```

### pause

1 号容器，其他容器共享其 `PID`，`IPC`，`Network`，

* `PID`：可以通过 `ps` 命令查看到其他容器的进程，回收僵尸进程

* `IPC`：可以通过共享内存进行通信

* `Network`：可以通过回环地址 `localhost` 相互通信

### initC

初始化容器，用于初始化环境，如配置文件，数据库等

* 线性启动

* 返回 0 时，开始 mainC 容器

### mainC

主容器，用于运行应用程序

**钩子**

* `postStart`：在容器启动后执行

* `preStop`：在容器停止前执行

**探针**

由当前 pod 所在的 node 节点的 kubelet 进行检查

* `startupProbe`：检查容器是否启动

* `livenessProbe`：检查容器是否存活

* `readinessProbe`：检查容器是否就绪

<br>

---

## deployment

```yaml
spec:
  replicas: 3

  selector:
    matchLabels:
      app: nginx
  
  template:
    metadata:
      labels:
        app: nginx
    spec:
      containers:
      - name: nginx
        image: nginx:latest
        ports:
        - containerPort: 80
```

<br>

---

## service

```yaml
spec:
  selector:
    app: nginx
  ports:
    - protocol: TCP
      port: 80
      targetPort: 80
```

<br>

---

## job

```shell
kubectl apply -f <job.yaml>
kubectl get jobs
kubectl get pods
kubectl logs <pod-name>
kubectl delete job <job-name>
```

<br>

---

## PersistentVolume

```yaml
apiVersion: v1
kind: PersistentVolume

metadata:
  name: nfs

spec:
  capacity:
    storage: 500Gi
  volumeMode: Filesystem
  accessModes:
    - ReadWriteMany
  nfs:
    server: 180.85.207.45
    path: "/mnt/nfs"
```

## PersistentVolumeClaim

```yaml
apiVersion: v1
kind: PersistentVolumeClaim

metadata:
  name: nfs.pvc

spec:
  accessModes:
    - ReadWriteMany
  resources:
    requests:
      storage: 500Gi
  volumeName: nfs # 指定 PersistentVolume 的名称
```



<br>

---

## kubelet

与容器运行时交互，依赖 `CRI` 容器运行时接口

<br>

---

## kubeadm

用于初始化集群、加入节点、重置集群等操作

### 完整清理 k8s 集群

```shell
sudo kubeadm reset
sudo rm -rf /etc/kubernetes /var/lib/etcd
sudo rm -rf $HOME/.kube
```


<br>

---

## kubectl

用于控制平面进行操作，如创建、删除、更新资源

### 查看集群相关信息

获取集群信息，包括 API 服务器地址、DNS 等

```shell
kubectl cluster-info          # 查看集群信息
kubectl get node              # 查看节点信息
kubectl describe node <node>  # 查看节点详细信息
```

### 查看 Pod 相关信息

```shell
kubectl get pod -A              # 查看所有 pod
kubectl get pod -n kube-system  # 查看 kube-system 命名空间下的 pod
kubectl get pod -o wide         # 查看 pod 的详细信息
```