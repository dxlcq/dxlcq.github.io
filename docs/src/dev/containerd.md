## 参考



<br>

---

## 安装 containerd

`apt` 安装

```shell
sudo apt install containerd
```

手动安装

```shell
wget https://github.com/containerd/containerd/releases/download/v2.0.0/containerd-2.0.0-linux-amd64.tar.gz
sudo tar -C /usr/local -zxvf containerd-2.0.0-linux-amd64.tar.gz
wget https://raw.githubusercontent.com/containerd/containerd/main/containerd.service
sudo mkdir -p /usr/local/lib/systemd/system/
sudo mv containerd.service /usr/local/lib/systemd/system/containerd.service
sudo systemctl daemon-reload
sudo systemctl enable --now containerd

wget https://github.com/opencontainers/runc/releases/download/v1.2.1/runc.amd64
sudo install -m 755 runc.amd64 /usr/local/sbin/runc

wget https://github.com/containernetworking/plugins/releases/download/v1.6.0/cni-plugins-linux-amd64-v1.6.0.tgz
sudo mkdir -p /opt/cni/bin
sudo tar -C /opt/cni/bin -zxvf cni-plugins-linux-amd64-v1.6.0.tgz

sudo systemctl enable containerd
```

## 容器

### 查看容器

```shell
sudo crictl ps
```
