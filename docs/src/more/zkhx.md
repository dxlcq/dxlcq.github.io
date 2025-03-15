# zkhx

## DataManage dev environment

* docker build

    ```Dockerfile
    FROM ubuntu:latest

    RUN apt update && apt install -y \
        build-essential cmake vim \
        openssh-server wget apt-transport-https ca-certificates curl gpg \
        python3-dev \
        libcurl4-openssl-dev \
        libssl-dev \
        libpq-dev \
        uuid-dev
    
    # ssh login (use your own key)
    RUN wget -P /root/.ssh "https://dxlcq.cn/public/authorized_keys"
    RUN mkdir /run/sshd

    # vim chinese support
    RUN echo "set encoding=utf-8" >> /etc/vim/vimrc

    RUN cp -r /usr/include/postgresql/* /usr/include
    
    CMD ["/etc/init.d/ssh", "restart","-D"]
    ```

    ```bash
    sudo docker build -t dxlcq/datamanage .
    ```

* docker run

    ```bash
    sudo docker run --rm -d -p 22001:22 -v /DataManage:/DataManage dxlcq/datamanage
    ```

<br>

---

## Qt


### Qt dev environment

* docker build

