## 参考

* [cmake 官方文档](https://cmake.org/cmake/help/latest/manual/cmake.1.html)

* [cmake 最佳实践](https://modern-cmake-cn.github.io/Modern-CMake-zh_CN/)

<br>

---

## 安装

* `sudo apt install cmake`

* [从源码安装](https://github.com/Kitware/CMake?tab=readme-ov-file#building-cmake-from-scratch)

<br>

---

## 基础用法

```bash
cmake -B build
cmake --build build -j
```

* 在顶层 `CMakeLists.txt` 目录中执行

* `cmake -B build`
    
    * 生成构建系统文件（例如 `Makefile`），避免中间文件污染源代码目录（out-of-source）

    * `-B` 指定输出目录为 `build`

* `cmake --build build/ -j`

    * 使用指定构建系统进行编译（例如 `make`）

    * `--build` 指定构建目录为 `build/`

    * `-j` 多线程编译

<br>

---

## 调包侠

如同使用 `g++` 编译项目一样，需要：

* 指定需要编译的源文件

* 头文件目录 `target_include_directories`

* 链接库 `target_link_libraries`，相当于 `-l`，具体的库

时代的巨轮滚滚向前，网上的教程可以说是五花八门，这里通过四种情况分析

### 存在 `.cmake`

如果第三方库存在 `.cmake` 文件，不要犹豫，直接使用 `find_package`

```CMake
# 设置 Qt 的 CMake 模块目录，如果不在 /usr/lib /usr/local/lib 等常见目录下
set(Qt6_DIR ".../Qt/x.y.z/gcc_64/lib/cmake/Qt6")

# 导入 Qt6 模块
# REQUIRED 必须找到
# COMPONENTS 需要的组件
find_package(Qt6 REQUIRED COMPONENTS
    Core
    Xml
)

# 链接
target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Core
    Qt6::Xml
)
```

### 存在 `.pc`

如果第三方库存在 `.pc` 文件，不要犹豫，优先使用 `pkg_check_modules`

```CMake
# 导入 pkg-config 模块
find_package(PkgConfig REQUIRED)

# pkg_check_modules 在什么目录查找
set(ENV{PKG_CONFIG_PATH} ".../lib/pkgconfig")
pkg_check_modules(PQ REQUIRED IMPORTED_TARGET
    libpq
)

# 链接
target_link_libraries(${PROJECT_NAME} PRIVATE
    PkgConfig::PQ
)
```

### 手动

只给 `include` 和 `lib` 目录

```CMake
# 头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/libs/xxx/include
)

# 查找指定库
find_library(LIBQICSTABLE libqicstable.so.3 
    PATHS /home/jiao/Desktop/qicstable-master/lib
)

# 链接
target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LIBQICSTABLE}
)
```

### 源码

项目和源码一起编

```CMake
# 第三方库目录
add_subdirectory(subprocess)

# 生成可执行文件
add_executable(${PROJECT_NAME} 
    ${SOURCES}
)

# 头文件目录
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_SOURCE_DIR}/subprocess/src/cpp
)

# 链接
target_link_libraries(${PROJECT_NAME} PRIVATE
    subprocess
)
```

<br>

---

## 常用

### add_library

```CMake
add_library(util STATIC util.cpp)       # 生成静态库 libutil.a
add_library(util SHARED util.cpp)       # 生成动态库 libutil.so
```

### ifelse

```CMake
if (CMAKE_SYSTEM_NAME STREQUAL "Linux")
    set(LIB_PATH "/usr/local/xyz/lib")
elseif (CMAKE_SYSTEM_NAME STREQUAL "Windows")
    set(LIB_PATH "C:/Path/To/Your/Libraries")
endif()

find_library(LIB_UTIL util 
    PATHS ${LIB_PATH}
)

target_link_libraries(${PROJECT_NAME} PRIVATE
    ${LIB_UTIL}
)
```