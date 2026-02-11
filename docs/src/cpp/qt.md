## 参考


<br>

---

## SETUP

### LINUX

1. 注册 QT：[官网](https://login.qt.io/register)

2. 下载 QT：[官网](https://www.qt.io/download-qt-installer-oss)

    装一些依赖：

    ```bash
    sudo apt install -y \
        libxcb-cursor0 libxcb-cursor-dev \
        mesa-common-dev libgl1-mesa-dev \
        libxcb-xinerama0 \
        
        libxkbcommon-x11-0 libxkbcommon-dev\
        libvulkan-dev
    ```



3. 添加环境变量：

    ```shell
    export PATH=/home/user/Qt/x.y.z/gcc_64/bin:$PATH
    export LD_LIBRARY_PATH=/home/user/Qt/x.y.z/gcc_64/lib:$LD_LIBRARY_PATH
    ```

4. vscode

    1. 安装插件 `C/C++`

    2. 配置 `.vscode/c_cpp_properties.json`

        ```json
        {
            "configurations": [
                {
                    "name": "Qt",
                    "includePath": [
                        "${workspaceFolder}/**",
                        "/home/user/Qt/x.y.z/gcc_64/include/**"
                    ],
                    "compilerPath": "/usr/bin/gcc"
                }
            ],
            "version": 4
        }
        ```

5. hello qt

    1. 源文件：`main.cpp`

        ```cpp
        #include <QApplication>
        #include <QPushButton>
        #include <QMessageBox>

        int main(int argc, char *argv[]) {
            QApplication app(argc, argv);

            // 创建一个按钮
            QPushButton button("点击我！", nullptr);

            // 当按钮被点击时，连接到应用程序的quit()槽函数
            QObject::connect(&button, &QPushButton::clicked, [&]() {
                // 显示一个消息框
                QMessageBox::information(nullptr, "消息", "按钮被点击了！");
            });

            // 显示窗口
            button.show();

            // 运行应用程序的事件循环
            return app.exec();
        }
        ```

    2. `CMakeLists.txt`

        ```CMakeLists.txt
        cmake_minimum_required(VERSION 3.28)
        project(HelloQt VERSION 1.0.0.0313)
        
        # C++ 标准配置
        set(CMAKE_CXX_STANDARD 23)
        set(CMAKE_CXX_STANDARD_REQUIRED ON)
        
        # 查找 Qt 库
        find_package(Qt6 REQUIRED COMPONENTS
            Core
            Widgets
        )
        
        # 可执行文件
        add_executable(HelloQt main.cpp)
        
        # 链接 Qt 库
        target_link_libraries(HelloQt PRIVATE
            Qt6::Core
            Qt6::Widgets
        )
        ```
    
    3. 编译

        ```shell
        mkdir build && cd build
        cmake ..
        cmake --build .
        ```

6. debug

    1. 配置 `.vscode/launch.json`：

        ```json
        {
            "version": "0.2.0",
            "configurations": [
                {
                    // 配置的名称，可以自定义
                    "name": "debug",
                    // 配置类型为cppdbg，表示C++调试
                    "type": "cppdbg",
                    // 请求类型为launch，表示启动调试
                    "request": "launch",
                    // 可执行文件路径为当前打开文件的路径和文件名（不带扩展名）
                    "program": "${fileDirname}/${fileBasenameNoExtension}",
                    // 是否在程序入口处停止
                    "stopAtEntry": true,
                    // 当前工作目录为VS Code的工作区目录
                    "cwd": "${workspaceFolder}",
                    // 调试器类型为gdb
                    "MIMode": "gdb",
                    // 指定gdb的可执行文件路径
                    "miDebuggerPath": "gdb",
                    // 配置调试会话的环境变量，这里设置 DISPLAY 以便远程调试（非必需）
                    // 可以设置为 x11 的转发的 DISPLAY 环境变量，localhost:10.0
                    "environment": [
                        {
                            "name": "DISPLAY",
                            "value": ":10.0"
                        }
                    ],
                }
            ]
        }
        ```

    2. 依次点击：`运行` -> `启动调试`，即可开始调试
        
        1. 继续：运行到下一个断点
        2. 逐过程：逐行执行，遇到函数则跳过函数的内部执行
        3. 单步调试：单步执行，如果遇到函数则进入函数内部执行
        4. 单步跳出：执行到当前函数的最后一行，然后跳出函数


### WINDOWS

### Source

1. 下载 [https://download.qt.io/official_releases/qt/](https://download.qt.io/official_releases/qt/)

2. `./configure -prefix /opt/Qt -opensource -confirm-license`

3. `make -j && make install`

<br>

---

## 打包！分享给 👧

### LINUX


### WINDOWS

1. 将你的 `main.exe` 文件单独复制到一个干净的文件夹中；

2. 打开终端 `Qt 6.x.x (MinGW)`，到新建的文件夹，执行：
    
    ```shell
    windeployqt main.exe
    ```
    
    * 它会自动分析你的应用程序，找出它所依赖的Qt模块和其他依赖项，并将这些文件复制到应用程序的目录中。
    
    * 此时，软件已经可以在其他（同一平台）电脑上运行了。
    
    * 为了更好的用户体验，我们可以将其打包成一个绿色版的软件，👧 可以点击 `main.exe` 直接运行！

3. 下载安装 [Enigma Virtual Box](https://www.enigmaprotector.com/cn/downloads.html)；

4. 使用 Enigma Virtual Box 将 `main.exe` 打包：
    
    1. 在 `Enter input File Name:` 中打开 `main.exe`，会自动填写 `output`；
    
    2. 点击 `Add` -> `Add Folder Recursive`，选择 `main.exe` 所在的文件夹，
    默认就好；
    
    3. 点击 `Files Options`，勾选 `Files Virtualization` 和 `Compress Files`；
    
    4. 点击 `Process`，等待打包完成；

<br>

---


## QML && project

<br>

---




## 第三方库

### qicstable

[qicstable](https://gitlab.com/ics-qicstable/qicstable)

* Build the DLL

    ```bash
    qmake qicstable.pro && make -j8
    ```

    ```bash
    echo "export LD_LIBRARY_PATH=/home/jiao/Desktop/qtp/qicstable-master/lib:\$LD_LIBRARY_PATH" >> ~/.bashrc
    source ~/.bashrc
    ```

* Build the Docs

    1. `../bin/generate_docs`






<br>

---


















## 信号与槽

简单理解，当你在页面点击一个按钮，这个点击就是 **信号**，而后端的处理函数就是 **槽**。
同理，当你在页面输入一个字符，这个输入就是 **信号**，而后端的处理函数就是 **槽**。

QT 官方对信号与槽的描述如下：
>Qt 的核心思想是信号与槽机制。信号与槽是一种机制，用于在对象间进行通信。信号在特定事件发生时被发射，槽是在信号被发射时被调用的函数。Qt 中，任何 Qt 对象都能发送信号和处理信号。信号与槽是一种非常灵活和松耦合的通信机制，它允许对象间的通信完全独立于彼此的实现。

**值得一提** 的是，信号与槽的连接是 **动态** 的，也就是说，你可以在程序运行的过程中，动态的连接信号与槽，也可以动态的断开信号与槽的连接。

**信号与槽的新语法** 

* 之前 信号与槽连接的方式：

    ```cpp
    connect(sender, SIGNAL(valueChanged(QString, QString)),
            receiver, SLOT(updateValue(QString)));

    // 具体的
    connect(button, SIGNAL(clicked()), this, SLOT(showMessage()));
    ```

    官网对这种方式的弊端进行了详细的说明：[Qt 5中信号和槽的新语法](https://www.qt.io/zh-cn/blog/2012/08/07/new-signals-slots-syntax-in-qt5)

    <br>

* 目前 信号与槽连接的方式：

    ```cpp
    connect(sender, &Sender::valueChanged, receiver, &Receiver::updateValue);

    // 具体的
    connect(button, &QPushButton::clicked, this, &MyWidget::showMessage);

    // 使用 lambda 表达式
    connect(button, &QPushButton::clicked, [=](){ 
        QMessageBox::information(nullptr, "消息", "按钮被点击了！"); 
        });
    ```

<br>

---

## 简单窗口和基本控件

```
QObject                 # 所有类的基类，提供了对象的基本功能（属性、信号与槽...）
  └── QWidget           # 所有窗口部件的基类，提供了窗口部件的基本功能（尺寸、位置、标题...）
      ├── QMainWindow   # 主窗口类，提供了主窗口的基本功能（菜单栏、工具栏、状态栏...）
      ├── QLabel        # 标签类，用于显示文本或图像
      ├── QPushButton   # 按钮类，用于响应用户的点击
      ├── QLineEdit     # 单行文本输入框类，用于接收用户的输入
      ├── QComboBox     # 下拉列表类，用于从列表中选择一个选项
      ├── QCheckBox     # 复选框类，用于从多个选项中选择一个或多个
      ├── QRadioButton  # 单选按钮类，用于从多个选项中选择一个
      ├── QSlider       # 滑块类，用于从一个范围中选择一个值
      ├── QProgressBar  # 进度条类，用于显示任务的进度
      └── ...

QLayout             # 所有布局管理器的基类，提供了布局管理器的基本功能
  ├── QHBoxLayout   # 水平布局
  ├── QVBoxLayout   # 垂直布局
  ├── QGridLayout   # 网格布局
  └── ...

QEvent              # 所有事件的基类，提供了事件的基本功能
  ├── QMouseEvent   # 鼠标事件
  ├── QKeyEvent     # 键盘事件
  ├── QResizeEvent  # 窗口大小改变事件
  ├── QCloseEvent   # 窗口关闭事件
  └── ...
  
QPainter    # 绘图设备，用于绘制各种图形
QPixmap     # 图片设备，用于显示图片
QImage      # 图片设备，用于显示图片
QPen        # 画笔，用于绘制各种图形的轮廓
QBrush      # 画刷，用于绘制各种图形的背景
QColor      # 颜色，用于设置画笔和画刷的颜色
...
```

## Leg 1 Hello Qt

Qt 创建一个窗口非常简单，只需要创建一个 `QWidget` 对象，然后调用 `QWidget` 的 `show()` 方法即可。

不过在这之前，我们先了解一下 `QApplication` 类，它是 Qt 程序的入口，也是 Qt 程序的核心对象，每个 Qt 程序都必须 **有且仅有一个** `QApplication` 对象。

1. 应用程序的初始化。
    * 命令行参数的解析。
    * 资源文件的加载：例如应用图标，各种按钮的图片等。
    * 初始化第三方库和服务：例如数据库服务。

2. 事件循环。
    * 通过调用 `exec()` 方法进入事件循环。

3. 处理系统事件。
    * 确保事件（鼠标点击、键盘输入）被传递给适当的窗口部件进行处理。

4. 退出应用程序。
    * 用户关闭主窗口，它负责安全地关闭所有窗口并释放所有资源。
    * 或调用 `quit()` 方法安全地退出事件循环。

5. 跟踪应用程序的状态。
    * 例如，`QApplication` 类提供了 `applicationStateChanged()` 信号，当应用程序的状态发生变化时，就会发射这个信号。

因此，我们的程序应该是这样的：

```cpp
#include <QApplication>

int main(int argc, char *argv[]){
    QApplication app(argc, argv);   // 创建一个应用程序对象
    return app.exec();              // 进入事件循环
}
```

程序有了，但是没有窗口，我们需要创建一个窗口，然后显示出来，
很有必要，创建一个主窗口类：

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>

class MainWindow : public QMainWindow   // 创建一个主窗口类
{                                       // 继承自QMainWindow
    Q_OBJECT                            // 使用Qt的信号与槽机制需要这个宏

public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();

private:
    // 在这里声明私有成员变量和私有方法
};
```

`Q_OBJECT` 宏是使用 Qt 的信号与槽机制必须的，它会在编译阶段自动将 `moc` 文件（元对象编译器）插入到源文件中，这个文件中包含了信号与槽的实现。

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent) // 这里的parent是可选的
    : QMainWindow(parent)               // 构造函数的初始化列表
{
    // 在这里进行主窗口的初始化操作
    this -> setWindowTitle("Hello Qt!");// 设置窗口标题
}

MainWindow::~MainWindow()
{
    // 在这里进行资源的清理工作（如果需要）
}
```

在 `main.cpp` 中，我们需要创建一个 `MainWindow` 对象，然后显示出来：

```cpp
MainWindow *w = new MainWindow();   // 创建一个主窗口对象
w->show();                          // 显示主窗口
```

窗口中的内容是空的，我们可以尝试在窗口中显示一些文字：

```cpp
// MainWindow.h
#include <QLabel>   // 包含标签类的头文件
// ...
private:
    QLabel *_label; // 声明一个标签
// ...
```
    
```cpp
// MainWindow.cpp
this -> _label = new QLabel(this);  // 为其分配内存
this -> _label -> setText("Hello Qt!!!");   // 设置标签文本
```

<br>

源代码及参见：[Leg1](https://github.com/daixll/A_Tour_of_Qt/tree/main/Leg1)

---

## Leg 2 布局管理器

为了能够控制标签的位置，我们需要使用布局管理器，布局管理器是 Qt 提供的一种自动布局机制，它能够根据窗口的大小自动调整窗口部件的位置和大小。

Qt 常见的三种布局管理器：
* 水平布局：`QHBoxLayout`
* 垂直布局：`QVBoxLayout`
* 网格布局：`QGridLayout`

我们这里使用垂直布局：

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QLabel>

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    QWidget     *_centralWidget;// 声明一个中央部件
    QVBoxLayout *_layout;       // 声明一个垂直布局管理器
    QLabel      *_labeltext;    // 声明一个文本标签
    QLabel      *_labelimg;     // 声明一个图片标签
};
```

布局管理器通常需要附着在一个特定的窗口部件上，这个窗口部件被称为中央部件（central widget）。

通过调用 `setCentralWidget(centralWidget)`，将整个布局应用到主窗口。

> Q：为什么要使用中央部件？而不是直接将布局应用到主窗口？
> 
> * 当你将布局管理器设置为主窗口时，它会直接影响主窗口的整体布局，包括菜单栏、工具栏等。而将布局管理器设置为中央部件的布局管理器，只会影响中央部件内部的子部件，不会影响其他部分的布局，这样更加灵活。
> * 主窗口是一个顶级窗口，可以包含多个子部件，而中央部件是主窗口的一个特殊子部件，它会自动占据主窗口的中央区域。

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Leg 2 布局管理器");

    _centralWidget  = new QWidget();
    _layout         = new QVBoxLayout();
    _labeltext      = new QLabel();
    _labelimg       = new QLabel();

    setCentralWidget(_centralWidget);     // 设置中央部件
    _centralWidget -> setLayout(_layout); // 设置中央部件的布局管理器
    _layout -> addWidget(_labeltext);   // 将文本标签添加到布局管理器
    _layout -> addWidget(_labelimg);    // 将图片标签添加到布局管理器

    // 设置标签的内容
    _labeltext -> setText("Leg 2 布局管理器");         // 设置文本标签
    _labelimg  -> setPixmap(QPixmap("img/cqvie.jpg"));// 设置图片标签
    // 设置标签的对齐方式为居中
    _labeltext -> setAlignment(Qt::AlignCenter);
    _labelimg  -> setAlignment(Qt::AlignCenter);
}

MainWindow::~MainWindow()
{
    delete _labelimg;
    delete _labeltext;
    delete _layout;
    delete _centralWidget;
}
```


显然，只有这几种布局是不够的，但如果布局可以嵌套，那么就可以实现更加复杂的布局。

我们尝试在现在的基础上，在上层添加一个网格布局：

```cpp
// MainWindow.h
// ...
private:
    QVBoxLayout *_vLayout;      // 声明一个垂直布局管理器
    QGridLayout *_gLayout;      // 声明一个网格布局管理器
    QLabel      _labeltext_1,   // 创建 6 个文本标签  
                _labeltext_2,
                _labeltext_3,
                _labeltext_4,
                _labeltext_5,
                _labeltext_6;
```



```cpp
// MainWindow.cpp
_vLayout        = new QVBoxLayout();
_gLayout        = new QGridLayout();
_labelimg       = new QLabel();

setCentralWidget(_centralWidget);       // 设置中央部件
_centralWidget -> setLayout(_vLayout);  // 设置中央部件的布局管理器

_vLayout -> addLayout(_gLayout);        // 将网格布局管理器添加到垂直布局管理器
_vLayout -> addWidget(_labelimg);       // 将图片标签添加到垂直布局管理器

// 将 6 个文本标签添加到网格布局管理器，并且设置内容
_gLayout -> addWidget(&_labeltext_1, 0, 0);
_gLayout -> addWidget(&_labeltext_2, 0, 1);
_gLayout -> addWidget(&_labeltext_3, 0, 2);
_gLayout -> addWidget(&_labeltext_4, 1, 0);
_gLayout -> addWidget(&_labeltext_5, 1, 1);
_gLayout -> addWidget(&_labeltext_6, 1, 2);
_labeltext_1.setText("C"); _labeltext_1.setAlignment(Qt::AlignCenter);
_labeltext_2.setText("Q"); _labeltext_2.setAlignment(Qt::AlignCenter);
_labeltext_3.setText("V"); _labeltext_3.setAlignment(Qt::AlignCenter);
_labeltext_4.setText("I"); _labeltext_4.setAlignment(Qt::AlignCenter);
_labeltext_5.setText("E"); _labeltext_5.setAlignment(Qt::AlignCenter);
_labeltext_6.setText("!"); _labeltext_6.setAlignment(Qt::AlignCenter);

// 设置图片标签，并且设置为居中
_labelimg  -> setPixmap(QPixmap("img/cqvie.jpg"));
_labelimg  -> setAlignment(Qt::AlignCenter);
```

<br>

源代码及参见：[Leg2](https://github.com/daixll/A_Tour_of_Qt/tree/main/Leg2)

---

## Leg 3 按钮与文本输入框

现在的窗口，都只是单一的显示内容，没有任何交互，我们可以添加一些按钮，来实现一些交互。

> 输入一串小写字母，点击按钮，将其转换为大写字母。

* **左边**：文本输入框，用于输入小写字母；
* **中间**：按钮，用于转换；
* **右边**：文本显示框，用于显示大写字母。

> * 按钮：`QPushButton`

> * 单行文本输入框：`QLineEdit` 
> * 多行文本输入框：`QTextEdit`

我们在这里使用水平布局，单行文本输入框。

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QLineEdit>
#include <QPushButton>
#include <QMessageBox>

class MainWindow : public QMainWindow{
    Q_OBJECT                  

public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();

private:
    QWidget     _centralWidget;
    QHBoxLayout _hLayout;       // 水平布局
    QLineEdit   _input, _output;// 文本框
    QPushButton _button;        // 按钮

    void _onButtonClicked();    // 按钮点击的槽函数
};
```

1. 首先将界面写出来；
2. 点击按钮时：
    1. 获取输入文本框的内容；
    2. 检测输入是否合法；
        * 不合法则弹出警告框；
    3. 将输入转换为大写；
    4. 将转换后的内容设置到输出文本框中。

```cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    setWindowTitle("Leg 3 按钮与文本框");
    
    setCentralWidget(&_centralWidget);  // 设置中心窗口
    _centralWidget.setLayout(&_hLayout);// 设置中心窗口的布局

    _hLayout.addWidget(&_input);    // 将文本框添加到布局中
    _hLayout.addWidget(&_button);   // 将按钮添加到布局中
    _hLayout.addWidget(&_output);   // 将文本框添加到布局中

    _button.setText("转换");        // 设置按钮的文本
    _output.setReadOnly(true);      // 设置输出文本框为只读

    // 连接按钮的点击信号与槽函数
    connect(&_button, &QPushButton::clicked, this, &MainWindow::_onButtonClicked);
}

void MainWindow::_onButtonClicked(){
    QString input = _input.text();  // 获取输入文本框的内容
    if (input.isEmpty()){           // 检测输入是否为空
        QMessageBox::warning(this, "警告", "输入不能为空");
        return;                     // 如果为空，弹出警告框
    }

    for (auto &c : input){          // 检测输入是否是小写字母
        if (c < 'a' || c > 'z'){    // 如果不是小写字母，弹出警告框
            QMessageBox::warning(this, "警告", "输入必须是小写字母");
            return;
        }
    }

    QString output = input.toUpper();   // 将输入转换为大写
    _output.setText(output);            // 将转换后的内容设置到输出文本框中
}

MainWindow::~MainWindow(){}
```

<br>

源代码及参见：[Leg3](https://github.com/daixll/A_Tour_of_Qt/tree/main/Leg3)

---


## Mission 1 计算器 🧮

> 在此节之前，需要再完成的几个简单任务： 
> 
>   1. 多行的大写转小写
>       * 左输入，中按钮，右输出
>   
>   2. 十进制转二/八进制
>       * 一个按钮将十进制转换为二进制
>       * 一个按钮将十进制转换为八进制
>   
>   3. 密码强度检查
>       * 长度需要超过 8 位，包含大写，小写，数字，特殊字符
>       * 检查结果通过弹出框显示
>           `QMessageBox::information(this, "title", "text");`
>
>   4. 模拟登录
>       * 先注册，再登录
>       * 注册后的信息，保存在任意 `.txt` 中
>       * 程序重新启动后，可以直接登录

设计一个简单的计算器，要求：

1. 输入框：用于输入数字和运算符；
2. 输出框：用于显示结果；
3. 操作符：`+`、`-`、`*`、`/`；
4. 数字：`0`、`1`、`2`、`3`、`4`、`5`、`6`、`7`、`8`、`9`；
5. 删除：`D`；
6. 清空：`C`。

<br>

源代码及参见：[Mission1](https://github.com/daixll/A_Tour_of_Qt/tree/main/Mission1)

> 此代码仅供参考，为使得代码更加简洁：
> 1. 没有进行错误处理。
> 2. 不支持高精度。
> 3. 不支持小数。 
> ...

同学们可以自行对 `calc.h` 进行修改，使得其支持更多的运算符和更高的精度。

<br>

---

## Leg 4 单选、多选

#### 单选

在一组单选框中，只能选择一个。

> 单选按钮 `QRadioButton`

```cpp
// MainWindow.h
private:
    QButtonGroup    *_one_group;        // 单选按钮组
    QRadioButton    *_one_A;            // 单选按钮
    QRadioButton    *_one_B;
    QRadioButton    *_one_C;

    QLabel          *_one_res;          // 存放单选选择结果
    void            _one_clicked();     // 单选按钮组的选择结果
```

```cpp
// MainWindow.cpp
// 设置单选按钮的文本
_one_A->setText("马克思");
_one_B->setText("列宁");
_one_C->setText("毛泽东");
// 将单选按钮添加到垂直布局
_vLayout->addWidget(_one_A);
_vLayout->addWidget(_one_B);
_vLayout->addWidget(_one_C);
// 将单选按钮添加到单选按钮组
_one_group->addButton(_one_A);
_one_group->addButton(_one_B);
_one_group->addButton(_one_C);
// 设置单选按钮组的选择结果
connect(_one_group, &QButtonGroup::buttonClicked, this, MainWindow::_one_clicked);
```

```cpp
// MainWindow.cpp
void MainWindow::_one_clicked(){
    if(_one_A->isChecked()){
        _one_res->setPixmap(QPixmap("./img/mks.jpg"));
    } else if(_one_B->isChecked()){
        _one_res->setPixmap(QPixmap("./img/ln.jpg"));
    } else if(_one_C->isChecked()){
        _one_res->setPixmap(QPixmap("./img/mzd.jpg"));
    }
}
```

#### 多选

给定多个选项，可以选择多个。

> 复选按钮 `QCheckBox`

```cpp
// MainWindow.h
QVBoxLayout     *_vLayout2;         // 垂直布局

QButtonGroup    *_two_group;        // 复选按钮组
QCheckBox       *_two;              // 复选按钮

QLabel          *_two_res;          // 存放复选选择结果
void            _two_clicked();     // 复选按钮组的选择结果
```

```cpp
// 设置为不互斥
_two_group->setExclusive(false);
for(int i = 0; i < 4; i++){
    _vLayout2->addWidget(&_two[i]); // 将复选按钮添加到垂直布局
    _two_group->addButton(&_two[i]);// 将复选按钮添加到复选按钮组
}
// 设置复选按钮的文本
_two[0].setText("披萨");
_two[1].setText("汉堡");
_two[2].setText("薯条");
_two[3].setText("热狗");
// 设置复选按钮组的选择结果
connect(_two_group, &QButtonGroup::buttonClicked, this, MainWindow::_two_clicked);
```

```cpp
// MainWindow.cpp
void MainWindow::_two_clicked(){
    QString res = "";
    if(_two[0].isChecked()){
        res += "披萨 ";
    }
    if(_two[1].isChecked()){
        res += "汉堡 ";
    }
    if(_two[2].isChecked()){
        res += "薯条 ";
    }
    if(_two[3].isChecked()){
        res += "热狗 ";
    }
    _two_res->setText(res);
}
```

<br>

---


## Leg 5 菜单栏与快捷键

菜单栏是主窗口的重要组成部分，它们是由 `QMainWindow` 类提供的。
在很多情况下，我们需要在菜单栏中添加一些菜单，然后在菜单中添加一些动作。

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QMenuBar>
#include <QMenu>
#include <QAction>
#include <QMessageBox>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     *_centralWidget;
    QMenuBar    *_menuBar;   // 菜单栏

    QMenu       *_file;      // 文件
        QAction     *_new;      // 新建
        QAction     *_open;     // 打开

    QMenu       *_help;      // 工具
        QAction     *_about;    // 关于

    void newFile();
    void openFile();
    void about();
};
```

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{   
    _centralWidget  = new QWidget();
    _menuBar        = new QMenuBar();
    _file           = new QMenu();
        _new        = new QAction();
        _open       = new QAction();
    _help           = new QMenu();
        _about      = new QAction();

    setWindowTitle("Leg 4 菜单与快捷键");
    setCentralWidget(_centralWidget);   // 设置中心窗口
    setMenuBar(_menuBar);               // 设置菜单栏

    _file = _menuBar->addMenu("文件");  // 添加 "文件菜单" 到 "菜单栏" 中
    _new->setText("新建");              // 设置 "new动作" 的文本
    _file->addAction(_new);             // 将 "new动作" 添加到 "文件菜单" 中
    _open->setText("打开");
    _file->addAction(_open);

    _help = _menuBar->addMenu("帮助");
    _about->setText("关于");
    _help->addAction(_about);

    connect(_new, &QAction::triggered, this, &MainWindow::newFile);
    connect(_open, &QAction::triggered, this, &MainWindow::openFile);
    connect(_about, &QAction::triggered, this, &MainWindow::about);
}

void MainWindow::newFile(){
    QMessageBox::information(this, "新建", "新建文件");
}

void MainWindow::openFile(){
    QMessageBox::information(this, "打开", "打开文件");
}

void MainWindow::about(){
    QMessageBox::information(this, "关于", "Leg 4 菜单与快捷键");
}

MainWindow::~MainWindow(){
    delete _centralWidget;
    delete _menuBar;
    delete _file;
    delete _new;
    delete _open;
    delete _help;
    delete _about;
}
```

一般的，我们会在菜单栏中添加一些快捷键，这样可以提高用户的使用效率。

```cpp
// MainWindow.h
// ...
private:
    QAction *_new, *_open, *_about;
```

```cpp
// MainWindow.cpp
// ...
_new->setShortcut(QKeySequence("Ctrl+N"));
_open->setShortcut(QKeySequence("Ctrl+O"));
_about->setShortcut(QKeySequence("Ctrl+A"));
```

现在，就可以通过快捷键来触发菜单栏中的动作了。

<br>

---


## Leg 6 列表

列表，显示一组数据，其和选择控件大同小异。

> 列表控件 `QListWidget`

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QListWidget>
#include <QLineEdit>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:

    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:

    void _onSelect(QListWidgetItem* item);

    QWidget*        _centralWidget; // 中心窗口
    QHBoxLayout*    _layout;        // 水平布局
    QListWidget*    _listWidget;    // 列表
    QLineEdit*      _lineEdit;      // 文本框
};
```

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 6 列表");
    _centralWidget  = new QWidget();
    _layout         = new QHBoxLayout();
    _listWidget     = new QListWidget();
    _lineEdit       = new QLineEdit();

    setCentralWidget(_centralWidget);
    _centralWidget -> setLayout(_layout);
    _layout -> addWidget(_listWidget);
    _layout -> addWidget(_lineEdit);

    _lineEdit -> setReadOnly(true);

    _listWidget -> addItem("鱼香肉丝");
    _listWidget -> addItem("宫保鸡丁");
    _listWidget -> addItem("糖醋排骨");

    connect(_listWidget, &QListWidget::itemClicked, this, &MainWindow::_onSelect);
}

MainWindow::~MainWindow(){
    delete _centralWidget;
    delete _layout;
    delete _listWidget;
    delete _lineEdit;
}

void MainWindow::_onSelect(QListWidgetItem* item){
    _lineEdit -> setText(item -> text());
}
```

<br>

---

## Leg 7 下拉列表

在若干选项中选择一个。

> 下拉列表 `QComboBox`

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QCompleter>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     _centralWidget; // 中心窗口
    QHBoxLayout _layout;        // 水平布局
    QComboBox   _comboBox;      // 下拉框
    QPushButton _button;        // 按钮
    QMessageBox _messageBox;    // 消息框
};
```

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 7 下拉列表");
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    _centralWidget.setLayout(&_layout);         // 设置中心窗口的布局
    _layout.addWidget(&_comboBox);              // 将下拉框添加到布局中
    _layout.addWidget(&_button);                // 将按钮添加到布局中

    _comboBox.addItem("鱼香肉丝");               // 添加下拉框的选项
    _comboBox.addItem("宫保鸡丁");
    _comboBox.addItem("糖醋排骨");

    _button.setText("确定");                    // 设置按钮的文本

    connect(&_button, &QPushButton::clicked, this, [this](){
        QMessageBox::information(nullptr, "提示", "你选择了：" + _comboBox.currentText());
    });
}

MainWindow::~MainWindow(){}
```

<br>

---

## Mission 2 模糊选择 🧾

在下拉列表中，输入一个字符串，下拉列表中的选项会根据输入的字符串进行模糊匹配，然后将匹配的选项显示出来。

```cpp
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QComboBox>
#include <QPushButton>
#include <QMessageBox>
#include <QCompleter>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     _centralWidget; // 中心窗口
    QHBoxLayout _layout;        // 水平布局
    QComboBox   _comboBox;      // 下拉框
    QPushButton _button;        // 按钮
    QMessageBox _messageBox;    // 消息框
};
```

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"
#include <fstream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Mission2 模糊搜索");
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    _centralWidget.setLayout(&_layout);         // 设置中心窗口的布局
    _layout.addWidget(&_comboBox);              // 将下拉框添加到布局中
    _layout.addWidget(&_button);                // 将按钮添加到布局中

    // 读取文件
    std::ifstream ifs("data.txt");
    std::string line;
    while (std::getline(ifs, line))
        _comboBox.addItem(QString::fromStdString(line));

    // 设置下拉框可编辑
    _comboBox.setEditable(true);
    // 设置下拉框的模糊搜索
    _comboBox.setCompleter(new QCompleter(_comboBox.model()));


    // 设置按钮的文本
    _button.setText("确定");
    
    // 设置按钮的点击事件
    connect(&_button, &QPushButton::clicked, this, [this](){
        QMessageBox::information(nullptr, "提示", "你选择了：" + _comboBox.currentText());
    });
}

MainWindow::~MainWindow(){}
```

<br>

---

## Leg 8 进度条

> 进度条 `QProgressBar`

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QProgressBar>
#include <QPushButton>
#include <QMessageBox>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget         _centralWidget; // 中心窗口
    QHBoxLayout     _layout;        // 水平布局
    QProgressBar    _progressBar;   // 进度条
    QPushButton     _button;        // 按钮
};
```

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg8 进度条");
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    _centralWidget.setLayout(&_layout);         // 设置中心窗口的布局
    _layout.addWidget(&_progressBar);           // 将进度条添加到布局中
    _layout.addWidget(&_button);                // 将按钮添加到布局中

    // 设置进度条的范围
    _progressBar.setRange(0, 100);
    // 设置进度条的当前值
    _progressBar.setValue(0);

    // 设置按钮的文本
    _button.setText("点击增加进度条的值");

    // 通过空格键来控制进度条的增长
    connect(&_button, &QPushButton::clicked, &_progressBar, [&](){
        if(_progressBar.value() == 100)
            QMessageBox::information(this, "提示", "进度条已经满了");
        _progressBar.setValue(_progressBar.value() + 1);
    });
}

MainWindow::~MainWindow(){}
```

<br>

---

## Leg 9 滑块

> 滑块 `QSlider`

```cpp
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QSlider>
#include <QLabel>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget         _centralWidget; // 中心窗口
    QHBoxLayout     _layout;        // 水平布局
    QSlider         _slider;        // 滑动条
    QLabel          _label;         // 标签
};
```

```cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg9 滑动条");
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    _centralWidget.setLayout(&_layout);         // 设置中心窗口的布局
    
    _layout.addWidget(&_slider);        // 将滑动条添加到布局中
    _layout.addWidget(&_label);         // 将标签添加到布局中

    _slider.setRange(0, 99);   // 设置滑动条的范围
    _slider.setOrientation(Qt::Horizontal); // 设置滑动条的方向
    _slider.setValue(49);       // 设置滑动条的当前值

    _label.setText("50");       // 设置标签的文本

    // 连接信号和槽
    connect(&_slider, &QSlider::valueChanged, this, [=](int value){
        _label.setText(QString::number(value)); // 将滑动条的值转换为字符串并设置为标签的文本
    });
}

MainWindow::~MainWindow(){}
```

<br>

---

## Leg 10 调整控件大小与位置

> 调整控件大小与位置 `setGeometry()`

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QPushButton>
#include <QSlider>
#include <QLabel>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    bool ck(int x, int y);          // 检查是否越界
    QWidget         _centralWidget; // 中心窗口
    QPushButton     _button_up,
                    _button_down,
                    _button_left,
                    _button_right;  // 按钮 上下左右
    QSlider         _slider;        // 滑动条
    QLabel          _label;         // 图片
};
```

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("leg10 设置大小");
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    this -> setFixedSize(1080, 720);            // 设置窗口大小，不可调整

    // 设置按钮
    _button_up.setParent   (&_centralWidget);
    _button_down.setParent (&_centralWidget);
    _button_left.setParent (&_centralWidget);
    _button_right.setParent(&_centralWidget);

    _button_up.setText   ("up");    
    _button_down.setText ("down");  
    _button_left.setText ("left");  
    _button_right.setText("right"); 

    _button_up.setGeometry   (100, 0, 100, 100);
    _button_down.setGeometry (100, 100, 100, 100);
    _button_left.setGeometry (0,   100, 100, 100);
    _button_right.setGeometry(200, 100, 100, 100);

    // 设置滑动条
    _slider.setParent(&_centralWidget);
    _slider.setOrientation(Qt::Horizontal);
    _slider.setRange(100, 300);
    _slider.setValue(200);
    _slider.setGeometry(0, 200, 300, 100);

    // 设置图片
    _label.setParent(&_centralWidget);
    
    QPixmap pixmap("Leg10.png");    // 读取图片 保持长宽比例缩放 图片平滑处理
    pixmap = pixmap.scaled(QSize(200, 200), Qt::KeepAspectRatio, Qt::SmoothTransformation);
    _label.setPixmap(pixmap);
    _label.setGeometry(0, 300, 200, 200);

    connect(&_button_up, &QPushButton::clicked, [&](){
        if(!ck(_label.x(), _label.y() - 10)) return;
        _label.move(_label.x(), _label.y() - 10);
    });

    connect(&_button_down, &QPushButton::clicked, [&](){
        if(!ck(_label.x(), _label.y() + 10)) return;
        _label.move(_label.x(), _label.y() + 10);
    });
    connect(&_button_left, &QPushButton::clicked, [&](){
        if(!ck(_label.x() - 10, _label.y())) return;
        _label.move(_label.x() - 10, _label.y());
    });
    connect(&_button_right, &QPushButton::clicked, [&](){
        if(!ck(_label.x() + 10, _label.y())) return;
        _label.move(_label.x() + 10, _label.y());
    });

    connect(&_slider, &QSlider::valueChanged, [&](int value){
        QPixmap pixmap("Leg10.png");    // 读取图片 保持长宽比例缩放 图片平滑处理
        pixmap = pixmap.scaled(QSize(value, value), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        _label.setPixmap(pixmap);
        _label.setGeometry(_label.x(), _label.y(), value, value);
    });
}

bool MainWindow::ck(int x, int y){
    if(x < 0 || x > 1080 || y < 0 || y > 720) return false;
    if(x < 300 && y < 300) return false;
    return true;
}

MainWindow::~MainWindow(){}
```

<br>

---

## Leg 11 滑动窗口与堆叠窗口

> 滑动窗口 `QScrollArea`

<details><summary><a href="" target="_blank"></a>滑动窗口简单实例 code</summary><br>

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QScrollArea>
#include <QLabel>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget         _centralWidget;
    QHBoxLayout     _centralLayout;

    QWidget         _contentWidget;
    QVBoxLayout     _contentLayout;

    QScrollArea     _scrollArea;
};
```

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Hello Qt!");
    this -> setCentralWidget(&_centralWidget);
    _centralWidget.setLayout(&_centralLayout);  // 设置布局
    
    _centralLayout.addWidget(&_scrollArea);     // 布局添加滑动区域

    _scrollArea.setWidgetResizable(true);       // 滑动区域可动
    _scrollArea.setWidget(&_contentWidget);     // 设置滑动区域的窗口

        _contentWidget.setLayout(&_contentLayout);  // 设置滑动区域的窗口的布局
        for(int i = 0; i < 20; i++){
            QLabel *label = new QLabel(QString("Hello Qt! %1").arg(i));
            _contentLayout.addWidget(label);
        }
}

MainWindow::~MainWindow(){}
```

