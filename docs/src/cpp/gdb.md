## 参考



<br>

---

## 基础

1. **启动GDB**

    ```sh
    gdb ac
    ```

    * `ac` 是需要调试的程序

2. **设置断点**

    ```sh
    break ac.cpp:main
    break ac.cpp:10
    ```

    * `break` 用于设置断点，简写为 `b`
    * `ac.cpp:main` 是断点的位置，这里是 `ac.cpp` 文件的 `main` 函数
    * `ac.cpp:10` 是断点的位置，这里是 `ac.cpp` 文件的第 `10` 行
    * 如果不指定文件名，那么默认是当前文件

3. **取消断点**

    ```sh
    delete 1
    ```

    * `delete` 用于取消断点，简写为 `d`
    * `1` 是断点的编号，可以通过 `info breakpoints` 查看当前所有断点

3. **运行程序**

    ```sh
    run
    ```

    * `run` 用于运行程序，简写为 `r`，遇到断点时会暂停执行

    * 如果需要传递参数给程序，可以在 `run` 后面加上参数

        ```sh
        run arg1 arg2
        ```

4. **单步执行**

    ```sh
    step
    ```

    * `step` 用于单步执行程序，简写为 `s`，遇到函数会进入函数内部

5. **跳出函数**

    ```sh
    finish
    ```

    * `finish` 用于跳出当前函数，返回到调用该函数的地方，可以简写为 `fin`

5. **单步跳过**

    ```sh
    next
    ```

    * `next` 用于单步跳过函数调用，简写为 `n`，不会进入函数内部

5. **继续执行**

    ```sh
    continue
    ```

    * `continue` 用于继续执行程序，直到遇到下一个断点，可以简写为 `c`

6. **查看变量**
    ```sh
    print a
    display a
    ```

    * `print` 用于查看变量，可以简写为 `p`

    * `display` 用于在每次程序暂停时自动显示变量的值

7. **查看堆栈**

    ```sh
    backtrace
    ```

    * `backtrace` 用于查看堆栈，可以简写为 `bt`

5. **退出GDB**

    ```sh
    quit
    ```

    * `quit` 用于退出GDB，可以简写为 `q`

<br>

---

## termdebug

**启用**

```sh
:packadd termdebug
```

**使用**

```sh
:Termdebug ac
```

* `ac` 是需要调试的程序

**切换窗口**

`Ctrl + w` `w`

