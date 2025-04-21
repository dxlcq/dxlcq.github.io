## 参考

[cyclonedds-cxx](https://github.com/eclipse-cyclonedds/cyclonedds-cxx)

[配置文件参考](https://cyclonedds.io/docs/cyclonedds/latest/config/config_file_reference.html#configuration-file-reference)

[发现配置](https://cyclonedds.io/docs/cyclonedds/latest/config/discovery-config.html#discovery-configuration)

<br>

---


## OMG DDS






<br>

---


## 编译安装

**cyclonedds**

```bash
cmake -B build -DCMAKE_INSTALL_PREFIX=./build/install
cmake --build build -j --target install
```

**cyclonedds-cxx**

```bash
cmake -B build -DCMAKE_INSTALL_PREFIX=./build/install -DCMAKE_PREFIX_PATH="../cyclonedds-0.10.5/build/install"
cmake --build build -j --target install
```

<br>

---

## IDL

IDL 用于定义语言无关的接口和数据类型

```idl
module HelloWorldData{
    struct Msg{
        long userID;
        string message;
    };
};
```


<br>

---


## cyclonedds.xml


```xml
<?xml version="1.0" encoding="UTF-8"?>
<CycloneDDS>
  <Domain>
    <General>
      <AllowMulticast>false</AllowMulticast>
    </General>
    
    <Discovery>
      <ParticipantIndex>auto</ParticipantIndex>     
      <Peers>
        <Peer Address="10.0.0.xx"/>
      </Peers>
    </Discovery>
  </Domain>
</CycloneDDS>
```

```bash
export CYCLONEDDS_URI=file://$(pwd)/cyclonedds.xml
```