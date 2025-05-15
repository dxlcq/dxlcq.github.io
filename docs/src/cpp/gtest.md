## setup

### linux

1. 下载 [地址](https://github.com/google/googletest/releases)

2. 解压
    
    ```
    tar -zxvf googletest*
    ```

3. 编译

    ```sh
    cd googletest*
    mkdir build && cd build
    cmake ..
    make
    ```

4. 安装

    ```sh
    sudo make install
    ```

    相当于将其复制到 `/usr/local` 目录下


<br>

---

## use


### easy

项目目录结构

```
├── CMakeLists.txt        # 顶层 CMake 配置文件
├── include               # 公共头文件
│   ├── add.h             # 加法头文件
│   └── sub.h             # 减法头文件
├── src                   # 源代码目录
│   ├── CMakeLists.txt    # src 目录下的 CMake 配置文件
│   ├── main.cpp          # 主函数源代码文件
│   ├── add.cpp           # 加法源代码文件
│   └── sub.cpp           # 减法源代码文件
└── tests                 # 测试代码目录
    ├── CMakeLists.txt    # tests 目录下的 CMake 配置文件
    └── test_as.cpp       # 测试文件
```

`CMakeLists.txt`

```cmake
cmake_minimum_required(VERSION 3.10)
project(GT)
set(CMAKE_CXX_STANDARD 11)

# 添加头文件目录
include_directories(${CMAKE_SOURCE_DIR}/include)

# 添加源代码目录
add_subdirectory(src)

# 添加测试目录
enable_testing()
add_subdirectory(tests)
```

`include/add.h`

```cpp
#pragma once

int add(int a, int b);
```

`include/sub.h`

```cpp
#pragma once

int sub(int a, int b);
```

`src/CMakeLists.txt`

```cmake
# 创建库目标，供其他可执行文件或测试使用
add_library(add add.cpp)
add_library(sub sub.cpp)

# 创建可执行文件目标
add_executable(main main.cpp)
target_link_libraries(main PRIVATE add sub)
```

`src/add.cpp`

```cpp
#include "add.hpp"

int add(int x, int y){
    return x + y;
}
```

`src/sub.cpp`

```cpp
#include "sub.hpp"

int sub(int x, int y){
    return x - y;
}
```

`src/main.cpp`

```cpp
#include "add.hpp"
#include "sub.hpp"
#include <iostream>

int main(){
    std::cout << add(2, 1) << std::endl;
    std::cout << sub(2, 1) << std::endl;
    return 0;
}
```

`tests/CMakeLists.txt`

```cmake
# 查找 GTest
find_package(GTest REQUIRED)

# 添加 GTest 的头文件
include_directories(${GTEST_INCLUDE_DIRS})

# 添加测试可执行文件
add_executable(test_as test.cpp)

# 链接 GTest 库和项目的代码库
target_link_libraries(test_as ${GTEST_LIBRARIES} add sub)

# 添加测试
add_test(NAME main COMMAND test_as)
```

`tests/test_as.cpp`

```cpp
#include <gtest/gtest.h>
#include "add.hpp"
#include "sub.hpp"

TEST(AddTest, PositiveNumbers){
    EXPECT_EQ(add(2, 1), 3);
}

TEST(SubTest, PositiveNumbers){
    EXPECT_EQ(sub(2, 1), 1);
}

int main(int argc, char **argv){
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
```