</details>

> 堆叠窗口 `QStackedWidget`

<details><summary><a href="" target="_blank"></a>堆叠窗口简单实例 code</summary><br>

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QStackedWidget>
#include <QPushButton>
#include <QLabel>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget         _centralWidget;
    QHBoxLayout     _centralLayout;
    QVBoxLayout     _leftLayout;    // 左侧
    QStackedWidget  _stackedWidget; // 右侧
    
    // 三个按钮对应三个布局
    QPushButton _button[4];
    QWidget     _widget[4];
        QVBoxLayout _layout_1;
            QLabel _label_1[5];
        QHBoxLayout _layout_2;
            QLabel _label_2[5];
        QGridLayout _layout_3;
            QLabel _label_3[5];
};
```

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Hello Qt!");
    this -> setCentralWidget(&_centralWidget);
    _centralWidget.setLayout(&_centralLayout);

    _centralLayout.addLayout(&_leftLayout);
    _centralLayout.addWidget(&_stackedWidget);

    for(int i=1; i<=3; i++){
        _leftLayout.addWidget(&_button[i]);
        _button[i].setText(QString("窗口 %1").arg(i));

        _stackedWidget.addWidget(&_widget[i]);
    }
    _widget[1].setLayout(&_layout_1);
    _widget[2].setLayout(&_layout_2);
    _widget[3].setLayout(&_layout_3);

    for(int i=1; i<=4; i++){
        _layout_1.addWidget(&_label_1[i]);
        _label_1[i].setText(QString("窗口1的第%1个标签").arg(i));
    }

    for(int i=1; i<=4; i++){
        _layout_2.addWidget(&_label_2[i]);
        _label_2[i].setText(QString("窗口2的第%1个标签").arg(i));
    }

    for(int i=1; i<=4; i++){
        _layout_3.addWidget(&_label_3[i], (i-1)/2, (i-1)%2);
        _label_3[i].setText(QString("窗口3的第%1个标签").arg(i));
    }
    
    for(int i=1; i<=3; i++)
        connect(&_button[i], &QPushButton::clicked, [=](){
            _stackedWidget.setCurrentIndex(i-1);
        });
}

MainWindow::~MainWindow(){}
```

