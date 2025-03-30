## 参考

<br>

---

## 基础用法

当前目录下存在 `CMakeLists.txt` 文件

```CMakeLists.txt
cmake_minimum_required(VERSION 3.28)

project(
    "MyProject"
    VERSION 1.0.0.250319
)

# 生成可执行文件
add_executable(MyExecutable
    src/main.cpp
)

# 为目标添加头文件和源文件
target_sources(MyLibrary
    PUBLIC include/api.h
    PRIVATE src/internals.cpp src/foo.cpp)




target_sources(MyExecutable PRIVATE src/main.cpp)

target_include_directories(MyExecutable PUBLIC include)
```


1. `mkdir build && cd build` 通常做法，避免中间文件污染源代码目录（out-of-source）

2. `cmake ..` 生成构建系统文件（例如 `Makefile`）

3. `cmake --build . -j8` 执行相应的构建命令（例如 `make`）

<br>

---

## 包含头文件

```CMakeLists.txt
include_directories
```


<br>

---

### 查找依赖库

查找库文件

```c
set(Boost_DIR /usr/local/boost)         # 设置 Boost 库的路径，非必须
find_package(Boost REQUIRED)            # 查找 Boost 库
find_package(Boost 1.75 REQUIRED)       # 查找 Boost 库的指定版本
find_package(Boost COMPONENTS system filesystem REQUIRED)  # 查找 Boost 库的 system 和 filesystem 组件
```

常见的变量：

`PackageName_FOUND`：是否找到了指定的包
`PackageName_INCLUDE_DIRS`：包含目录
`PackageName_LIBRARIES`：库文件
`PackageName_VERSION`：版本号

### include_directories

添加头文件目录

```c
include_directories(/usr/local/include)     # 添加头文件目录
include_directories(${Boost_INCLUDE_DIRS})  # 添加 Boost 头文件目录
```

### add_executable

生成可执行文件

```c
add_executable(main main.cpp)               # 生成可执行文件
```

### target_link_libraries

链接库文件

```c
LINK_DIRECTORIES(dir1 dir2)                 # 添加动态库目录，不推荐使用
target_link_libraries(main libssl.so)       # 链接库到 main
target_link_libraries(a ${Boost_LIBRARIES}) # 链接 Boost 库到 a
```

private 的库不会传递给依赖项，public 的库会传递给依赖项


### add_library

生成库文件

```c
add_library(util STATIC util.cpp)       # 生成静态库 libutil.a
add_library(util SHARED util.cpp)       # 生成动态库 libutil.so
```

### if_else

选择判断

```c
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(LIB_PATH "/usr/local/xyz/lib")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIB_PATH "C:/Path/To/Your/Libraries")
endif()

LINK_DIRECTORIES(${LIB_PATH})
```