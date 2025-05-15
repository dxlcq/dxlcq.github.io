## 参考

* [cmake 官方文档](https://cmake.org/cmake/help/latest/manual/cmake.1.html)

* [cmake 最佳实践](https://modern-cmake-cn.github.io/Modern-CMake-zh_CN/)

<br>

---

## 安装

* `sudo apt install cmake`

* [从源码安装](https://github.com/Kitware/CMake?tab=readme-ov-file#building-cmake-from-scratch)

<br>

## 基础用法

```bash
cmake -B build
cmake --build build -j$(nproc)
```

* 在顶层 `CMakeLists.txt` 目录中执行

* `cmake -B build`
    
    * 生成构建系统文件（例如 `Makefile`），避免中间文件污染源代码目录（out-of-source）

    * `-B` 指定输出目录为 `build`

* `cmake --build build -j$(nproc)`

    * 使用指定构建系统进行编译（例如 `make`）

    * `-j$(nproc)` 并行编译，`$(nproc)` 表示使用所有 CPU 核心数

<br>

---

## 快速上手

如同使用 `g++` 编译项目一样，需要：

* 指定需要编译的源文件

* 指定第三方库的头文件路径 `target_include_directories`

* 指定第三方库的库文件路径 `target_link_directories`

* 接接库 `target_link_libraries`

其中最混乱的就是第三方库的管理，网上的教程五花八门，这里通过三种情况来分析：

### 存在 `.cmake`

如果第三方库存在 `.cmake` 文件，不要犹豫，直接使用 `find_package`

```CMakeLists.txt
# 设置 Qt 的 CMake 模块路径，如果不在 /usr/lib /usr/local/lib 等常见路径下
set(Qt6_DIR ".../Qt/x.y.z/gcc_64/lib/cmake/Qt6")

# 导入 Qt6 模块
# REQUIRED 必须找到
# COMPONENTS 需要的组件
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Xml
)

# 链接库
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Xml
)
```

### 存在 `.pc`

如果第三方库存在 `.pc` 文件，不要犹豫，优先使用 `pkg_check_modules`

```CMakeLists.txt
# 导入 pkg-config 模块
find_package(PkgConfig REQUIRED)

# pkg_check_modules 查找的路径
set(ENV{PKG_CONFIG_PATH} ".../lib/pkgconfig")
pkg_check_modules(PQ REQUIRED IMPORTED_TARGET
    libpq
)

# 链接库目录
target_link_libraries(${PROJECT_NAME} PRIVATE
    PkgConfig::PQ
)
```

### 手动

只给你 `lib` 和 `include` 目录，直接复制到你项目目录下

```CMakeLists.txt
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/libs/xxx/include
)

find_library(LIBQICSTABLE libqicstable.so.3 PATHS /home/jiao/Desktop/qicstable-master/lib)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LIBQICSTABLE}
)
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