</details>

<br><br><br>

组合实现

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLayout>
#include <QListWidget>
#include <QStackedWidget>
#include <QScrollArea>
#include <QLabel>
#include <QScrollBar>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    void onItemClicked(QListWidgetItem *item);  // 点击列表项

    QWidget     _centralWidget; // 中心窗口
    QHBoxLayout _layout;        // 水平布局
    QListWidget _listWidget;    // 列表窗口
    QStackedWidget _stackedWidget;  // 堆叠窗口

    QWidget     _contextWidget1;// 右侧窗口
    QWidget     _contextWidget2;
    QWidget     _contextWidget3;

    QVBoxLayout _layout1;       // 垂直布局
    QVBoxLayout _layout2;
    QVBoxLayout _layout3;

    QScrollArea _scrollArea1;   // 滚动窗口
    QScrollArea _scrollArea2;
    QScrollArea _scrollArea3;

    QString _str1="", _str2="", _str3="";
    int cnt1=0, cnt2=0, cnt3=0;
};
```

```cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 11 滑动窗口");
    this -> setCentralWidget(&_centralWidget);
    _centralWidget.setLayout(&_layout);

    _layout.addWidget(&_listWidget);    // 左侧列表窗口
    _layout.addWidget(&_stackedWidget); // 右侧堆叠窗口

    _listWidget.addItem("窗口 1");
    _listWidget.addItem("窗口 2");
    _listWidget.addItem("窗口 3");

    _stackedWidget.addWidget(&_scrollArea1); // 右侧第一个窗口
    _stackedWidget.addWidget(&_scrollArea2); // 右侧第二个窗口
    _stackedWidget.addWidget(&_scrollArea3); // 右侧第三个窗口

    _contextWidget1.setLayout(&_layout1); // 右侧第一个窗口的布局
    _contextWidget2.setLayout(&_layout2); // 右侧第二个窗口的布局
    _contextWidget3.setLayout(&_layout3); // 右侧第三个窗口的布局

    connect(&_listWidget, &QListWidget::itemClicked, this, &MainWindow::onItemClicked);
}

