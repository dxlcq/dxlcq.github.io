## 参考



<br>

---


## 进程

### IPC

#### 管道

#### 共享内存 Share Memory

1. 在物理内存中直接开辟一片空间

2. 将空间映射到各个进程的虚拟地址空间的共享区

3. 进程通过虚拟地址直接对共享内存进行操作

```c
// write.c
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

#define MAXSIZE 1024 * 4  // 共享内存对象的大小，用于映射

int main() {
    // 创建一个共享内存对象 /dev/shm
    // __name: 共享内存对象的名称，在 /dev/shm 目录下
    // __oflag: 打开模式: 不存在就创建 | 存在就清空 | 读写
    // __mode: 权限
    int fd = shm_open("shm.test", O_CREAT | O_TRUNC | O_RDWR, 0664);
    if (fd == -1) {
        fprintf(stderr, "shm_open failed: %s\n", strerror(errno));
        return -1;
    }

    // 调整大小
    if (ftruncate(fd, MAXSIZE) == -1) {
        fprintf(stderr, "ftruncate failed: %s\n", strerror(errno));
        return -1;
    }

    // 建立映射关系
    // __addr: 映射起始地址，NULL 表示由系统决定
    // __len: 映射长度
    // __prot: 访问权限: 可读 | 可写
    // __flags: 标志位: 多个进程共享
    // __fd: 文件描述符
    // __offset: 偏移量
    char* ptr =
        (char*)mmap(NULL, MAXSIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        fprintf(stderr, "mmap failed: %s\n", strerror(errno));
        return -1;
    }

    // 关闭文件描述符，映射关系不会被删除
    // 直到所有进程都解除映射或进程终止
    close(fd);

    // 写入数据
    char data_buf = '0';
    char* data = &data_buf;  // 使用指针指向字符变量
    while (1) {
        printf("writing %c\n", *data);
        *ptr = *data;  // 写入数据到共享内存
        (*data)++;
        sleep(1);
    }

    return 0;
}
```

```c
// read.c
#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main() {
    // 创建一个共享内存对象
    int fd = shm_open("shm.test", O_RDONLY, 0);
    if (fd == -1) {
        fprintf(stderr, "shm_open failed: %s\n", strerror(errno));
        return -1;  // 打开共享内存失败
    }

    // 获取共享内存的属性
    struct stat buf;
    int ret = fstat(fd, &buf);
    if (ret == -1) {
        fprintf(stderr, "fstat failed: %s\n", strerror(errno));
        return -1;  // 获取共享内存属性失败
    }

    // 建立映射关系
    char* ptr = (char*)mmap(NULL, buf.st_size, PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED) {
        fprintf(stderr, "mmap failed: %s\n", strerror(errno));
        return -1;  // 映射失败
    }

    // 关闭文件描述符
    close(fd);

    while (1) {
        printf("reading %c\n", *ptr);  // 读取共享内存中的数据
    }

    return 0;
}
```

#### 消息队列 Message Queue

消息队列独立于发送和接收进程而存在，

1. 创建消息队列

2. 向消息队列发送/接收消息

```c
// sender.c
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
    // 创建消息队列
    // __name: 消息队列的名称，必须以 / 开头，保存在 /dev/mqueue 目录下
    // __oflag: 打开标志，O_WRONLY 表示只写，O_CREAT 表示如果不存在则创建
    mqd_t mq = mq_open("/t-mq", O_WRONLY | O_CREAT);
    if (mq == -1) {
        fprintf(stderr, "mq_open failed: %s\n", strerror(errno));
        return -1;
    }

    // 发送的消息内容
    char* data;
    *data = '0';

    // 向消息队列发送消息
    while (1) {
        int mq_status = mq_send(mq, data, sizeof(char), 0);
        if (mq_status == -1) {
            fprintf(stderr, "mq_send failed: %s\n", strerror(errno));
            return -1;
        }
        (*data)++;
        sleep(1);  // 每隔一秒发送一次消息
    }

    return 0;
}
```

```c
// receiver.c
#include <errno.h>
#include <fcntl.h>
#include <mqueue.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char** argv) {
    // 打开消息队列
    mqd_t mq = mq_open("/t-mq", O_RDONLY);
    if (mq == -1) {
        fprintf(stderr, "mq_open failed: %s\n", strerror(errno));
        return -1;
    }

    // 获取消息队列属性
    struct mq_attr attr;
    if (mq_getattr(mq, &attr) == -1) {
        fprintf(stderr, "mq_getattr failed: %s\n", strerror(errno));
        return -1;
    }

    // 分配内存存储消息内容
    // attr.mq_msgsize 是消息队列中每个消息的最大长度
    // 接收消息的缓冲区大小应该至少为 attr.mq_msgsize 字节
    char* data = (char*)malloc(attr.mq_msgsize);  // 分配内存存储字符数据
    if (data == NULL) {
        fprintf(stderr, "malloc failed: %s\n", strerror(errno));
        mq_close(mq);
        return -1;
    }

    // 从消息队列中接收消息
    while (1) {
        ssize_t bytes_received = mq_receive(mq, data, attr.mq_msgsize, NULL);
        if (bytes_received == -1) {
            fprintf(stderr, "mq_receive failed: %s\n", strerror(errno));
            return -1;
        }
        printf("Received message: %s\n", data);  // 打印接收到的消息
    }

    return 0;
}
```


#### 本地套接字

<br>

---


## 线程


<br>

---