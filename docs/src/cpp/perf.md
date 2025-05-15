1. **安装 perf**
    ```sh
    sudo apt install linux-tools-common linux-tools-generic linux-tools-`uname -r`
    ```
    * `linux-tools-common`：Linux 性能分析工具的公共文件。
    * `linux-tools-generic`：Linux 性能分析工具的通用文件。
    * `linux-tools-<version>`：Linux 性能分析工具的内核版本文件。
        * `uname -r` 命令用于查看内核版本。

    ```sh
    perf -v # 验证是否安装成功
    ```

2. **下载 FlameGraph**
    

    FlameGraph 是一个生成火焰图的工具。

    ```sh
    git clone https://github.com/brendangregg/FlameGraph.git
    ```

3. **使用** 

    ```sh
    sudo perf record -g ./a.out sleep 10
    ```

    * `perf record` 命令用于记录性能数据。
    * `-g` 选项用于记录调用图。
    * `./a.out` 需要记录性能的程序。
    * `sleep 10` 程序运行 10 秒。

    ```sh
    sudo perf script -i perf.data &> perf.unfold 
    ```

    * `perf script` 命令用于将性能数据转换为可读的格式。
    * `-i` 选项用于指定输入文件。
    * `perf.data` 是性能数据文件。
    * `&> perf.unfold` 用于将输出重定向到 `perf.unfold` 文件。

    ```sh
    sudo FlameGraph/stackcollapse-perf.pl perf.unfold &> perf.folded
    ```

    * `stackcollapse-perf.pl` 命令用于将性能数据转换为火焰图的输入格式。
    * `perf.unfold` 是性能数据文件。
    * `&> perf.folded` 用于将输出重定向到 `perf.folded` 文件。

    ```sh
    sudo FlameGraph/flamegraph.pl perf.folded > perf.svg
    ```

    * `flamegraph.pl` 命令用于生成火焰图。
    * `perf.folded` 是火焰图需要的性能数据文件。
    * `> perf.svg` 用于将输出重定向到 `perf.svg` 文件。


<br>

---