MainWindow::~MainWindow(){}

void MainWindow::onItemClicked(QListWidgetItem *item){
    if(item -> text() == "窗口 1"){
        _stackedWidget.setCurrentWidget(&_scrollArea1);
        // 直接给窗口怼一个标签
        QLabel *label = new QLabel(QString("第 1 个窗口，第 %1 次点击").arg(++cnt1), &_contextWidget1);
        _scrollArea1.setWidgetResizable(true);  // 设置滚动窗口的大小可变
        _layout1.addWidget(label);
        _scrollArea1.setWidget(&_contextWidget1);
        // 定位到最后
        QScrollBar *vScrollBar = _scrollArea1.verticalScrollBar();
        vScrollBar->setValue(vScrollBar->maximum());
    }
    else if(item -> text() == "窗口 2"){
        _stackedWidget.setCurrentWidget(&_scrollArea2);
        QLabel *label = new QLabel(QString("第 2 个窗口，第 %1 次点击").arg(++cnt2)); 
        _scrollArea2.setWidgetResizable(true);  // 设置滚动窗口的大小可变
        _layout2.addWidget(label);
        _scrollArea2.setWidget(&_contextWidget2);
    }
    else if(item -> text() == "窗口 3"){
        _stackedWidget.setCurrentWidget(&_scrollArea3);
        QLabel *label = new QLabel(QString("第 3 个窗口，第 %1 次点击").arg(++cnt3));
        _scrollArea3.setWidgetResizable(true);  // 设置滚动窗口的大小可变
        _layout3.addWidget(label);
        _scrollArea3.setWidget(&_contextWidget3);
    }
}
```


<br>

---

## 绘图

## Leg 12 绘制直线

> 绘制 `QPainter`

在Qt中，绘图通过 `paintEvent` 事件来实现，当窗口需要重绘时，就会调用 `paintEvent` 事件，且不需要手动调用，只需要重写 `paintEvent` 事件即可。

在下面的例子中，我们通过 `QLineEdit` 中的内容来绘制一条直线。
当 `QLineEdit` 中的内容改变时，就会调用 `paintEvent` 事件，动态绘制直线。

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QPainter>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     _centralWidget;
    QLabel      _A, _B;
    QLineEdit   _lineEdit_A_X,
                _lineEdit_A_Y,
                _lineEdit_B_X,
                _lineEdit_B_Y;

    void paintEvent(QPaintEvent *event);
};
```

```cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 11 Qt绘图");
    this -> setFixedSize(1080, 720);            // 设置窗口大小，不可调整
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口

    _A.setParent(&_centralWidget);
    _B.setParent(&_centralWidget);
    _lineEdit_A_X.setParent(&_centralWidget);
    _lineEdit_A_Y.setParent(&_centralWidget);
    _lineEdit_B_X.setParent(&_centralWidget);
    _lineEdit_B_Y.setParent(&_centralWidget);

    _A.setText("A点坐标");
    _B.setText("B点坐标");
    _lineEdit_A_X.setText("123");
    _lineEdit_A_Y.setText("123");
    _lineEdit_B_X.setText("456");
    _lineEdit_B_Y.setText("456");

    _A.setGeometry(0, 0, 50, 50);
    _B.setGeometry(100, 0, 50, 50);
    _lineEdit_A_X.setGeometry(50, 0, 50, 25);
    _lineEdit_A_Y.setGeometry(50, 25, 50, 25);
    _lineEdit_B_X.setGeometry(150, 0, 50, 25);
    _lineEdit_B_Y.setGeometry(150, 25, 50, 25);

}

void MainWindow::paintEvent(QPaintEvent *event){
    update();
    Q_UNUSED(event);
    QPainter painter(this);
    int A_X = _lineEdit_A_X.text().toInt(),
        A_Y = _lineEdit_A_Y.text().toInt(),
        B_X = _lineEdit_B_X.text().toInt(),
        B_Y = _lineEdit_B_Y.text().toInt();
    painter.drawLine(QPoint(A_X, A_Y), QPoint(B_X, B_Y));
}

MainWindow::~MainWindow(){}
```

