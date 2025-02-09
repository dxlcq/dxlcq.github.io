[语法速查](https://tonybai.com/2023/02/23/learn-go-in-10-min/)


## 上手

1. [官网](https://golang.google.cn/dl/) 康康最新版本，下载

2. 解压缩至 `/usr/local/`
    * `sudo tar -zxvf go* -C /usr/local/`

3. 配置环境变量
    * `vim ~/.bashrc`
      ```sh
      export PATH=$PATH:/usr/local/go/bin
      ```

    * 刷新
      `source ~/.bashrc`

4. 测试 `go version`

### 单个文件运行

```
── my_project/
   ├── go.mod
   ├── main.go
```

1. `mkdir my_project && cd my_project`

2. `go mod init github.com/daixll/my_project`

3. `vim main.go`

    ```go
    // main.go
    package main
    import "fmt"
    func main() {
        fmt.Println("Hello, World!")
    }
    ```

4. `go run main.go`

<br>

### 多个文件运行

```
── my_project/
   ├── go.mod
   ├── main.go
   ├── one.go
```

1. `vim one.go`

    ```go
    package main  // 在同一目录下，一定要是 main 包
    import "fmt"
    func One() {  // 首字母大写，表示可以被外部调用
        fmt.Println("Hello, one")
    }
    ```

2. `vim main.go`

    ```go
    package main
    func main() {
        One()  // 调用包中的函数
    }
    ```

3. `go run main.go one.go`


<br>

### 调用本地包

```
── my_project/
   ├── go.mod
   ├── main.go
   ├── one.go
   ├── two
       ├── two.go
```

1. `mkdir two && vim two/two.go`
  
      ```go
      package two
      import "fmt"
      func Two() {
          fmt.Println("Hello, two")
      }
      ```
2. `vim main.go`

    ```go
    package main
    import (
        "github.com/daixll/my_project/two"  // 导入本地包
    )
    func main() {
        two.Two()  // 调用包中的函数
    }
    ```

3. `vim go.mod`

    ```sh
    module github.com/daixll/my_project

    go 1.22
    // 重定向到本地
    replace github.com/daixll/my_project/two => ./two
    ```

4. `go mod tidy`

5. `go build`

6. `./my_project`



## 1 高并发支持

Go语言并行设计的牛逼之处就在于 `goroutine` 和 `channel`，基于这俩实现简单的并发编程

* `goroutine` 协程 
  * 一个进程可以拥有多个线程，一个线程可以拥有多个协程
  * 协程由程序控制（用户态），而不是由操作系统控制
  * 轻量级，没有内核切换的开销大，上下文切换很快

关于协程的底层原理和设计可以看看 **GMP**

* `Channel` 管道
  * 一种协程间的异步通信方式
    * `goroutine A` 和`goroutine B` 可以通过 `Channel` 完成通信，遵循先进先出
  * Don’t communicate by sharing memory, share memory by communicating

## 2 丰富标准库

<div class="center">

| 标准库 | 功能 |
|:--:|:--:|
| fmt | 格式化操作 |
| net | 网络库：Socket、HTTP、RPC... |
| html| 网页 |
| math | 数学 |
| strings| 字符串 |
| time | 时间 |
| ... | ... |

</div>

ps：没有有序map



## 3 完整工具链

内置了很多性能调优、测试的工具，比如CPU分析器pprof、Uber开源的用于生成火焰图的go-torch、流量拷贝工具goreplay等

## 4 快速编译

* 跨平台
  * Go程序是通过自己的 `runtime` 库实现与操作内核系统交互。
* 静态链接
  * 在编译时会将依赖库一起编译进二进制文件
* 快速编译  
  * 使用了import的引用管理方式
  * 没有模板的编译负担
  * ？


## 5 垃圾回收
垃圾回收（GC）是在后台运行一个守护线程，它的作用是在监控各个对象的状态，识别并且丢弃不再使用的对象来释放和重用资源

关于GO GC的底层原理和设计可以看看 **三色标记法**


# 基础语法

## 1 Hello World

```Go
package main

import (
  "fmt"
)

func main() {
  fmt.Println("Hello World!")
}
```

## 2 var

声明：`var name type`，var 是关键字，name 是变量名，type 是变量类型 

简短声明：`name := val`，name 是变量名，val 是表达式

```Go
// 声明一个
var a int
// 声明且初始化
var a int = 100

// 声明多个
var a, b int    
// 声明多个不同类型
var (
    a int
    b string
    c []float32
    d func() bool
    e struct {
        x int
    }
)
// 简短声明
a := 1

a, b := 6.0, "666"

// 静态变量
const a = 100   // 无须设置类型
```

匿名变量：不占用内存空间，不会分配内存。匿名变量与匿名变量之间也不会因为多次声明而无法使用。

```Go
a, _ = Get2num()    // 这个下划线就是匿名变量
```

## 3 if else

必须大括号

```Go
if a:=1; a == 1 {
    a := 1
} else if a == 0 {
    a := 2
} else {
    a := 3
}
```

## 4 for

```Go
for {
    // 死循环
}

for i := 1; i <= 10; i++{

}

for i <= 10 {
    // 循环 10 次
}
```

## 5 switch

* `case` 只要执行了就不会再选择了 
* 条件可以随便写，也就是无需选择某一变量

```Go
a := "6"
switch a {
case "1":
  fmt.Println("1")
case "2":
  fmt.Println("2")
default:
  fmt.Print("6")
}
```

```Go
switch {    // 比 if else 嵌套更清晰
case getuid() > 6:
  fmt.Println("1")
case getuid() < 6:
  fmt.Println("2")
default:
  fmt.Print("6")
}
```

## 6 array & slice

数组 `array` 的下标从 0 开始

```Go
var a [5][5]int
a[1][1] = 666
fmt.Println(a)
```

切片 `slice`

* 声明
```Go
// 直接定义一个不定长数组
var arr []int   
// 使用 make 定义一个切片
var slice []int = make([]int, 8， 16) // 第三个参数为提前预留的大小
// 简化写法
slice := make([]int, 8)
```

* 初始化
```Go
arr := []int{1, 2, 3}

a := 1
b := 2
```

* 截取（用截取做删除操作）

```Go
// 截取 [a,b) 中的内容
brr := arr[a:b]
// 不写, 就是默认从第一个元素到最后一个元素
```

* 获取长度
```Go
len(arr)  // 实际使用长度
cap(arr)  // 加上预留的长度
```

* 增加元素
```Go
arr = append(arr, 1, 2, 3)  // 可以添加多个元素
```

## 7 map

* 声明
  
```Go
cnt := make(map[string]int, 6) // map[key]val, 预留空间6, 可以不写

cnt := map[string]int { // 创建多个
  "123": 666,
  "555": 777,
  "777": 888,
}
```

* 获取键值对

```Go
v := cnt["123"]     // 获取 val
k, v := cnt["123"]  // 获取 key val
```

## 8 range

用于 for 循环中迭代数组(array)、切片(slice)、通道(channel)或集合(map)的元素

```Go
for _, v := range cnt { // 善用匿名变量
  fmt.Println(v)
}
```

## 9 结构体函数

```Go
// 定义结构体
type T struct {
  a int
  b int
  c string
}

// 结构体 T 的一个函数
func (u T) ADD() int {
  return u.a + u.b
}

// 初始化 与 使用
x := T{1, 2, "666"}
var y T
fmt.Println(x.ADD(), y)
```

## 10 字符串处理

* 包

```Go
import (
  "strings"
)
```

* 是否含有子串
```Go
strings.Contains(s, "substr")
```

* 子串出现的次数

```Go
strings.Count(s, "substr")
```

* 串是否以 pre 开始
```Go
strings.HasPrefix(s, "pre")
```

* 串是否以 suf 结束

```Go
strings.HasSuffix(s, "suf")
```

* 还有一些，后面写吧

## 11 JSON处理

* 结构体 -> json

  1. u 一个带内容结构体
  ```Go
  u := &T{
    1,
    []int{1, 2, 3},
    true,
  }
  ```

  2. 结构体(u) -> json(uJson)

  ```Go
  uJson, err := json.Marshal(u) // 转换
  if err != nil {
	  fmt.Println("错误")
  }
  ```

  3. 输出
  ```Go
  fmt.Println(string(uJson)) // 输出需要 string()
  ```

* json -> 结构体

  1. nu 一个空的结构体
  ```Go
  nu := &T{}
  ```

  2. json(uJson) -> 结构体(nu)
  ```Go
  err2 := json.Unmarshal(uJson, nu)
  if err2 != nil {
    fmt.Println("错误")
  }
  ```

  1. 输出
  ```Go
  fmt.Println(nu)
  ```

## 12 时间处理

## 13 错误处理

* Go 直接提供一个错误类型 error

```Go
// 一个函数
func DIV(a int, b int) (int, error) {
  if b == 0 {
    return -1, errors.New("g")
  }
  return a / b, errors.New("")
}

// 使用
a, msg := DIV(10, 2)

if msg == errors.New("") {
  fmt.Println(a, msg)
} else {
  fmt.Println(a, msg)
} 
```

## 14 进程信息





---
html:
    toc: true           # 打开侧边目录
    toc_depth: 6        # 打开的目录层级
    toc_float: true     # 侧边悬停
    collapsed: true     # 只显示高级别标题(2)
    smooth_scroll: true # 页面滚动,标题变化
    number_sections: false  # 显示标题编号
    theme: united
---

# 进阶

## goroutine 和 channel 实例

A 线程协程 0~9 个数字

B 线程协程 计算 接受到的数字 的平方

主函数输出 B 协程计算的

```Go
package main

import (
    "fmt"
)

func main() {
    src := make(chan int)      // 无缓冲通道
    dest := make(chan int, 10) // 有缓冲通道
    go func() { // A
        defer close(src)
        for i := 1; i <= 10; i++ {
            src <- i
        }
    }()

    go func() { // B
        defer close(dest)
        for i := range src {
            dest <- i * i
        }
    }()

    for i := range dest {
        fmt.Println(i)
    }
}
```

* 无缓冲通道
    发送方和接收方，必须同时发送和接受，也就是同步

* 有缓冲通道
    发送方可以先将东西放到通道，接收方需要了就从通道拿


## lock 并发安全

```Go
package main

import (
	"fmt"
	"sync"
	"time"
)

var (
	x    int64
	lock sync.Mutex
)

func addWithlock() {
	for i := 0; i < 2e3; i++ {
		lock.Lock()
		x += 1
		lock.Unlock()
	}
}

func addWithoutlock() {
	for i := 0; i < 2e3; i++ {
		x += 1
	}
}

func main() {

	x = 0
	for i := 0; i < 5; i++ {
		go addWithoutlock() // 无锁加法
	}
	time.Sleep(time.Second)
	fmt.Println("无锁：", x)

	x = 0
	for i := 0; i < 5; i++ {
		go addWithlock() // 有锁加法
	}
	time.Sleep(time.Second)
	fmt.Println("有锁：", x)
}
```
> 输出：
    
    无锁：9767
    有锁：10000

在不加锁的情况下，x 被5个协程同时访问，某些+1加在了错误的 x 上面
因此，共享内存需要特别注意并发安全

## WaitGroup 协程计数器

创建一个协程计数器 `var wg sync.WaitGroup`
协程数量增加 1 个 `wg.Add(1)`
协程数量减少 1 个 `wg.Done()`
等待协程数量归零 `wg.Wait()`

```Go
package main

import (
	"fmt"
	"sync"
)

var wg sync.WaitGroup

func hello(i int) {
	defer wg.Done() // 当函数结束，代表一个协程结束
	fmt.Println(i)
}

func main() {
	for i := 0; i < 5; i++ {
		wg.Add(1)
        go hello(i)
	}
	wg.Wait() // 等待协程全部结束
}
```

# 依赖管理




# 高质量代码

高质量代码

* 正确可靠
  * 边界条件是否考虑完备
  * 异常情况处理，稳定性保证

* 简洁清晰
  * 易读易维护

错误处理
* 简单错误
  * 在其他地方不需要捕获这个错误
  * 优先使用 `errors.New` 直接表示简单错误
  
* 错误的 wrap（包）
  * 当嵌套调用多个函数的时候，error嵌套另一个error，需要生成一个跟踪链
  * 优先使用 `fmt.Errorf` 中的 `%w` 来将错误关联至错误链中

* 错误判定
  * 在错误链上获取特定种类的错误
  * 优先使用 `errors.As`

# 性能优化

## benchmark
[参考这篇文章](https://geektutu.com/post/hpg-benchmark.html)


# 测试

## 单元测试

## Mock测试

## 基准测试









# HTTP 路由

<details>

使用 Gin 框架定义了四个 HTTP 路由，分别对应 `HTTP GET`、`POST`、`PUT` 和 `DELETE` 请求。
当用户访问 `/book` 路径并发送不同类型的 HTTP 请求时，服务器会返回相应的 JSON 对象，其中包含一条消息，表示请求的类型。

> 不使用路径名 `/book` 来区分 HTTP 请求

```Go
package main

import (
	"github.com/gin-gonic/gin"
	"net/http"
)

func main() {
	r := gin.Default()

	r.GET("/book", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{
			"method": "GET",
		})
	})

	r.POST("/book", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{
			"method": "POST",
		})
	})

	r.PUT("/book", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{
			"method": "PUT",
		})
	})

	r.DELETE("/book", func(c *gin.Context) {
		c.JSON(http.StatusOK, gin.H{
			"method": "DELETE",
		})
	})

	err := r.Run(":9090")
	if err != nil {
		return
	}
}
```


</details>

---

# HTML 渲染

## 模板的使用


<details>

1. 创建模板 `*.tmpl`

```HTML
<!DOCTYPE html>
<html lang="zh-CN">

<head>
    <title> Hello </title>
</head>

<body>

{{ with .uu1 }}
<p>Hello {{ .Name }} {{ .Age }} {{ .Gender }}</p>
{{ end }}

{{ if lt .uu1.Age 20}}
未成年
{{ else }}
成年人
{{ end }}

{{ range $idx, $hb := .hobby }}
   <p> {{ $idx }} - {{ $hb }} </p>
{{ else }}
    空空如也
{{ end }}

</body>
</html>
```

2. 解析模板
    * `ParseFiles` 函数会读取指定的模板文件，并将其解析为模板对象

3. 渲染模板
    * `Execute` 渲染一个模板
    * 第一个参数是一个 `io.Writer` 类型的变量，表示要将模板的输出写入到哪里；
    * 第二个参数是一个 `interface{}` 类型的变量，表示要传递给模板的数据。

```cpp
package main

import (
	"fmt"
	"html/template"
	"net/http"
)

type U struct {
	Name   string
	Age    int
	Gender string
}

// 这两个参数分别用于向客户端发送响应和获取客户端发送的请求信息
func sayHello(w http.ResponseWriter, r *http.Request) {
	// 解析模板
	t, err := template.ParseFiles("./learn/hello.tmpl")
	if err != nil {
		fmt.Println("模板解析错误：%v", err)
		return
	}
	// 渲染模板

	u1 := U{
		"奥特曼",
		18,
		"性别男，爱好女",
	}

	hobbyList := []string{
		"唱跳",
		"rap",
		"篮球",
	}

	err = t.Execute(w, map[string]interface{}{
		"uu1":   u1,
		"hobby": hobbyList,
	})

	if err != nil {
		fmt.Println("模板渲染错误：%v", err)
	}
}

func main() {
	// 当服务器收到对根路径 / 的 HTTP 请求时，它会调用 f1 函数来处理该请求
	http.HandleFunc("/", sayHello)
	err := http.ListenAndServe(":9090", nil)
	if err != nil {
		fmt.Println("HTTP server start failed, err:%v", err)
		return
	}
}
```

</details>

## 模板的函数

<details>

```HTML
<!DOCTYPE html>
<html lang="zh-CN">

<head>
    <title>自定义模板函数</title>
</head>

<body>

{{ onevar . }}

</body>
</html>
```


使用自定义的变量 `onevar`

```Go
package main

import (
	"fmt"
	"net/http"
	"text/template"
)

func f1(w http.ResponseWriter, r *http.Request) {
	// 定义一个函数 f2
	//f2 := func(name string) (string, error) {
	//	return name + "六六六", nil
	//}

	// 定义模板
	// 解析模板
	// template.New的名字 要与模板名字对应
	t, err := template.New(
		"f1.tmpl").Funcs(template.FuncMap{ // 需要使用一个函数
		"onevar": func(name string) (string, error) { // 一个自定义的函数
			return name + "六六六", nil
		},
	}).ParseFiles("./learn/f1.tmpl") // 解析模板

	if err != nil {
		fmt.Println("模板解析失败！因为：%v", err)
		return
	}
	// 渲染模板
	name := "奥特曼"
	t.Execute(w, name)
}

func main() {
	http.HandleFunc("/", f1)
	err := http.ListenAndServe(":9090", nil)
	if err != nil {
		fmt.Println("HTTP 服务启动失败！因为：%v", err)
		return
	}
}

```

</details>

## 模板的嵌套

<details>

```html
<!DOCTYPE html>
<html lang="zh-CN">

<head>
    <title> 嵌套模板 </title>
</head>

<body>

{{/*嵌套另一个单独的模板文件*/}}
{{template "f2.tmpl"}}

{{/*嵌套另一个define定义的模板*/}}
{{template "f3.tmpl"}}

</body>
</html>

{{ define "f3.tmpl" }}
    <ol>
        <li> 吃饭 </li>
        <li> 睡觉 </li>
        <li> 打豆豆 </li>
    </ol>
{{ end }}
```

```Go
package main

import (
	"fmt"
	"html/template"
	"net/http"
)

func f(w http.ResponseWriter, r *http.Request) {
	// 定义模板
	// 解析模板
	t, err := template.ParseFiles("./learn/f1.tmpl", "./learn/f2.tmpl")
	if err != nil {
		fmt.Println("模板解析失败！因为：%v", err)
		return
	}
	// 渲染模板
	t.Execute(w, nil)
}

func main() {
	http.HandleFunc("/", f)
	err := http.ListenAndServe(":9090", nil)
	if err != nil {
		fmt.Println("HTTP 服务启动失败！因为：%v", err)
		return
	}
}

```

</details>

## 模板的继承

<details>

1. 创建一个基础模板

其中需要被替换的块，`content` 是块的名字，`.`是传进去一个变量
```html
 {{block "content" .}}{{end}}
```

```html
<!DOCTYPE html>
<html lang="zh-CN">

<head>
    <title> 模板继承 </title>
    <style>
    *{
        margin: 0;
    }
    .nav {
        height: 50px;
        width: 100%;
        position: fixed;
        top: 0;
        background-color: burlywood;
    }
    .main {
        margin-top: 50px;
    }
    .menu {
        width: 20%;
        height: 100%;
        position: fixed;
        left: 0;
        background-color: cornflowerblue;
    }
    .center {
        text-align: center;
    }
    </style>
</head>

<body>

<div class="nav"></div>
<div class="main">
    <div class="menu"></div>
    <div class="content center">

        {{/* 不同的地方，定义一个块 */}}
        {{block "content" .}}{{end}}

    </div>
</div>

</body>
</html>
```

2. 创建一个块模板

这里指明你继承的是哪一个基础模板，以及传进来了那些变量
`{{template "base.tmpl" .}}`

块的名字要和根模板中的名字，一一对应
`{{define "content"}}{{end}}`

```html
{{/*继承根模板*/}}
{{template "base.tmpl" .}}

{{/*重新定义块模板*/}}
{{define "content"}}
    <h1> 这里的内容，完整的替换过去 </h1>
    <h1> {{.}} </h1>
{{end}}
```

3. 渲染模板

`template.ParseFiles` 依次传入根模板、块模板
`t.ExecuteTemplate` 依次传入需要渲染的块模板、变量

```Go
package main

import (
	"fmt"
	"html/template"
	"net/http"
)

func ff(w http.ResponseWriter, r *http.Request) {
	t, err := template.ParseFiles("./learn/base.tmpl", "./learn/index.tmpl")
	if err != nil {
		fmt.Printf("模板解析失败！因为：%v\n", err)
		return
	}
	// 渲染模板
	msg := "666"
	t.ExecuteTemplate(w, "index.tmpl", msg)
}

func main() {
	http.HandleFunc("/ff", ff)
	err := http.ListenAndServe(":9090", nil)
	if err != nil {
		fmt.Println("HTTP 服务启动失败！因为：%v", err)
		return
	}
}

```


</details>
