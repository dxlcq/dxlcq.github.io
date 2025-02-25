## 参考



<br>

---

## Getting Started

1. 安装 helm

[github helm](https://github.com/helm/helm/releases)

解压到 /usr/local/bin

2. 添加 prometheus-community 仓库

```shell
helm repo add prometheus-community https://prometheus-community.github.io/helm-charts
```

3. 安装 prometheus

```shell
helm install prometheus prometheus-community/prometheus
helm install prometheus prometheus-community/kube-prometheus-stack --namespace prometheus --create-namespace
```

4. 让服务暴露出来

```yaml
# values.yaml
prometheus:
  prometheusSpec:
    service:
      type: NodePort

grafana:
  service:
    type: NodePort

alertmanager:
  service:
    type: NodePort
```

```shell
helm upgrade prometheus prometheus-community/kube-prometheus-stack -n prometheus -f values.yaml
```

5. 康康服务

```shell
kubectl get svc -n prometheus
```