<br>

---

## Leg 13 绘制多种图形

`QPainter` 提供了一系列的绘图函数，可以绘制多种图形。

> * 直线：`drawLine()`
> * 矩形：`drawRect()`
> * 椭圆：`drawEllipse()`
> * 圆弧：`drawArc()`
> * 多边形：`drawPolygon()`
> * 文字：`drawText()`

同时，`QPainter` 还提供了一系列的设置函数，可以设置绘图的颜色、线宽、填充等。

> * 设置画笔颜色：`setPen()` **外部线条**
> * 设置画刷颜色：`setBrush()` **内部填充**
> * 设置线宽：`setLineWidth()`

```cpp
#pragma once

#include <QMainWindow>
#include <QWidget>
#include <QMenuBar>
#include <QLabel>
#include <QLineEdit>
#include <QInputDialog>
#include <QPainter>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     _centralWidget; // 中心窗口
    QMenuBar    _menuBar;       // 菜单栏

    QLabel      _label;         // 状态标签

    QMenu       _shape;         // 形状菜单
        QAction     _line;      // 直线
        QAction     _rectangle; // 矩形
        QAction     _ellipse;   // 椭圆
        QAction     _polygon;   // 多边形
    QString     _shape_str;     // 当前选择的形状
    
    QMenu       _color_A;       // 外部线条颜色
        QAction     _A_black;   // 黑色
        QAction     _A_red;     // 红色
        QAction     _A_green;   // 绿色
        QAction     _A_blue;    // 蓝色
    QString     _color_A_str;   // 当前选择的外部线条颜色
    
    QMenu       _color_B;       // 内部填充颜色
        QAction     _B_black;   // 黑色
        QAction     _B_red;     // 红色
        QAction     _B_green;   // 绿色
        QAction     _B_blue;    // 蓝色
    QString     _color_B_str;   // 当前选择的内部填充颜色
    
    QAction     _width;         // 线条宽度
    QString     _width_str;     // 当前选择的线条宽度

    void paintEvent(QPaintEvent *event);
};
```

```cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 12 绘制多种图形");
    this -> setFixedSize(1080, 720);            // 设置窗口大小，不可调整
    this -> setCentralWidget(&_centralWidget);  // 设置中心窗口
    this -> setMenuBar(&_menuBar);              // 设置菜单栏

    _menuBar.addMenu(&_shape);  // 添加 形状 菜单
    _shape.setTitle("形状");
        _line.setText("直线");      _shape.addAction(&_line);
        _rectangle.setText("矩形"); _shape.addAction(&_rectangle);
        _ellipse.setText("椭圆");   _shape.addAction(&_ellipse);
        _polygon.setText("多边形"); _shape.addAction(&_polygon);
    _shape_str = "直线";
    
    _menuBar.addMenu(&_color_A);// 添加 外部线条颜色 菜单
    _color_A.setTitle("外部线条颜色");
        _A_black.setText("black");   _color_A.addAction(&_A_black);
        _A_red.setText("red");     _color_A.addAction(&_A_red);
        _A_green.setText("green");   _color_A.addAction(&_A_green);
        _A_blue.setText("blue");    _color_A.addAction(&_A_blue);
    _color_A_str = "black";

    _menuBar.addMenu(&_color_B);// 添加 内部填充颜色 菜单
    _color_B.setTitle("内部填充颜色");
        _B_black.setText("black");   _color_B.addAction(&_B_black);
        _B_red.setText("red");     _color_B.addAction(&_B_red);
        _B_green.setText("green");   _color_B.addAction(&_B_green);
        _B_blue.setText("blue");    _color_B.addAction(&_B_blue);
    _color_B_str = "black";
    
    _menuBar.addAction(&_width);// 添加 线条宽度 菜单
    _width.setText("线条宽度");
    _width_str = "1";

    _menuBar.setCornerWidget(&_label);  // 设置状态标签
    _label.setAlignment(Qt::AlignRight);// 设置标签右对齐
    _label.setText("      当前选择：直线，black，black，1");

    // 连接信号与槽
    connect(&_line, &QAction::triggered, [=](){
        _shape_str = "直线";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_rectangle, &QAction::triggered, [=](){
        _shape_str = "矩形";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_ellipse, &QAction::triggered, [=](){
        _shape_str = "椭圆";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_polygon, &QAction::triggered, [=](){
        _shape_str = "多边形";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_A_black, &QAction::triggered, [=](){
        _color_A_str = "black";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_A_red, &QAction::triggered, [=](){
        _color_A_str = "red";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_A_green, &QAction::triggered, [=](){
        _color_A_str = "green";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_A_blue, &QAction::triggered, [=](){
        _color_A_str = "blue";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_B_black, &QAction::triggered, [=](){
        _color_B_str = "black";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_B_red, &QAction::triggered, [=](){
        _color_B_str = "red";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_B_green, &QAction::triggered, [=](){
        _color_B_str = "green";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_B_blue, &QAction::triggered, [=](){
        _color_B_str = "blue";
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

    connect(&_width, &QAction::triggered, [=](){
        bool ok;
        _width_str = QInputDialog::getText(this, "线条宽度", "请输入线条宽度", QLineEdit::Normal, "", &ok);
        if(!ok){
            _width_str = "1";
        }
        _label.setText("当前选择：" + _shape_str + "，" + _color_A_str + "，" + _color_B_str + "，" + _width_str);
    });

}

void MainWindow::paintEvent(QPaintEvent *event){
    update();
    Q_UNUSED(event);
    QPainter painter(this);

    if(_shape_str == "直线"){
        painter.setPen(QPen(QColor(_color_A_str), _width_str.toInt(), Qt::SolidLine, Qt::RoundCap));
        painter.drawLine(100, 100, 500, 500);
    }
    else if(_shape_str == "矩形"){
        painter.setPen(QPen(QColor(_color_A_str), _width_str.toInt(), Qt::SolidLine, Qt::RoundCap));
        painter.setBrush(QBrush(QColor(_color_B_str), Qt::SolidPattern));
        painter.drawRect(100, 100, 400, 400);
    }
    else if(_shape_str == "椭圆"){
        painter.setPen(QPen(QColor(_color_A_str), _width_str.toInt(), Qt::SolidLine, Qt::RoundCap));
        painter.setBrush(QBrush(QColor(_color_B_str), Qt::SolidPattern));
        painter.drawEllipse(100, 100, 400, 400);
    }
    else if(_shape_str == "多边形"){
        painter.setPen(QPen(QColor(_color_A_str), _width_str.toInt(), Qt::SolidLine, Qt::RoundCap));
        painter.setBrush(QBrush(QColor(_color_B_str), Qt::SolidPattern));
        QVector<QPoint> points;
        // 五角星
        points.push_back(QPoint(200, 50));
        points.push_back(QPoint(250, 200));
        points.push_back(QPoint(400, 200));
        points.push_back(QPoint(300, 300));
        points.push_back(QPoint(350, 450));
        points.push_back(QPoint(200, 350)); // 底部
        points.push_back(QPoint(50, 450));
        points.push_back(QPoint(100, 300));
        points.push_back(QPoint(0, 200));
        points.push_back(QPoint(150, 200));

        painter.drawPolygon(points);
    }

}

MainWindow::~MainWindow(){}
```

<br>

---

## 定时器

## Leg 14 定时器

> 定时器 `QTimer`

除了通过 `connect` 函数来连接信号和槽，还可以通过定时器来连接信号和槽。
也就是说，当定时器超时时，就会触发信号，然后执行槽函数。

> 随机数 `QRandomGenerator::global()->bounded()`

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QTimer>
#include <QRandomGenerator>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     _centralWidget; // 中央部件
    QLabel      _labeltext;
    QTimer      _timer;         // 定时器
};
```

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Leg 14 定时器");
    this -> setCentralWidget(&_centralWidget);
    this -> resize(400, 300);

    _labeltext.setParent(&_centralWidget);
    _labeltext.setText("Hello World!");

    _timer.start(5);

    int lastDx = 10, lastDy = 10;
    connect(&_timer, &QTimer::timeout, this, [&](){
        int x = _labeltext.x(), y = _labeltext.y();
        int nx = x + lastDx, ny = y + lastDy;

        if(nx >=1 && nx <= 320 && ny >= 1 && ny <= 280 && x != nx && y != ny)
            _labeltext.move(nx, ny);
        else{
            lastDx = QRandomGenerator::global()->bounded(10)-5;
            lastDy = QRandomGenerator::global()->bounded(10)-5;
        }
    });
}

MainWindow::~MainWindow(){}
```

<br>

---

## Leg 15 动画

暂时没有好的想法，但感觉有必要，所以先占个坑。

<br>

---

## 事件

事件 `event`，是指用户与程序交互的过程中，程序接收到的信号。
例如 **鼠标点击**、**光标移动**、**键盘按下** 等，都是事件。
捕捉信号，执行槽函数，就是事件处理。

## Leg 16 鼠标事件

> 鼠标事件 `QMouseEvent`

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QLabel>
#include <QMouseEvent>
#include <QPainter>
#include <QTimer>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QWidget     _centralWidget;

    void paintEvent(QPaintEvent *event);

    bool _l_pressed=0, _r_pressed=0, _m_pressed=0;
    // 鼠标按下
    void mousePressEvent(QMouseEvent *event);
    // 鼠标释放
    void mouseReleaseEvent(QMouseEvent *event);

    // 鼠标移动
    QLabel      _x_y;
    void mouseMoveEvent(QMouseEvent *event);

    // 鼠标滚轮
    bool _wheel_up=0, _wheel_down=0;
    void wheelEvent(QWheelEvent *event);
};
```

```cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("鼠标检测器");
    this -> setCentralWidget(&_centralWidget);
    this -> setFixedSize(800, 600);

    _x_y.setParent(&_centralWidget);
    _x_y.setGeometry(0, 0, 100, 20);
    _x_y.setText("x: 0, y: 0");

    setMouseTracking(true); // 鼠标跟踪
}

MainWindow::~MainWindow(){}

void MainWindow::paintEvent(QPaintEvent *event){
    Q_UNUSED(event);
    QPainter painter(this);
    painter.setPen(Qt::black);
    // 鼠标外形
    painter.drawRect(300, 200, 200, 300);   // 坐标 长宽
    
    // 鼠标左键
    if(_l_pressed) painter.setBrush(Qt::red);
    painter.drawRect(300, 200, 90, 150);
    painter.setBrush(Qt::NoBrush);  // 恢复现场
    
    // 鼠标右键
    if(_r_pressed) painter.setBrush(Qt::red);
    painter.drawRect(410, 200, 90, 150);
    painter.setBrush(Qt::NoBrush);  // 恢复现场
    
    // 鼠标中键
    if(_m_pressed) painter.setBrush(Qt::red);
    painter.drawRect(390, 200, 20, 150);
    painter.setBrush(Qt::NoBrush);  // 恢复现场
    
    // 鼠标前进
    if(_wheel_up) painter.setPen(QPen(Qt::red, 6));
    else painter.setPen(QPen(Qt::black, 6));
    painter.drawLine(400, 100, 400, 175);
    painter.drawLine(400, 95, 375, 125);
    painter.drawLine(400, 95, 425, 125);
    _wheel_up = 0;

    // 鼠标后退
    if(_wheel_down) painter.setPen(QPen(Qt::red, 6));
    else painter.setPen(QPen(Qt::black, 6));
    painter.drawLine(400, 400, 400, 475);
    painter.drawLine(375, 450, 400, 480);
    painter.drawLine(425, 450, 400, 480);
    _wheel_down = 0;
    
} // 真的服了，这个坐标太反人类了

