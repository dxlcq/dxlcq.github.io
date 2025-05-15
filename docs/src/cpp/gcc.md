
* **安装**

    1. 下载 [mingw-w64](https://github.com/niXman/mingw-builds-binaries/releases) `x86_64` `posix` `seh` `ucrt`

    2. 解压

    3. 添加至环境变量 `GCC\XY\mingw-w64\bin`





* **编译安装指定版本**

    1. [下载（日本镜像站）](https://ftp.tsukuba.wide.ad.jp/software/gcc/releases/)

    2. 解压缩
        ```sh
        tar -zxvf *.tar.gz
        cd gcc*
        ```

    2. 安装依赖
        ```sh
        sudo apt install libgmp-dev libmpfr-dev libmpc-dev
        ```

    3. 配置编译选项
        ```sh
        ./configure \
            --enable-languages=c,c++ \
            --prefix='/usr/local/gcc-x.y.z' \
            --disable-multilib
        ```
    
    4. 编译
        ```sh
        make -j$(nproc)
        ```
    
    5. 安装
        ```sh
        sudo make install
        ```

    * 在手动安装 GCC 后，使用 `cmake -B build -DCMAKE_CXX_COMPILER=/usr/local/gcc-14.2.0/bin/g++` 来指定编译器

    * 临时运行 `LD_LIBRARY_PATH=/usr/local/gcc-14.2.0/lib64:$LD_LIBRARY_PATH ./xxx` 来指定运行时的动态链接库路径

<br>

* **多个版本切换**

    1. 设置候选项
        ```shell
        sudo update-alternatives --install /usr/bin/gcc gcc /usr/bin/gcc-11 110
        sudo update-alternatives --install /usr/bin/g++ g++ /usr/bin/g++-11 110
        sudo update-alternatives --install /usr/bin/gcc gcc /usr/local/gcc-14.1.0/bin/gcc 140
        sudo update-alternatives --install /usr/bin/g++ g++ /usr/local/gcc-14.1.0/bin/g++ 140
        ```
    
    2. 切换版本
        ```shell
        sudo update-alternatives --config gcc
        ```

    3. 删除多余候选项
        ```shell
        sudo update-alternatives --remove gcc /usr/local/gcc-14.1.0/bin/gcc
        sudo update-alternatives --remove g++ /usr/local/gcc-14.1.0/bin/g++
        ```

## Linux-use

* 指定输出文件名字
    ```shell
    g++ main.cpp -o main
    ```
* 指定 `c++` 标准
    ```shell
    g++ main.cpp -std=c++26
    ```
* 指定编译器优化
    
    ```shell
    g++ main.cpp -O2
    ```
    
    * `-O0` 无优化
        * 效果：不进行任何优化，生成的代码与源代码结构一致，方便试
        * 适用：开发和调试阶段，用于方便调试和查找问题
    * `-O1` 基本优化（缺省）
        * 效果：应用基本的优化策略，如内联函数、去除未使用的变量等
        * 适用：提供一些优化，但不会显著增加编译时间，适用于大多情况
    * `-O2` 标准优化
        * 效果：包括更多的内联、循环展开、消除不必要的指令等优化略
        * 适用：提供更多的性能优化，适用于发布版本，编译时间可能增加
    *  `-O3` 更高级的优化
        * 效果：包括更多复杂的优化，如矢量化、函数调用优化等
        * 适用：对性能要求非常高的应用，但可能增加编译时间，不建用于所有应用
    * `-Ofast` 最高级的优化
        * 效果：启用所有可能的优化，包括不遵循标准的优化，例如非准数学优化和禁用安全性检查
        * 适用：对极致性能要求的应用，但可能引入精度损失和不可预的行为

* 输出文件带调试信息
    ```shell
    g++ main.cpp -g
    ```

* 生成动态库
    ```shell
    g++ -shared -fPIC -o libutil.so util.cpp
    ```

* 连接动态库
    ```shell
    g++ main.cpp -lssl
    ```
    * `-lssl` 是 `OpenSSL` 的 `SSL` 库
    ```shell
    g++ main.cpp -I/usr/local/openssl-x.y.z/include -L/usr/local/openssl-x.y.z/lib -lssl
    ```
    * 在手动连接动态库时，通常还需要指定头文件搜索位置




## mingw-w64

[下载地址](https://github.com/niXman/mingw-builds-binaries/releases)

mingw-w64 是一个跨平台的编译器，可以在 Windows 上编译出 Linux 下可执行文件。

| 系统架构 | 位数 |
|:-:|:-:
| **i686** | 32位 |
| **x86-64**| 64位 | 

| 接口标准 | 跨平台性 | 主要特点 |
|:-------:|:-------:|:-------:|
| **POSIX**  | 跨UNIX和类UNIX系统   | 标准化的UNIX系统API，跨平台 |
| **MCF**    | 仅限于Windows平台    | Windows API集成，提供高级功能 |
| **Win32**  | 仅限于Windows平台    | 提供Windows操作系统的各种功能 |

| 异常处理与调试 | 用途 | 应用范围 | 使用场景 | 
|:-:|:-:|:-:|:-:|
| **SEH** | 仅限于Windows平台，处理Windows特定的异常 | 处理程序运行时的异常，提供结构化的异常处理           | 应用程序中处理可能出现的异常情况，如文件读取失败或内存访问错误    |
| **DWARF** | 用于多种操作系统，包括Linux、Unix、macOS等             | 提供编译后程序的调试信息给调试器                  | 由编译器生成，提供源代码级别的调试信息给开发者，用于程序调试和分析    |

| 运行时库   | 版本兼容性和兼容性 | 提供的函数和特性 |
|:-:|:-:|:-:|
| **ucrt**   | 较新的Windows版本 | 标准C库函数，包括C11和POSIX标准的扩展函数 |
| **msvcrt** | 早期和某些Windows版本 | 早期的C库函数和一些扩展函数         |

值得一提，虽然 POSIX 接口标准是跨平台的，但是 Windows 并不支持 POSIX 标准，如果使用 POSIX 标准，那么程序会

<br>