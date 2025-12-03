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

1. 后台启动 zookeeper 和 kafka

    ```shell
    ./bin/zookeeper-server-start.sh -daemon config/zookeeper.properties
    ./bin/kafka-server-start.sh -daemon config/server.properties
    ```

<br>

---


## C++

```Dockerfile
FROM ubuntu:latest AS builder

RUN apt update && apt install -y \
    build-essential cmake pkg-config \
    librdkafka-dev libglib2.0-dev
```

生成镜像：

```shell
sudo docker build -t dxlcq/kafka_builder_cpp .
```

编译：

```shell
sudo docker run --rm -v /kafka-c-getting-started:/kafka-c-getting-started -w /kafka-c-getting-started/build dxlcq/kafka_builder_cpp cmake ..
sudo docker run --rm -v /kafka-c-getting-started:/kafka-c-getting-started -w /kafka-c-getting-started/build dxlcq/kafka_builder_cpp cmake --build .
```

消费者：

```shell
sudo docker run --rm --net=host -v /kafka-c-getting-started:/kafka-c-getting-started -w /kafka-c-getting-started/build dxlcq/kafka_builder_cpp ./consumer
```

生产者：

```shell
sudo docker run --rm --net=host -v /kafka-c-getting-started:/kafka-c-getting-started -w /kafka-c-getting-started/build dxlcq/kafka_builder_cpp ./producer
```