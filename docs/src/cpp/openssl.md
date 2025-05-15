[官网](https://www.openssl.org/) | [下载](https://www.openssl.org/source/) | [使用文档](https://www.feistyduck.com/library/openssl-cookbook/online/) | [开发文档](https://www.openssl.org/docs/manmaster/man3/index.html)


## setup

### linux

```shell
sudo apt-get install libssl-dev
```

1. 下载 `wget` / 解压 `tar -zxvf` / 提权 `chmod +x`

2. 配置安装选项 `./config shared --prefix=/opt/OpenSSL-x.y.z --openssldir=/opt/OpenSSL-x.y.z`

3. 安装 `make && sudo make install`

4. 编写测试代码
    ```c
    #include <stdio.h>
    #include <openssl/opensslv.h>
    #include <openssl/crypto.h>

    int main() {
        // 输出 OpenSSL 版本信息
        printf("OpenSSL version: %s\n", OpenSSL_version(OPENSSL_VERSION));
        printf("OpenSSL version number: %lx\n", OpenSSL_version_num());
        return 0;
    }
    ```

5. 编译
    ```bash
    gcc a.c -I/.../openssl-x.y.z/include -L/.../openssl-x.y.z/lib64 -Wl,-rpath=/opt/openssl-x.y.z/lib64 -lssl -lcrypto
    ```


### windows

---

## use

### 生成密钥对

```shell
openssl genpkey -out pri.pem -algorithm RSA -pkeyopt rsa_keygen_bits:2048
openssl pkey -in pri.pem -pubout -out pub.pem
```

---

## dev

