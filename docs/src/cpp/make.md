[官网](https://www.gnu.org/software/make/)

## setup

### linux

### windows


1. 下载 [Make](https://gnuwin32.sourceforge.net/downlinks/make.php)
2. 安装
3. 添加环境变量 `GnuWin32\bin`

<br>

---


## use

* 当前目录下存在 `Makefile` 文件
    ```
    project/
    ├── main.cpp
    └── Makefile
    ```

    ```shell
    make # 直接 make 即可
    ```

* `Makefile` 最简示例
    ```makefile
    # 声明变量
    CXX = g++                       # 编译器命令
    CXXFLAGS = -std=c++26 -O2       # 编译选项
    TARGET = main                   # 目标可执行文件名
    SRCS = main.cpp                 # 源文件列表

    all: $(TARGET)                  # 默认目标规则

    $(TARGET): $(SRCS)              # 生成可执行文件的规则
            $(CXX) $(CXXFLAGS) -o $(TARGET) $(SRCS)

    clean:                          # 清理生成的文件
            rm -f $(TARGET)

    .PHONY: all clean               # 声明伪目标，避免与文件名冲突
    ```

* `Makefile` 连接动态库
    ```makefile
    # 声明变量
    CXX = g++
    CXXFLAGS = -std=c++26
    TARGET = main
    SRCS = main.cpp

    # 需要链接的动态库列表
    LIBS = -lssl -lcrypto -lz       # OpenSSL 的 SSL 库、加密库和 zlib 库

    # 头文件和库文件路径
    INC_DIR = /usr/local/XYZ/include
    LIB_DIR = /usr/local/XYZ/lib /usr/lib

    all: $(TARGET)                  # 默认目标规则

    $(TARGET): $(SRCS)              # 生成可执行文件的规则
        $(CXX) $(CXXFLAGS) -I$(INC_DIR) -L$(LIB_DIR) -o $(TARGET) $ (SRCS) $(LIBS)

    clean:                          # 清理生成的文件
        rm -f $(TARGET)

    .PHONY: all clean               # 声明伪目标，避免与文件名冲突
    ```