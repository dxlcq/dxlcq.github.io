## 参考

* [helm 教程](https://helm.sh/zh/docs/intro/using_helm/)

## Helm

    ```shell
    snap install helm --classic
    ```

* repo

    * 查看

        ```shell
        helm repo list
        ```

    * 添加

        ```shell
        helm repo add 仓库名称 仓库地址
        ```

    * 更新

        ```shell
        helm repo update
        ```

* release

    * 查看

        ```shell
        helm list -A
        ```

    * 卸载

        ```shell
        helm uninstall [release]
        ```

    * 安装

        ```shell
        helm install [release] 仓库名称/包名 -n 命名空间 --create-namespace
        ```

* upgrade

    * 查看

        ```shell
        helm show values 仓库名称/包名
        ```

        ```shell
        helm get values [release] -n 命名空间
        ```

    * 修改

        ```shell
        helm upgrade [release] 仓库名称/包名 -n 命名空间 -f values.yaml
        ```

    * rollback
    
        ```shell
        helm rollback [release] 版本号 -n 命名空间
        ```

        ```shell
        helm history [release] -n 命名空间
        ```


<br>

---


## Prometheus

1. 添加 prometheus-community 仓库

    ```shell
    helm repo add prometheus-community https://prometheus-community.github.io/helm-charts
    ```

2. 安装 prometheus

    ```shell
    helm install prometheus prometheus-community/kube-prometheus-stack --namespace prometheus --create-namespace
    ```

3. 让服务暴露出来

    ```yaml
    # values-prometheus.yaml
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
    helm upgrade prometheus prometheus-community/kube-prometheus-stack -n prometheus -f values-prometheus.yaml
    ```

4. 康康服务

    ```shell
    kubectl get svc -n prometheus
    ```

<br>

---

## GPU Operator

1. 导入仓库

    ```shell
    helm repo add nvidia https://helm.ngc.nvidia.com/nvidia
    ```

2. 安装 GPU Operator

    ```shell
    helm install gpu-operator nvidia/gpu-operator -n gpu-operator --create-namespace
    ```

3. 暴露服务

    ```yaml
    # values-gpu-operator.yaml
    dcgmExporter:
      service:
        type: NodePort
    ```

    ```shell
    helm upgrade gpu-operator nvidia/gpu-operator -n gpu-operator -f values-gpu-operator.yaml
    ```

4. 康康服务

    ```shell
    kubectl get svc -n gpu-operator
    ```