## 参考

* [廖雪峰的git教程](https://www.liaoxuefeng.com/wiki/896043488029600)

* [License](https://opensource.org/licenses)

<br>

---

## License

### MIT 

`Massachusetts Institute of Technology License`

> 我只想安安静静写代码，你干嘛都与我无关

1. 版权申明
    * 文档和软件中需保留原始版权信息

2. 免责条款
    * 原始作者对软件使用引发的任何损害不负责

3. 使用
    * 随便用

4. 修改
    * 随便改

5. 再分发
    * 随意

<br>

### BSD 

`Berkeley Software Distribution License`

> 打广告的时候，别说你是基于我的，丢脸

1. 版权申明
    * 文档和软件中需保留原始版权信息

2. 免责条款
    * 原始作者对软件使用引发的任何损害不负责

3. 使用
    * 随便用，但是宣传软件的时候，不要带上我

4. 修改
    * 随便改

5. 再分发
    * 随意

<br>

### GPL

`GNU General Public License`

> 一日GPL，一生GPL

1. 版权申明
    * 文档和软件中需保留原始版权信息

2. 免责条款
    * 原始作者对软件使用引发的任何损害不负责

3. 使用
    * 随便用

4. 修改
    * 随便改，但是改了之后的代码不能闭源

5. 再分发
    * 依旧遵循 GPL

<br>

### LGPL

`GNU Lesser General Public License`

> 更灵活的GPL

* 允许动态连接闭源库

* 虽然灵活，但这并不意味着你可以闭源

<br>

### Apache

1. 版权申明
    * 文档和软件中需保留原始版权信息

2. 免责条款
    * 原始作者对软件使用引发的任何损害不负责

3. 使用
    * 随便用

4. 修改
    * 随便改

5. 再分发
    * 修改后的软件，分发时需要带上原始版权信息

<br>

---

## 安装

### Linux

```shell
sudo apt install git # 安装 git
git --version        # 验证 git 安装成功
```

<br>

### Windows

[git 官网](https://git-scm.com/downloads)

<br>

---

## 首次使用

### 初始化仓库

在需要管理的目录（工作区）下，执行以下命令：

```shell
git init
```

> 将目标目录初始化成 git 可以管理的仓库，会生成一个 `.git` 目录
>
> 同时，会创建一个 `master` 分支，看不见，但是存在

<br>

### 设置名字和邮箱

此操作的目的，是为了追踪每次操作，究竟是谁做的，我们一般将其存储在 `config` 中，配置文件有三个级别，权重从高到底：

1. 仓库 `local`，此配置文件只对 **当前仓库** 有效

2. 全局 `global`，此配置文件对 **当前用户** 有效

3. 系统 `system`，此配置文件对 **全局** 有效

所在位置：

**Windows**：

1. `local`： `.git/config`

2. `global`：`C:\Users\username\.gitconfig`

3. `system`：`C:\Program Files\Git\etc\gitconfig`


**Linux**：

1. `local`：`.git/config` 

2. `global`：`~/.gitconfig`

3. `system`：`/etc/gitconfig`

<br>

### 文件追踪 / 移动到暂存区

```shell
git add 目标文件
```

或者追踪所有文件：

```shell
git add .
```

<br>

### 将暂存区提交到本地仓库

目标文件提交到本地仓库的当前分支：

```shell
git commit -m "提交说明"
```

<br>

### 将本地仓库推送到远程仓库

将本地仓库推送到远程仓库，需要使用 `SSH key` 进行身份验证；私钥存储在本地，公钥存储在远程仓库；当你推送的时候，远程仓库会验证你的身份，如果验证通过，则可以推送

1. 生成 `SSH key`

    [在线生成](https://bkssl.com/ssl/ssh_generate)

2. 将公钥添加到远程仓库（[github](https://github.com/) or [gitee](https://gitee.com/)）
    
    **Windows**：`C:\Users\username\.ssh\id_rsa.pub`
    
    **Linux**：`~/.ssh/id_rsa.pub`

    登录远程仓库，`setting` -> `SSH keys` -> `New SSH key`
    
    > `title`：填写公钥的名字
    
    > `key`：填写公钥的内容

3. 在远程仓库中新建仓库

4. 添加远程仓库
    
    ```shell
    git remote add origin 远程仓库地址
    ```

    > `origin` 是远程仓库的别名，可以自定义

5. 推送到远程仓库
    
    ```shell
    git push origin master
    ```

    > 如果远程仓库没有 `master` 分支，则会自动创建一个 `master` 分支

如果是通过账号密码进行身份验证

* 记住账号密码

    ```shell
    git config --local credential.helper store
    ```

<br>

### 将远程仓库拉取到本地仓库

* `git fetch origin`
    
    > 下载但不合并

* `git merge origin/master`
    
    > 合并分支

* `git pull origin`
    
    > 下载并合并

* `git clone 远程仓库地址`
    
    > 在本地创建一个远程仓库的克隆（副本）

<br>

---

## 子模块

* 拉取含有子模块的仓库

    ```shell
    git clone --recursive 远程仓库地址
    ```

* 添加子模块

    ```shell
    git submodule add 远程仓库地址 子模块目录
    ```

* 删除子模块

    ```shell
    git rm 子模块目录
    ```

* 查看子模块

    ```shell
    git submodule
    ```

* 更新子模块

    ```shell
    git submodule update
    ```

<br>

---


## 123

### 创建分支

```shell
git branch 分支名
```

<br>

### 设置默认编辑器

```shell
git config --local core.editor "vim"
```

<br>

---

## 查看状态

### 仓库

```shell
git status
```

* 显示位于哪个 **分支**

* 显示 **暂存区** 的信息

* 显示 **未跟踪** 的文件

<br>

### 设置

```shell
git config --级别 -l
```

> `--级别` 可以省略，会显示最终三个配置文件计算后的配置信息

<br>

### 所有分支

```shell
git branch
```

> `*` 表示当前分支

<br>

### 远程仓库

```shell
git remote -v
```

* 远程仓库的别名和地址

<br>

### 查看提交历史

```shell
git log
```

> 显示从最近到最远的提交日志

> 简化输出：`git log --pretty=oneline`

<br>

### 查看命令历史

```shell
git reflog
```

> 显示从最近到最远的命令日志

> 可以看到每一次命令的 `commit id`

<br>

---

## 修改

### 更改名字和邮箱

```shell
git config --级别 user.name "新名字"
git config --级别 user.email "新邮箱"
```

<br>

### 修改上一次提交的信息

```shell
git commit --amend
```

> 如果使用的是 `nano` 编辑器，按 `Ctrl + X` 退出，然后输入 `Y` 保存，最后按 `Enter` 退出

<br>

### 从暂存区移除文件

```shell
git reset 目标文件
```

这个命令本质上是

```shell
git reset --mixed commit_id
```

> 从暂存区移除文件，但是不会删除文件

> `commit_id` 可以省略，默认是 `HEAD`

> 意思是将暂存区的文件恢复到 `commit_id` 的状态

<br>

### 撤销本次提交

1. 保留工作区的修改
    ```shell
    git reset --soft HEAD^
    ```
    > 撤销本次提交，但是保留工作区的修改

    > `HEAD^` 表示上一次提交，`HEAD^^` 表示上上次提交，以此类推

1. 删除工作区的修改
    
    ```shell
    git reset --hard HEAD^
    ```

    > 撤销本次提交，同时删除工作区的修改

<br>

### 删除远程仓库地址

```shell
git remote rm origin
```

> 删除远程仓库的别名为 `origin` 的仓库（地址）
> 仅仅是删除了别名，远程仓库并没有被删除

<br> 

### 切换分支

* 切换到指定分支

    ```shell
    git checkout 分支名
    ```

<br> 

---

## 国区操作

### 代理

**设置代理**

    ```shell
    git config --local http.proxy http://192.168.19.19:7890
    git config --local https.proxy http://192.168.19.19:7890
    ```

* 取消代理

    ```shell
    git config --local --unset http.proxy
    git config --local --unset https.proxy
    ```

### 同时推送到多个远程仓库

1. 再添加一个需要推送的远程仓库

    ```shell
    git remote set-url --add origin 远程仓库地址
    ```

2. 推送到远程仓库

    ```shell
    git push origin
    ```

> 注意，此方案只适用于多个远程仓库的代码完全一致的情况
>
> 因为我们只是给 `origin` 添加了多个 `URL`
>
> 虽然效果上看起来是推送到了多个仓库，但是实际上只是推送到了一个仓库

### gitee 记住账号密码

```shell
git config --local credential.helper store
```

<br>

---

## .gitignore

忽略某些文件和目录

### 忽略文件或目录

```
a.txt
a/
```

### 忽略某类文件

```
*.txt
```

### 例外规则

```
!a.txt
```