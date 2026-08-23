## 参考


<br>

---

## 磁盘性能

* 测试磁盘的写入速度

```sh
time dd if=/dev/zero of=test.t bs=4k count=200000
```

* 清除缓存

```sh
sudo sync && sudo sh -c 'echo 3 > /proc/sys/vm/drop_caches'
```

* 测试磁盘的读取速度

```sh
time dd if=test.t of=/dev/null bs=4k
```

<br>

---

## 挂载磁盘

1. 查看磁盘分区情况 `lsblk`

2. 创建分区 `fdisk /dev/nvme0n1`

    1. `n` 新建分区

    2. 主分区 (直接回车, 默认 p 主分区)

    3. 分区号 (直接回车, 默认 1)

    4. 起始扇区 (直接回车, 默认 2048)

    5. 结束扇区 (直接回车, 默认 100% 的大小)

    6. `w` 保存并退出

3. 格式化分区 `mkfs.ext4 /dev/nvme0n1p1`

4. 创建挂载点 `mkdir -p /mnt/nvme2t`

5. 持久化挂载

    1. 获取分区 UUID `blkid /dev/nvme0n1p1`

    2. 编辑 `/etc/fstab` 文件

        ```conf
        UUID=你的UUID /mnt/nvme2t ext4 defaults 0 2
        ```

6. 挂载分区 `mount -a`

<br>

---

## 临时挂载


## 