## 参考

[官网](https://www.boost.org/) | [下载](https://www.boost.org/users/download/) | [开发文档](https://www.boost.org/doc/)

<br>

---

## setup

### linux

* 通过 apt

    ```shell
    sudo apt-get install libboost-all-dev
    ```

1. 下载 `wget` / 解压 `tar -zxvf` / 提权 `chmod +x`

2. 配置安装选项 `./bootstrap.sh --prefix=/.../boost-x.y.z`

3. 安装 `./b2 -j$(nproc) --prefix=/.../boost-x.y.z install`

4. 编写测试代码

    ```cpp
    #include <boost/version.hpp>
    #include <boost/config.hpp>
    #include <iostream>
    using namespace std;

    int main(){
        cout << BOOST_VERSION << endl;      // Boost 版本号
        cout << BOOST_LIB_VERSION << endl;  // Boost 版本号
        cout << BOOST_PLATFORM << endl;     // 操作系统
        cout << BOOST_COMPILER << endl;     // 编译器
        cout << BOOST_STDLIB << endl;       // 标准库
        return 0;
    }
    ```
5. 编译
    ```shell
    g++ test.cpp -I/.../boost-x.y.z/include -L/.../boost-x.y.z/lib
    ```

### windows

1. 下载
    [Boost](https://www.boost.org/users/download/)

2. 解压

3. 进入解压后的目录，执行 `.\bootstrap.bat gcc`
    * 编译前的配置工作

4. 执行 `.\b2.exe install`
    * 编译安装

5. 测试
    ```cpp
    #include <boost/version.hpp>//包含 Boost 头文件
    #include <boost/config.hpp> //包含 Boost 头文件
    #include <iostream>

    using namespace std;
    int main(){
        cout << BOOST_VERSION << endl;      // Boost 版本号
        cout << BOOST_LIB_VERSION << endl;  // Boost 版本号
        cout << BOOST_PLATFORM << endl;     // 操作系统
        cout << BOOST_COMPILER << endl;     // 编译器
        cout << BOOST_STDLIB << endl;       // 标准库
        return 0;
    }
    ```
    * 编译
        ```shell
        g++ -o test test.cpp -I"C:\Boost\include\boost-1_84" -L"C:\Boost\lib"
        ```
    * 如果使用网络库，还需要 `-lws2_32`

<br>

---

## dev

### Boost.PropertyTree

属性树，数据结构为🌲，键值对形式存在，可以嵌套，适用于配置文件，如 JSON、XML 等

```cpp
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/xml_parser.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <iostream>

namespace pt = boost::property_tree;

/*
    将数据塞到数据结构 boost::property_tree::ptree 中
    输出到文件 json / xml
*/

int main()
{
    try
    {
        pt::ptree tree_1;   // 根节点
        pt::ptree tree_2_1; // 第 1 个子节点
        pt::ptree tree_2_2; // 第 2 个子节点

        // 根节点添加属性
        tree_1.add("tree1", "1");
        tree_1.add("tree2", "2");

        // 第 1 个子节点添加属性
        tree_2_1.add("tree2_1", "2_1");
        tree_2_1.add("tree2_2", "2_x");
        tree_2_1.put("tree2_2", "2_2"); // put 有则改之，无则加冕

        // 第 2 个子节点添加属性
        tree_2_2.add("tree3_1", "3_1");
        tree_2_2.add("tree3_2", "3_2");

        // 根节点添加子节点
        tree_1.add_child("2_1", tree_2_1); // 添加第 1 个节点
        tree_1.add_child("2_2", tree_2_2); // 添加第 2 个节点

        // 保存至 json
        pt::write_json("output.json", tree_1);
        // 保存至 xml
        pt::write_xml("output.xml", tree_1);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}
```