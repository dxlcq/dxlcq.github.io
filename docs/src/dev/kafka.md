## 参考

* [kafka 容器](https://hub.docker.com/r/apache/kafka)

* [kafka get started](https://developer.confluent.io/get-started/c/#create-project)

<br>

---

## MQ

* 消息队列，程序间通信的一种方式

### why

* 解耦

* 异步

* 削峰

### how


### waht


<br>

---

## docker

1. 使用 docker 启动

    ```shell
    sudo docker run -d --rm -p 9092:9092 apache/kafka
    ```

2. 创建一个主题

    ```shell
    sudo docker exec -it <container_id> /opt/kafka/bin/kafka-topics.sh --bootstrap-server localhost:9092 --create --topic test-topic
    ```

3. 生产者

    ```shell
    sudo docker exec -it <container_id> /opt/kafka/bin/kafka-console-producer.sh --bootstrap-server localhost:9092 --topic test-topic
    ```

    > 输入消息后按 `Ctrl+C` 结束

4. 消费者

    ```shell
    sudo docker exec -it <container_id> /opt/kafka/bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic test-topic --from-beginning
    ```

## bin

1. 下载

    ```shell
    wget https://dlcdn.apache.org/kafka/3.9.1/kafka_2.13-3.9.1.tgz
    wget https://download.oracle.com/java/21/latest/jdk-21_linux-x64_bin.tar.gz
    ```

2. 设置环境变量

    ```shell
    export JAVA_HOME=.../jdk-21.0.10
    export PATH=$JAVA_HOME/bin:$PATH
    ```

3. 修改配置文件

    ```shell
    # config/server.properties
    # 监听地址为本机 IP 地址
    advertised.listeners=PLAINTEXT://x.x.x.x:9092
    # 单条消息最大大小 100MB
    message.max.bytes=104857600
    # log 保留时间 60 秒, 每 10 秒检查一次
    log.retention.ms=60000
    log.retention.check.interval.ms=10000
    ```

4. 后台启动 zookeeper 和 kafka

    ```shell
    ./bin/zookeeper-server-start.sh -daemon config/zookeeper.properties
    ./bin/kafka-server-start.sh -daemon config/server.properties
    ```

5. 看看有没有收到消息

    ```shell
    ./bin/kafka-console-consumer.sh --bootstrap-server localhost:9092 --topic test-topic --from-beginning
    ```

<br>

---