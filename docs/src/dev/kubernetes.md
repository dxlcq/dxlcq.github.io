## 参考

* [Kubernetes一小时轻松入门](https://www.youtube.com/watch?v=SL83f7Nzxr0/)

* [Kubernetes 进阶训练营(第3期)](https://www.qikqiak.com/k3s/)

* [Kubernetes 基础教程](https://jimmysong.io/book/kubernetes-handbook/)

* [Kubernetes 中文社区](http://docs.kubernetes.org.cn/)

* [Kubernetes 官方教程](https://kubernetes.io/zh-cn/docs/tutorials/)

* [k8s 1.29 教程](https://www.bilibili.com/video/BV1PbeueyE8V)

---

* [k8s scheduler-plugins](https://github.com/kubernetes-sigs/scheduler-plugins/tree/v0.29.7)

* [调度框架](https://kubernetes.io/zh-cn/docs/concepts/scheduling-eviction/scheduling-framework/)

* [调度器配置](https://kubernetes.io/zh-cn/docs/reference/scheduling/config/)

* [配置多个调度器](https://kubernetes.io/zh-cn/docs/tasks/extend-kubernetes/configure-multiple-schedulers/)

* [k8s 调度器开发教程](https://blog.haohtml.com/archives/34665)

* [同上](https://arthurchiao.art/blog/k8s-scheduling-plugins-zh/)

* [同上](https://www.qikqiak.com/post/custom-kube-scheduler/)



<br>

---

## Getting Started

`sudo su`

1. 禁用交换空间，以提高性能，启用 IPv4 转发，以便 `kubeadm` 可以正确的配置 `iptables` 链

    ```shell
    # 在 /etc/fstab 文件中查找所有包含 swap 的行，将这些行注释掉，然后关闭交换空间
    sed -i '/\bswap\b/ s/^/#/' /etc/fstab
    swapoff -a
    # 在 /etc/sysctl.d/ 目录下创建一个 k8s.conf 文件，写入 net.ipv4.ip_forward = 1
    cat <<EOF | sudo tee /etc/sysctl.d/k8s.conf
    net.ipv4.ip_forward = 1
    EOF
    # 重新加载配置
    sysctl --system
    # 交换空间成功关闭后，应该是 0
    free -h
    # IP 转发启用成功后，应该是 1
    sysctl net.ipv4.ip_forward
    ```
    

2. 安装并配置容器运行时

    * 使用 [Docker](./docker.md)，**注意**，初始化和加入集群时，都需要指定 `--cri-socket=unix:///var/run/cri-dockerd.sock`

        ```shell
        # 下载容器运行时
        apt install docker.io unzip -y
        # 下载垫片，用于将 cri-dockerd 作为 CRI 运行时，下载垫片源码，用于安装服务
        wget https://github.com/Mirantis/cri-dockerd/archive/refs/tags/v0.3.16.zip
        wget https://github.com/Mirantis/cri-dockerd/releases/download/v0.3.16/cri-dockerd-0.3.16.amd64.tgz
        # 解压垫片，解压源码
        unzip v0.3.16.zip
        tar -zxvf cri-dockerd-0.3.16.amd64.tgz
        # 复制二进制文件到 /usr/bin 目录下
        cp cri-dockerd/cri-dockerd /usr/bin
        # 安装 systemd 服务，重新加载 systemd，启用 cri-docker 服务
        install cri-dockerd-0.3.16/packaging/systemd/* /etc/systemd/system
        systemctl daemon-reload
        systemctl enable --now cri-docker.socket
        ```

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

3. 安装 `NVIDIA CTK`

    [NVIDIA Container Toolkit](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html)

    ```shell
    sudo apt install curl -y
    # 添加 nv 的 apt 仓库
    curl -fsSL https://nvidia.github.io/libnvidia-container/gpgkey | sudo gpg --dearmor -o /usr/share/keyrings/nvidia-container-toolkit-keyring.gpg \
    && curl -s -L https://nvidia.github.io/libnvidia-container/stable/deb/nvidia-container-toolkit.list | \
    sed 's#deb https://#deb [signed-by=/usr/share/keyrings/nvidia-container-toolkit-keyring.gpg] https://#g' | \
    sudo tee /etc/apt/sources.list.d/nvidia-container-toolkit.list
    # 安装 ctk
    sudo apt-get update
    sudo apt-get install -y nvidia-container-toolkit
    ```

    * docker

        ```shell
        # 将 nv 的容器运行时集成到 docker 中，并设置为 docker 的默认运行时
        sudo nvidia-ctk runtime configure --runtime=docker --set-as-default
        ```

4. 安装 `kubeadm` `kubelet` 和 `kubectl`

    [kubeadm](https://kubernetes.io/zh-cn/docs/setup/production-environment/tools/kubeadm/install-kubeadm/)

    ```shell
    # 添加 k8s 的 apt 仓库
    curl -fsSL https://pkgs.k8s.io/core:/stable:/v1.29/deb/Release.key | sudo gpg --dearmor -o /etc/apt/keyrings/kubernetes-apt-keyring.gpg
    echo 'deb [signed-by=/etc/apt/keyrings/kubernetes-apt-keyring.gpg] https://pkgs.k8s.io/core:/stable:/v1.29/deb/ /' | sudo tee /etc/apt/sources.list.d/kubernetes.list
    # 安装并锁定版本
    sudo apt-get update
    sudo apt-get install -y kubelet kubeadm kubectl
    sudo apt-mark hold kubelet kubeadm kubectl
    # 开机启动 kubelet
    sudo systemctl enable --now kubelet
    ```

5. 初始化 / 加入集群
    
    * 控制平面

        ```shell
        # 初始化集群
        kubeadm init
        # 
        mkdir -p $HOME/.kube
        sudo cp -i /etc/kubernetes/admin.conf $HOME/.kube/config
        sudo chown $(id -u):$(id -g) $HOME/.kube/config
        ```
        
        ```shell
        # 再看一眼 join
        kubeadm token create --print-join-command
        ```


    * 工作节点

        ```shell
        # 加入集群
        kubeadm join <control-plane-host>:<control-plane-port> --token <token> --discovery-token-ca-cert-hash sha256:<hash>
        ```

6. 安装 `CNI` 网络插件

    [calico](https://github.com/projectcalico/calico/tags)

    ```shell
    # 只需要在控制平面部署
    kubectl create -f https://raw.githubusercontent.com/projectcalico/calico/refs/tags/v3.29.1/manifests/calico.yaml
    ```


7. 安装 `NVIDIA` 插件

    [NVIDIA device plugin for Kubernetes](https://github.com/NVIDIA/k8s-device-plugin/tags)

    ```shell
    # 只需要在控制平面部署
    kubectl create -f https://raw.githubusercontent.com/NVIDIA/k8s-device-plugin/refs/tags/v0.17.0/deployments/static/nvidia-device-plugin.yml
    ```

7. 查看集群状态

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


## node

```shell
kubectl describe node <node-name>  # 查看节点详细信息

kubectl label node <node-name> <key>=<value>              # 添加标签
kubectl label node <node-name> <key>-                     # 删除标签
kubectl label node <node-name> <key>=<value> --overwrite  # 覆写标签
kubectl get nodes --show-labels                           # 查看标签
```

<br>

---

## namespace

```shell
kubectl get namespaces              # 查看所有命名空间
kubectl create namespace <ns-name>  # 创建命名空间
```


<br>

---

## pod

```yaml
apiVersion: v1
kind: Pod

metadata:
  name: po-ubuntu
  namespace: carla

spec:
  containers:
  - name: c-ubuntu
    image: ubuntu:latest
    command: ["sleep", "infinity"]
    volumeMounts:
      - name: v-nfs           # 使用的 volume 名称
        mountPath: /mnt/nfs   # 挂载路径

  volumes:
    - name: v-nfs             # volume 名称
      persistentVolumeClaim:
        claimName: pvc-nfs    # 引用 PVC 名称

# kubectl -n carla exec -it po-ubuntu -c c-ubuntu -- /bin/bash
```

**pause**

1 号容器，其他容器共享其 `PID`，`IPC`，`Network`，

* `PID`：可以通过 `ps` 命令查看到其他容器的进程，回收僵尸进程

* `IPC`：可以通过共享内存进行通信

* `Network`：可以通过回环地址 `localhost` 相互通信

**initC**

初始化容器，用于初始化环境，如配置文件，数据库等

* 线性启动

* 返回 0 时，开始 mainC 容器

**mainC**

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

## Network

### Calico

BGP 对等创建失败

添加环境变量，做 CIDR 匹配

```shell
kubectl set env daemonset/calico-node -n kube-system \
  IP_AUTODETECTION_METHOD="cidr=180.85.206.0/23"
```

删除

```shell
kubectl set env daemonset/calico-node -n kube-system \
  IP_AUTODETECTION_METHOD-
```

查看

```shell
kubectl describe daemonset/calico-node -n kube-system
```




<br>

---

## Controller

### deployment

```yaml
apiVersion: apps/v1
kind: Deployment

metadata:
  name: deployment-carla
  namespace: carla

spec:
  replicas: 2     # 副本数量
  
  selector:       # 选择器
    matchLabels:
      app: po-carla

  template:       # 模板，起 pod
    metadata:
      labels:     # 设置标签
        app: po-carla
    
    spec:
      containers:
        - name: c-carla
          image: carlasim/carla:0.9.15
          command: ["/bin/bash", "./CarlaUE4.sh", "-RenderOffScreen"]
          securityContext:          # 启用特权模式
            privileged: true
          resources:                # 设置资源限制
            limits:
              nvidia.com/gpu: 1
          ports:
            - containerPort: 2000
            - containerPort: 2001

```

### job

```shell
kubectl apply -f <job.yaml>
kubectl get jobs
kubectl get pods
kubectl logs <pod-name>
kubectl delete job <job-name>
```

<br>

---


## Service

```shell
kubectl get service -A          # 查看所有 service
kubectl get service -n <ns>     # 查看 <ns> 命名空间下的 service
```

### ClusterIP

```yaml
apiVersion: v1
kind: Service

metadata:
  name: service-carla
  namespace: carla

spec:
  type: ClusterIP       # 集群内部访问

  selector:
    app: po-carla

  ports:
    - name: carla2000
      targetPort: 2000  # Pod 端口
      port: 2000        # Service 端口

    - name: carla2001
      port: 2001
      targetPort: 2001
```

### NodePort

```yaml
apiVersion: v1
kind: Service

metadata:
  name: service-carla
  namespace: carla

spec:
  type: NodePort        # 集群外部访问

  selector:
    app: po-carla

  ports:
    - name: carla32000
      targetPort: 32000 # Pod 端口
      port: 32000       # Service 端口
      nodePort: 32000   # Node 端口

    - name: carla32001
      port: 32001
      targetPort: 32001
      nodePort: 32001
```

<br>

---

## Persistence


### PersistentVolume

```yaml
apiVersion: v1
kind: PersistentVolume

metadata:
  name: pv-nfs

spec:
  capacity:
    storage: 500Gi
  volumeMode: Filesystem
  accessModes:
    - ReadWriteMany # 多个 Pod 可以同时读写
  nfs:
    server: 180.85.207.45
    path: "/home/jiao/Public"
```

### PersistentVolumeClaim

```yaml
apiVersion: v1
kind: PersistentVolumeClaim

metadata:
  name: pvc-nfs
  namespace: carla

spec:
  accessModes:
    - ReadWriteMany
  resources:
    requests:
      storage: 500Gi
  volumeName: pv-nfs # 指定 PersistentVolume 的名称
```


<br>

---

## Scheduler

为 pod 分配 node，流程：

* 预选（Filtering），过滤
    
  1. 资源（CPU，内存）

  2. 亲和性和反亲和性

  3. 污点与容忍

* 优选（Scoring），打分

  1. 资源均衡（将 pod 分配到负载更低的 node）


### Affinity

#### NodeAffinity

* 软亲和性：倾向于调度到满足条件的 node

* 硬亲和性：必须调度到满足条件的 node

* 软反亲和性：倾向于不调度到满足条件的 node

* 硬反亲和性：绝对不能调度到满足条件的 node

**软亲和性**

```yaml
apiVersion: v1
kind: Pod

metadata:
  name: pod-nginx
  namespace: tmp

spec:
  affinity:                                             # 亲和
    nodeAffinity:                                       # 节点亲和
      preferredDuringSchedulingIgnoredDuringExecution:  # 软亲和
      - weight: 66          # 设置节点的优先级权重
        preference:
          matchExpressions:
          - key: dddd
            operator: In    # 节点中存在 key:value
            values:
              - bdzd

  containers:
  - name: nginx
    image: nginx:latest
```

**硬亲和性**

```yaml
apiVersion: v1
kind: Pod

metadata:
  name: pod-nginx
  namespace: tmp

spec:
  affinity:                                           # 亲和
    nodeAffinity:                                     # 节点亲和
      requiredDuringSchedulingIgnoredDuringExecution: # 硬亲和
        nodeSelectorTerms:
        - matchExpressions:
          - key: dddd
            operator: In    # 节点中存在 key:value
            values:
            - bdzd

  containers:
  - name: nginx
    image: nginx:latest
```

**反亲和性**

```yaml
...
  operator: NotIn
...
```

#### PodAffinity

* 软亲和性：倾向于调度到满足条件的 pod 附近

```yaml
apiVersion: v1
kind: Pod

metadata:
  name: pod2-nginx
  namespace: tmp

spec:
  affinity:
    podAffinity:                                        # pod 亲和
      preferredDuringSchedulingIgnoredDuringExecution:  # 软亲和
      - weight: 66
        podAffinityTerm:        
          labelSelector:
            matchExpressions:
            - key: bdzd
              operator: In    # 节点中存在 key:value
              values:
              - dddd
          topologyKey: "kubernetes.io/hostname"
  containers:
  - name: nginx
    image: nginx:latest
```

* 硬亲和性：必须调度到满足条件的 pod 附近

```yaml
apiVersion: v1
kind: Pod

metadata:
  name: pod2-nginx
  namespace: tmp

spec:
  affinity:
    podAffinity:                                      # pod 亲和
      requiredDuringSchedulingIgnoredDuringExecution: # 硬亲和
      - labelSelector:
          matchExpressions:
          - key: bdzd
            operator: In    # 节点中存在 key:value
            values:
            - dddd
        topologyKey: "kubernetes.io/hostname"
  containers:
  - name: nginx
    image: nginx:latest
```

#### PodAntiAffinity

* 软反亲和性：倾向于不调度到满足条件的 pod 附近

```yaml
apiVersion: v1
kind: Pod

metadata:
  name: pod2-nginx
  namespace: tmp

spec:
  affinity:
    podAntiAffinity:                                    # pod 反亲和
      preferredDuringSchedulingIgnoredDuringExecution:  # 软亲和
      - weight: 66
        podAffinityTerm:        
          labelSelector:
            matchExpressions:
            - key: bdzd
              operator: In    # 节点中存在 key:value
              values:
              - dddd
          topologyKey: "kubernetes.io/hostname"
  containers:
  - name: nginx
    image: nginx:latest
```

* 硬反亲和性：绝对不能调度到满足条件的 pod 附近

```yaml
apiVersion: v1
kind: Pod

metadata:
  name: pod2-nginx
  namespace: tmp

spec:
  affinity:
    podAntiAffinity:                                  # pod 反亲和
      requiredDuringSchedulingIgnoredDuringExecution: # 硬亲和
      - labelSelector:
          matchExpressions:
          - key: bdzd
            operator: In    # 节点中存在 key:value
            values:
            - dddd
        topologyKey: "kubernetes.io/hostname"
  containers:
  - name: nginx
    image: nginx:latest
```

### Taints & Tolerations

#### Taint

当 pod 无法容忍 node 上的污点时：

* `NoSchedule`：不调度到该 node

* `PreferNoSchedule` 尽量别调度到 该 node

* `NoExecute`：不调度到该 node，且驱离正在运行的 pod

```shell
kubectl describe node <node-name> | grep Taints       # 查看污点
kubectl taint node <node-name> key=value:NoSchedule   # 添加污点
kubectl taint node <node-name> key=value:NoSchedule-  # 删除污点
```

#### Toleration

pod 可以选择容忍污点

* 一般容忍

```yaml
tolerations:
- key: "key"
  operator: "Equal"
  value: "value"
  effect: "NoSchedule"
```

* 容忍所有污点

```yaml
tolerations:
- operator: "Exists"
```

### 二开

按照官方的说法，调度器开发有一种非常简单的做法：

1. 修改默认调度器的启动文件 `/etc/kubernetes/manifests/kube-schdueler.yaml`

    ```yaml
    apiVersion: v1
    kind: Pod
    metadata:
      creationTimestamp: null
      labels:
        component: kube-scheduler
        tier: control-plane
      name: kube-scheduler
      namespace: kube-system
    spec:
      containers:
      - command:
        - kube-scheduler
        - --authentication-kubeconfig=/etc/kubernetes/scheduler.conf
        - --authorization-kubeconfig=/etc/kubernetes/scheduler.conf
        - --bind-address=127.0.0.1
        - --kubeconfig=/etc/kubernetes/scheduler.conf
        - --leader-elect=true
        image: registry.k8s.io/kube-scheduler:v1.31.4
        imagePullPolicy: IfNotPresent
        livenessProbe:
          failureThreshold: 8
          httpGet:
            host: 127.0.0.1
            path: /healthz
            port: 10259
            scheme: HTTPS
          initialDelaySeconds: 10
          periodSeconds: 10
          timeoutSeconds: 15
        name: kube-scheduler
        resources:
          requests:
            cpu: 100m
        startupProbe:
          failureThreshold: 24
          httpGet:
            host: 127.0.0.1
            path: /healthz
            port: 10259
            scheme: HTTPS
          initialDelaySeconds: 10
          periodSeconds: 10
          timeoutSeconds: 15
        volumeMounts:
        - mountPath: /etc/kubernetes/scheduler.conf
          name: kubeconfig
          readOnly: true
      hostNetwork: true
      priority: 2000001000
      priorityClassName: system-node-critical
      securityContext:
        seccompProfile:
          type: RuntimeDefault
      volumes:
      - hostPath:
          path: /etc/kubernetes/scheduler.conf
          type: FileOrCreate
        name: kubeconfig
    status: {}
    ```





