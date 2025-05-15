## 参考

* [C++ STL Tutorial](https://cui-jiacai.gitbook.io/c++-stl-tutorial)

<br>

---

## jiao::STL

* [骄骄的 C++ 标准库](https://github.com/daixll/STL)

<br>

---

## 容器：序列

### vector

* 可以自动扩展大小的动态数组。

* 其扩容规则为：

    * 当数组大小不够容纳新的元素时，`new` 一片更大的空间，将旧的元素复制过去；

    * 更大空间的大小不确定，一般为旧空间的 $1.5$ 倍或 $2$ 倍。


**创建**

```cpp
vector<int> v();            // 空数组
vector<int> v(10);          // 10个元素，每个元素都是0
vector<int> v(10, 1);       // 10个元素，每个元素都是1
vector<int> v(v0);          // 拷贝构造函数
vector<int> v({1, 2, 3});   // 初始化列表
```

**空间**

```cpp
v.size();           // 实际存储的元素数量
v.capacity();       // 预先分配的可用元素数量，占用内存
v.resize(10);       // 调整容器大小为 10
v.shrink_to_fit();  // 释放未使用的内存
```

* `resize(n)` 等价于 `resize(n, 0)`：
    
    * 如果已有元素，则不变；

    * 如果没有元素，则赋值为 `0` 或自定义的值；

    * 如果调整了一个更小的值，其实只是将 `end()` 前移了。

        * 越界访问仍然可以访问到元素，`size()` 变了，`capacity()` 没变；

        * `push_back` 会覆盖之前的值；

        * 可以通过 `shrink_to_fit()` 释放空间；

<br>

---

### deque

<br>

---



### array

<br>

---

### list

<br>

---

### forward_list

<br>

---


## 容器：关联

<br>

---

## 容器：无序关联

<br>

---

## 迭代器

<br>

---

## 算法

<br>

---

## 函数对象

<br>

---

## 配接器

<br>

---

## 内存分配器