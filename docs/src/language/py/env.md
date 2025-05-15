## miniconda

1. 下载安装脚本

    ```bash
    wget https://repo.anaconda.com/miniconda/Miniconda3-latest-Linux-x86_64.sh
    ```

2. 执行安装脚本

    默认安装在 `~/miniconda3` 目录下

    ```bash
    bash Miniconda3-latest-Linux-x86_64.sh -b
    ```

    ```bash
    rm Miniconda3-latest-Linux-x86_64.sh
    ```

3. 更新

    ```bash
    ~/miniconda3/bin/conda update -n base -c defaults conda
    # -n 指定环境为 base
    # -c 指定源为 defaults
    # conda 软件名
    ```

4. 配置环境变量

    ```bash
    echo 'export PATH=$HOME/miniconda3/bin:$PATH' >> ~/.bashrc
    ```

    ```bash
    source ~/.bashrc
    ```

5. 验证

    ```bash
    conda init
    source ~/.bashrc
    ```

6. 删除默认启动 `base` 环境

    ```bash
    conda config --set auto_activate_base false
    ```

### command

* 查看所有环境

    ```bash
    conda info -e
    ```

* 创建环境
    ```bash
    conda create -n py27 python=2.7
    # 创建名为 py27 的环境，使用 Python 2.7
    conda create -n py36 python=3.6 django=1.11
    # 创建名为 py36 的环境，使用 Python 3.6，安装 Django 1.11
    ```

* 激活环境

    ```bash
    conda activate py27
    ```

* 退出环境

    ```bash
    conda deactivate
    ```

* 删除环境

    ```bash
    conda remove -n py27 --all
    ```

* 查看环境中已安装的软件

    ```bash
    conda list
    ```

* 安装软件

    ```bash
    conda install django
    ```

* 卸载软件

    ```bash
    conda remove django
    ```

<br>

---


## pip

* 下载 `wget https://bootstrap.pypa.io/get-pip.py`
* 安装 `python get-pip.py`
* 测试 `python -m pip --version`

**查看当前软件包**

* `pip list`


<br>

---

## 通过源码构建特定版本的 Python

以下是在 `Ubuntu 20.04` 上构建 `Python 3.12.0` 的步骤。

1. 下载源码包

    ```bash
    wget https://www.python.org/ftp/python/3.12.0/Python-3.12.0.tar.xz
    ```

2. 下载依赖包

    ```bash
    apt install build-essential zlib1g-dev libncurses5-dev libgdbm-dev libnss3-dev libssl-dev libreadline-dev libffi-dev libsqlite3-dev wget libbz2-dev
    ```

3. 解压源码包

    ```bash
    tar -xvf Python-3.12.0.tar.xz
    ```

4. 运行配置脚本

    ```bash
    cd Python-3.12.0
    ./configure --enable-optimizations
    ```

5. 编译

    ```bash
    make -j8    # 多线程编译
    ```

6. 安装

    ```bash
    make altinstall
    ```

7. 验证

    ```bash
    python3.12 -V
    ```