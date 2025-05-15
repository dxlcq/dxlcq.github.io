1. **启动GDB：**
    ```sh
    gdb ac
    ```
    * `ac` 是需要调试的程序。

2. **设置断点：**
    ```sh
    break ac.cpp:main
    break ac.cpp:10
    ```
    * `break` 命令用于设置断点，可以简写为 `b`。
    * `ac.cpp:main` 是断点的位置，这里是 `ac.cpp` 文件的 `main` 函数。
    * `ac.cpp:10` 是断点的位置，这里是 `ac.cpp` 文件的第 `10` 行。
    * 如果不指定文件名，那么默认是当前文件。

3. **运行程序：**
    ```sh
    run
    ```
    * `run` 命令用于运行程序，可以简写为 `r`。

4. **单步执行：**
    ```sh
    step
    ```
    * `step` 命令用于单步执行程序，可以简写为 `s`。

5. **继续执行：**
    ```sh
    continue
    ```
    * `continue` 命令用于继续执行程序，直到遇到下一个断点，可以简写为 `c`。

6. **查看变量：**
    ```sh
    print a
    ```
    * `print` 命令用于查看变量，可以简写为 `p`。

7. **查看堆栈：**
    ```sh
    backtrace
    ```
    * `backtrace` 命令用于查看堆栈，可以简写为 `bt`。

5. **退出GDB：**
    ```sh
    quit
    ```
    * `quit` 命令用于退出GDB，可以简写为 `q`。