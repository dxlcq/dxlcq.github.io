
## 系统

**`btop`** 状态总览

**`screenfetch`** 配置

### Process


`ps -aux` 查看所有进程

`ps -aux | grep [关键字]` 查看包含关键字的进程

`ps -p [PID]` 查看指定进程

`ps -u [USER]` 查看指定用户的进程

| USER              | PID        | %CPU    | %MEM    | VSZ(KB)      | RSS(KB)      | TTY      | STAT | START | TIME   | COMMAND              |
|-------------------|------------|---------|---------|----------|----------|----------|------|-------|--------|----------------------|
| 进程所有者的用户名 | 进程 ID    | CPU 使用率 | 内存使用率 | 虚拟内存大小 | 常驻内存集大小 | 终端类型 | 进程状态 | 启动时间 | 进程使用的 CPU 时间 | 启动该进程的命令行  |
    
* `STAT`：

    * `S` 睡眠：等待事件（等待 I/O ）

    * `s` 领导：具有子进程

    * `+` 前台进程

    * `R` 运行

    * `l` 多线程，克隆线程

    * `L` 有些页被固定在内存中，不允许交换到磁盘

    * `D` 不可中断的睡眠：等待事件完成（正在进行 I/O ）

    * `Z` 僵尸：进程已经终止，但是父进程还没有回收

`ps -ef` 多了一个 `ppid` 父进程 ID

`ps -ef --forest` 查看进程树

`pstree` 查看进程树

`kill -9 [PID]` 杀死进程，`-9` 是强制杀死

`pkill -9 [进程名]` 杀死进程

`killall -9 [进程名]` 杀死同名进程

<br>

### 守护进程

[Systemd](https://www.ruanyifeng.com/blog/2016/03/systemd-tutorial-part-two.html)

* 刷新 `sudo systemctl daemon-reload`

* 重置失败状态 `sudo systemctl reset-failed`

* 查看部分在运行的服务 `systemctl list-units --type=service --state=running | grep srv`

* 查看设置开机启动的服务 `systemctl list-unit-files --type=service | grep enabled | grep srv`

* 一个简单的守护进程模板

    ```ini
    # /etc/systemd/system/xxx.service
    [Unit]
    Description=xxx             # 服务描述
    After=network.target        # 在网络启动后启动

    [Service]
    Type=simple                 # 简单类型
    User=root                   # 运行用户
    Group=root                  # 运行用户组
    WorkingDirectory=/root      # 工作目录

    ExecStart=python3 xxx.py    # 启动命令

    Restart=always              # 总是重启
    RestartSec=10               # 重启间隔时间
    TimeoutStopSec=60           # 停止超时时间

    [Install]
    WantedBy=multi-user.target  # 多用户模式启动
    ```

