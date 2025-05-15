## 参考

* [PostgreSQL Docker hub](https://hub.docker.com/_/postgres)

## 启动

```bash
sudo docker run -e POSTGRES_PASSWORD=postgres -d -p 5432:5432 postgres
```

```bash
sudo apt install postgresql-client
psql -h localhost -U postgres -d postgres
```

## 查

* 查看所有数据库 `SELECT datname FROM pg_database;`
* 查看当前数据库 `SELECT current_database();`
* 进入数据库 `\c <dbname>;`

* 查看所有表 `\d;`
* 查看某表的所有数据 `SELECT * FROM <tablename>;`
* 查看某表 i - j 的数据 `SELECT * FROM <tablename> LIMIT j-i+1 OFFSET i-1;`

* 查看某表的行数 `SELECT count(*) FROM <tablename>;`
* 查看某表的列数 `SELECT count(*) FROM information_schema.columns WHERE table_name='<tablename>';`

## 增

* 创建数据库 `CREATE DATABASE <dbname>;`

## 删

* 删除数据库 `DROP DATABASE <dbname>;`

## 改


## C

* 安装 `sudo apt install libpq-dev`

* 测试 [代码](https://www.postgresql.org/docs/current/libpq-example.html)

* 运行 `g++ pq.cpp -I/usr/include/postgresql -lpq`

## C++



* 下载 `wget https://github.com/jtv/libpqxx/archive/refs/tags/7.10.0.tar.gz`

* 解压 `tar zxvf 7.10.0.tar.gz`

* 编译安装 `mkdir build && cd build && cmake .. && make -j8 && sudo make install`

* 编译 `g++ a.cc -lpqxx -lpq`

```cpp
#include <iostream>
#include <pqxx/pqxx>

int main() {
    try {
        // 连接到数据库
        pqxx::connection c(
            "host=localhost port=5432 dbname = qicstabledata user=postgres "
            "password=postgres");
        std::cout << "Connected to " << c.dbname() << '\n';

        // 开始一个事物
        // 一个连接在同一时间只能有一个事物打开
        pqxx::work tx{c};

        // 执行查询并获取结果集
        pqxx::result res = tx.exec("SELECT * FROM events");

        // 查询的结果
        std::unique_ptr<std::vector<std::vector<std::string>>> data =
            std::make_unique<std::vector<std::vector<std::string>>>();

        // 遍历结果集并填充数据
        for (const auto& row : res) {
            std::vector<std::string> row_data;
            for (const auto& col : row) {
                row_data.push_back(col.c_str());
            }
            data->push_back(row_data);
        }

        // 输出结果集
        for (const auto& row : *data) {
            for (const auto& col : row) {
                std::cout << col << " ";
            }
            std::cout << "\n";
        }

        // 提交事物
        tx.commit();
    } catch (std::exception const& e) {
        std::cerr << "ERROR: " << e.what() << '\n';
        return 1;
    }
    return 0;
}
```