void MainWindow::mousePressEvent(QMouseEvent *event){
    if(event -> button() == Qt::LeftButton)
        _l_pressed = 1; // 鼠标左键
    if(event -> button() == Qt::RightButton)
        _r_pressed = 1; // 鼠标右键
    if(event -> button() == Qt::MiddleButton)
        _m_pressed = 1; // 鼠标中键
    update();           // 重绘
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event){
    if(event -> button() == Qt::LeftButton)
        _l_pressed = 0; // 鼠标左键
    if(event -> button() == Qt::RightButton)
        _r_pressed = 0; // 鼠标右键
    if(event -> button() == Qt::MiddleButton)
        _m_pressed = 0; // 鼠标中键
    update();           // 重绘
}

void MainWindow::mouseMoveEvent(QMouseEvent *event){
    _x_y.setText(QString("x: %1, y: %2").arg(event -> pos().x()).arg(event -> pos().y()));
    update();
}

void MainWindow::wheelEvent(QWheelEvent *event){
    if(event ->angleDelta().y() == 0) _wheel_up = 0, _wheel_down = 0;
    else if(event ->angleDelta().y() > 0) _wheel_up = 1, _wheel_down = 0;
    else if(event ->angleDelta().y() < 0) _wheel_down = 1, _wheel_up = 0;
    update();

    // 233ms 后执行一次
    QTimer::singleShot(233, this, [=](){
        _wheel_up = 0, _wheel_down = 0;
        update();
    });
}
```

<br>

---

## Leg 17 键盘事件

> 键盘事件 `QKeyEvent`

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <fstream>
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    QString _words; // 从文件中读取的所有字
    int cnt=0;      // 记录已经打对的字数

    void paintEvent(QPaintEvent *event);
    void keyPressEvent(QKeyEvent *event);
};
```

```cpp
// MainWindow.cpp
#include "../include/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("缙云山打字通");
    this -> setFixedSize(800, 600);

    std::ifstream ifs("data.txt");
    std::string str;
    while(ifs >> str)
        _words.push_back(QString::fromStdString(str));
}

MainWindow::~MainWindow(){}

void MainWindow::paintEvent(QPaintEvent *event){
    update();
    Q_UNUSED(event);
    QPainter painter(this);
    QFont font;
    // 设置等宽字体
    font.setFamily("Courier New");
    font.setPointSize(30);
    painter.setFont(font);
    painter.setPen(Qt::green);

    int x = 0, y = 100;
    for (int i = 0; i < _words.size(); i++) {
        QString word = _words[i];
        if (i >= cnt) painter.setPen(Qt::black);
        painter.drawText(x, y, word);
        x += 30;
        if (x > 750) {
            x = 0;
            y += 50;
        }
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event -> key() == Qt::Key_Backspace){
        if(cnt > 0) cnt--;
    }
    else if(event -> key() == Qt::Key_Space){
        cnt++;
    }
    else{
        QString str = event -> text();
        if(str == _words[cnt]) cnt++;
    }
    if(cnt == _words.size()){
        QMessageBox::information(this, "恭喜", "你已经完成了打字练习");
    }
}
```


## Mission 3 🐤

```cpp
// MainWindow.h
#pragma once

#include <QMainWindow>
#include <QPainter>
#include <QLabel>
#include <QKeyEvent>
#include <QTimer>
#include <QRandomGenerator>
#include <QMessageBox>

class MainWindow : public QMainWindow{
    Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr); 
    ~MainWindow();
private:
    bool ck();  // 检查是否碰撞
    void keyPressEvent(QKeyEvent *event);

    double g=1;    // 将 g 看作加速度    
    int acc(){
        return std::max(15, (int)(g += 0.2));
    } // 重力加速度，越来越快

    int source = 0; // 记录分数
    double up=-8;
    int bcc(){
        return up += 0.2;
    } // 跳跃加速度，越来越慢

    QLabel  _background,
            _bird,
            za, zb;
    
    QTimer  _G, _jump;  // 重力与跳跃
    QTimer  _za_t;      // 障碍物

    bool flg = false;   // 用于判断是否开始游戏
    int starty=0;       // 记录跳跃前的高度
};
```

```cpp
// MainWindow.cpp
#include "../Headers/MainWindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    this -> setWindowTitle("Misson3 飞鸟");
    this -> setFixedSize(600, 800);
    
    QPixmap pixmap("img/bg.jpg");
    pixmap = pixmap.scaled(this -> size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    
    _background.setParent(this);
    _background.setPixmap(pixmap);
    _background.setGeometry(0, 0, this -> width(), this -> height());

    pixmap.load("img/bird.jpg");
    pixmap = pixmap.scaled(50, 50, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    _bird.setParent(this);
    _bird.setPixmap(pixmap);
    _bird.setGeometry(200, 340, pixmap.width(), pixmap.height());

    pixmap.load("img/za.jpg");
    pixmap = pixmap.scaled(100, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    za.setParent(this);
    za.setPixmap(pixmap);
    za.setGeometry(600, -400, pixmap.width(), pixmap.height());

    pixmap.load("img/za.jpg");
    pixmap = pixmap.scaled(100, 600, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    zb.setParent(this);
    zb.setPixmap(pixmap);
    zb.setGeometry(600, 500, pixmap.width(), pixmap.height());

    // 左上角显示分数
    QLabel *score = new QLabel(this);
    score -> setGeometry(10, 10, 50, 20);
    connect(&_za_t, &QTimer::timeout, [=](){
        score -> setText("分数：" + QString::number(source));
    });

    // 通过定时器实现重力效果
    connect(&_G, &QTimer::timeout, [=](){
        _bird.move(_bird.x(), _bird.y() + acc());
        update();
    });

    // 通过定时器实现跳跃效果
    connect(&_jump, &QTimer::timeout, [=](){
        if(abs(starty - _bird.y()) > 200){  // 跳跃高度
            _jump.stop();

            g=1;    // 每次 start 加速度重置
            _G.start(10);
            return;
        }

        _bird.move(_bird.x(), _bird.y() + bcc());
    });

    connect(&_za_t, &QTimer::timeout, [=](){
        za.move(za.x() - 2, za.y());
        zb.move(zb.x() - 2, zb.y());

        if(za.x() + za.width() < 0){
            int dy = QRandomGenerator::global()->bounded(-200, 200);
            za.move(600, -400 + dy);
            zb.move(600, 500 + dy);
            source++;
        }

        if(ck()){   // 检查碰撞
            _G.stop();
            _jump.stop();
            _za_t.stop();
            flg = false;
            QMessageBox::information(this, "提示", "游戏结束，您的分数为：" + QString::number(source));
            // bird重置
            _bird.move(200, 340);
            // za重置
            za.move(600, -400);
            zb.move(600, 500);
            // 分数重置
            source = 0;
        }
    });
}

MainWindow::~MainWindow(){}

bool MainWindow::ck(){
    if(_bird.x()+_bird.width() >= za.x() && _bird.x() <= za.x() + za.width()){
        if(_bird.y() <= za.y() + za.height() || _bird.y() + _bird.height() >= zb.y()){
            return true;
        }
    }
    return false;
}

void MainWindow::keyPressEvent(QKeyEvent *event){
    if(event -> key() == Qt::Key_Space){
        
        // 开始游戏
        if(!flg){
            flg=1;
            g=1;
            starty = _bird.y(); // 记录跳跃前的高度
            _G.start(10);
            _za_t.start(10);
        }

        // 跳跃
        if(!_jump.isActive()){ // 在非跳跃状态
            _G.stop();          // 重力停止
            
            starty = _bird.y(); // 记录跳跃前的高度
            
            g=1;
            up=-8;
            _jump.start(10);    // 跳跃开始
        }
        else if(_jump.isActive()){ // 在跳跃状态再跳跃
            //_G.stop();          // 实际上本来就是停止的，这里没必要

            _jump.stop();       // 停止上一次的跳跃
            starty = _bird.y(); // 记录跳跃前的高度
            
            // g=1; 连续跳跃 g 叠加
            up=-8;
            _jump.start(10);    // 重新跳跃
        }
    }
}
```

## 文件与数据库操作

## Leg xx 读写文件

## Leg xx 连接 MYSQL 数据库

## Leg xx 增删改查

## 多媒体

## Leg xx 播放音频

## Leg xx 播放视频




## raylib

raylib 是一个简单易用的游戏开发库，它提供了一系列的函数，用于处理窗口、图像、音频、输入、模型等。

## 安装

```sh
sudo apt install libglfw3-dev libgl1-mesa-dev libglu1-mesa-dev
```

## 测试代码

```cpp
#include "raylib.h"


## 编译

```sh
gcc main.c -o main -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
```

## 运行

```sh
./main
```