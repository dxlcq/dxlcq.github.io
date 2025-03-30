##  参考

* [我常用的六种设计模式-C++程序员昊天](https://mp.weixin.qq.com/s/yWCVZX_82V3GfaZkFHTTdA)

<br>

---

## 设计原则

1. `SRP` 单一职责
    一个类只负责一个功能，职责单一。
2. `OCP` 开闭
    对扩展开放，对修改关闭（封装应当遵守的原则）。
3. `LSP` 里式替换
    子类可以扩展父类的功能，但不能修改父类原有的功能（继承应当遵守的原则）。
4. `*DIP` 依赖倒置
    高层模块不依赖低层模块，它们共同依赖同一个抽象。抽象不要依赖具体实现细节，具体实现细节依赖抽象。
5. `ISP` 接口隔离
    客户端不应该依赖那些它不需要的接口（封装应当遵守的原则）。

6. `CRP` 合成复用
7. `LoD` 迪米特


<br>

---

## 单例模式

一个类只有一个实例，并提供一个全局访问点。适用于日志、公共数据等全局性质的对象。

* Meyers’ Singleton

    ```cpp
    class Singleton {
       public:
        static Singleton& getInstance() {
            static Singleton inst;
            return inst;
        };

        Singleton(const Singleton&) = delete;             // 禁止拷贝构造函数
        Singleton& operator=(const Singleton&) = delete;  // 禁止拷贝赋值运算符
        Singleton(Singleton&&) = delete;                  // 禁止移动构造函数
        Singleton& operator=(Singleton&&) = delete;       // 禁止移动赋值运算符

       private:
        Singleton() = default;
    };
    ```

* 饿汉式：类加载时初始化实例
* 懒汉式：第一次使用时初始化实例
* 懒汉式-线程安全：每次使用时通过锁机制保证线程安全
* 懒汉式-DCL：检查指针，指针为空再加锁，双重检查锁定



<br>

---

## 观察者模式

```
┌─────────┐               ┌───────────┐
│         │ -- attach --> │           │
│         │               │ Observer1 │
│         │ -- notify --> │           │
│ Subject │               └───────────┘
│         │
│         │               ┌───────────┐
│         │ ------------- │ Observer2 │
└─────────┘               └───────────┘
```

* `Subject` 被观察者，维护一组 `Observer` 对象，提供添加、删除、通知方法
* `Observer` 观察者，定义一个 `update` 接口，当收到通知时调用 `update` 更新状态


<br>

---

## 发布订阅模式

```
┌────────────┐                ┌─────────┐                  ┌─────────────┐
│ Publisher1 │ -- publish --> │         │ <-- subscribe -- │ Subscriber1 │
└────────────┘                │  Event  │                  └─────────────┘
┌────────────┐                │ Channel │                  ┌─────────────┐
│ Publisher2 │ -- publish --> │         │ <-- subscribe -- │ Subscriber2 │
└────────────┘                └─────────┘                  └─────────────┘
```

* `Publisher` 发布者，向 `Event Channel` 发布消息

* `Subscriber` 订阅者，向 `Event Channel` 订阅消息


<br>

---


## 设计模式

* [UML类图和时序图]()
* [创建型模式 ( 总结 )]
    1. [简单工厂模式 ( Simple Factory Pattern )]
    2. [工厂方法模式 ( Factory Method Pattern )]
    3. [抽象工厂模式 ( Abstract Factory Pattern )]
    4. [建造者模式()]
    5. [单例模式()]
* 结构型模式
    1. [适配器模式]
    2. [桥接模式]
    3. [装饰模式]
    4. [外观模式]
    5. [享元模式]
    6. [代理模式]
* 行为型模式
    1. [命令模式]
    2. [中介者模式]
    3. [观察者模式]
    4. [状态模式]
    5. [策略模式]


简单工厂：唯一工厂类，一个产品抽象类，工厂类的创建方法依据入参判断并创建具体产品对象。


工厂方法：多个工厂类，一个产品抽象类，利用多态创建不同的产品对象，避免了大量的if-else判断。


抽象工厂：多个工厂类，多个产品抽象类，产品子类分组，同一个工厂实现类创建同组中的不同产品，减少了工厂子类的数量




## 含义

* 简单工厂模式(Simple Factory Pattern): 又称为静态工厂方法(Static Factory Method)模式, 它属于类创建型模式
* 在简单工厂模式中, 可以根据参数的不同返回不同类的实例
* 简单工厂模式专门定义一个类来负责创建其他类的实例, 被创建的实例通常都具有共同的父类

## 解决的问题

将“类实例化的操作”与“使用对象的操作”分开, 让使用者不用知道创建逻辑就可以实例化出所需要的“产品”类, 从而避免了在客户端代码中显式指定, 实现了解耦

## UML类图及时序图

![](https://raw.githubusercontent.com/kiddxl/dxlkid/main/daixll/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/11.png)

## 代码实例

抽象产品
```cpp
class 产品
{
public:
    // 提供接口框架的纯虚函数
    virtual std::string 产品名字() = 0;
    产品() {};
    ~产品() {};
};
```

具体产品
```cpp
// 三个实际产品
class 电脑 : public 产品 {
public:
    电脑() {};
    ~电脑() {};
    std::string 产品名字() {
        return "电脑";
    };
};

class 手机 : public 产品 {
public:
    手机() {};
    ~手机() {};
    std::string 产品名字() {
        return "手机";
    };
};

class 平板 : public 产品 {
public:
    平板() {};
    ~平板() {};
    std::string 产品名字() {
        return "平板";
    };
};
```

具体工厂
```cpp
class 工厂
{
public:
    工厂() {};
    ~工厂() {};
    产品* 制造产品(std::string 产品名) {
        if (产品名 == "电脑")
            return new 电脑;
        if (产品名 == "手机")
            return new 手机;
        if (产品名 == "平板")
            return new 平板;
        return NULL;
    };
};
```

```cpp
int main() {
    工厂* 龙龙的血汗工厂 = new 工厂();
    产品* 佳佳的电脑 = 龙龙的血汗工厂->制造产品("电脑");

    std::cout << 佳佳的电脑->产品名字();

    return 0;
}
```

## 优点

* 工厂类含有必要的判断逻辑, 可以决定在什么时候创建哪一个产品类的实例, 客户端可以免除直接创建产品对象的责任, 而仅仅“消费”产品; 简单工厂模式通过这种做法实现了对责任的分割, 它提供了专门的工厂类用于创建对象

* 客户端无须知道所创建的具体产品类的`类名`, 只需要知道具体产品类所对应的参数即可, 对于一些复杂的类名, 通过简单工厂模式可以减少使用者的记忆量

* 通过引入配置文件, 可以在不修改任何客户端代码的情况下更换和增加新的具体产品类, 在一定程度上提高了系统的灵活性

## 缺点

* 由于工厂类集中了所有产品创建逻辑，一旦不能正常工作，整个系统都要受到影响

* 使用简单工厂模式将会增加系统中类的个数, 在一定程序上增加了系统的复杂度和理解难度

* 系统扩展困难, 一旦添加新产品就不得不修改工厂逻辑, 在产品类型较多时, 有可能造成工厂逻辑过于复杂, 不利于系统的扩展和维护

* 简单工厂模式由于使用了静态工厂方法, 造成工厂角色无法形成基于继承的等级结构

## 典型应用





## 含义

* 工厂方法模式(Factory Method Pattern)又称为工厂模式, 也叫虚拟构造器(Virtual Constructor)模式或者多态工厂(Polymorphic Factory)模式, 它属于类创建型模式

* 在工厂方法模式中, 工厂父类负责定义创建产品对象的公共接口, 而工厂子类则负责生成具体的产品对象

* 目的是将产品类的实例化操作`延迟`到工厂子类中完成, 即通过工厂子类来确定究竟应该实例化哪一个具体产品类

## 解决的问题

这种抽象化的结果使这种结构可以在不修改具体工厂类的情况下引进新的产品; 当有新产品加入时, 新建具体工厂继承抽象工厂, 而不用修改任何一个类 `有效避免简单工厂在工厂类中又臭又长的if...else`

## UML类图及时序图

![](https://raw.githubusercontent.com/kiddxl/dxlkid/main/daixll/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/12.png)

## 代码实例

抽象产品
```cpp
class 产品 {
public:
    virtual std::string 产品名字() = 0;
    产品() {};
    ~产品() {};
};
```

具体产品
```cpp
class 手机 : public 产品 {
public:
    std::string 产品名字() {
        return "手机";
    }
    手机() {};
    ~手机() {};
};
```

抽象工厂
```cpp
class 工厂 {
public:
    virtual 产品* 制造产品() = 0;
    工厂() {};
    ~工厂() {};
};
```

具体工厂
```cpp
class 手机厂 :public 工厂 {
public:
    手机* 制造产品() {
        return new 手机();
    }
    手机厂() {};
    ~手机厂() {};
};
```

```cpp
int main() {
    工厂* 龙龙的手机工厂 = new 手机厂();
    产品* 佳佳的小手机 = 龙龙的手机工厂->制造产品();

    std::cout << 佳佳的小手机->产品名字();

    delete 龙龙的手机工厂;
    delete 佳佳的小手机;
    return 0;
}
```

## 优点

* 只需要关心工厂, 无需关心创建细节

## 缺点

* 增加了类的数量, 增加了系统复杂度

* 引入了抽象层, 增加了系统的抽象性和理解难度

## 典型应用

日志记录器

支持文件记录、数据库记录等不同记录方式




## 含义

提供一个创建一系列相关或相互依赖对象的接口, 而无须指定它们具体的类

## 解决的问题

当需要一个工厂提供多种产品, 而不是单一的产品对象(相较于工厂方法模式)

> * 产品等级结构: 如 `电视` 和 `电视的子类`(小米电视, 三星电视, 索尼电视) 
> * 产品族: 同一个工厂生成的 `小米电视`, `小米手机`, `小米电脑`

![](https://raw.githubusercontent.com/kiddxl/dxlkid/main/daixll/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/13_1.png)

## UML类图及时序图

![](https://raw.githubusercontent.com/kiddxl/dxlkid/main/daixll/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/13.png)

## 代码实例

产品等级结构 `电视` 和 `各个品牌的电视`
```cpp
// 抽象类
class 电视 {
public:
    virtual std::string 尺寸() = 0;
    电视() {};
    ~电视() {};
};

// 具体类
class oppo电视 : public 电视 {
public:
    std::string 尺寸() {
        return "88寸";
    }
    oppo电视() {};
    ~oppo电视() {};
};

class 三星电视 : public 电视 {
public:
    std::string 尺寸() {
        return "32寸";
    }
    三星电视() {};
    ~三星电视() {};
};
```

产品等级结构 `手机` 和 `各个品牌的手机`
```cpp
// 抽象类
class 手机 {
public:
    virtual std::string 芯片() = 0;
    手机() {};
    ~手机() {};
};

// 具体类
class oppo手机 : public 手机 {
public:
    std::string 芯片() {
        return "马里亚纳海沟";
    }
    oppo手机() {};
    ~oppo手机() {};
};
class 三星手机 : public 手机 {
public:
    std::string 芯片(){
        return "猎户座";
    }
    三星手机() {};
    ~三星手机() {};
};
```

产品族 同一个工厂生产的
```cpp
// 抽象类
class 品牌 {
public:
    virtual 电视* 制造电视() = 0;
    virtual 手机* 制造手机() = 0;
    品牌() {};
    ~品牌() {};
};

// 具体类
class oppo : public 品牌 {
public:
    电视* 制造电视() {
        return new oppo电视();
    }
    手机* 制造手机() {
        return new oppo手机();
    }
    oppo() {};
    ~oppo() {};
};
class 三星 : public 品牌 {
public:
    电视* 制造电视() {
        return new 三星电视();
    }
    手机* 制造手机() {
        return new 三星手机();
    }
    三星() {};
    ~三星() {};
};
```

```cpp
int main() {
    三星* 三星重庆分厂 = new 三星();
    oppo* oppo重庆分厂 = new oppo();

    手机* 小精灵的小手机 = oppo重庆分厂->制造手机();
    电视* 佳佳的大电视 = 三星重庆分厂->制造电视();

    std::cout << 小精灵的小手机->芯片() << "\n";
    std::cout << 佳佳的大电视->尺寸();
    return 0;
}
```

## 优点

当一个产品族中的多个对象被设计成一起工作时, 它能保证客户端始终只使用同一个产品族中的对象

## 缺点

产品族扩展非常困难, 要增加一个系列的某一产品, 既要在抽象类里加代码, 又要在具体的类里加代码

## 典型应用






## 含义

* 适配器模式(Adapter Pattern): 将一个接口转换成客户希望的另一个接口, 适配器模式使接口不兼容的那些类可以一起工作, 其别名为包装器(Wrapper)
* 适配器模式既可以作为类结构型模式, 也可以作为对象结构型模式

## 解决的问题

* 系统需要使用现有的类, 而这些类的接口不符合系统的需要
* 想要建立一个可以重复使用的类, 用于与一些 ( 彼此之间没有太大关联的一些类,可能在将来引进的类 ) 一起工作

## UML类图及时序图

![](https://raw.githubusercontent.com/kiddxl/dxlkid/main/daixll/%E8%AE%BE%E8%AE%A1%E6%A8%A1%E5%BC%8F/21.png)

## 代码实例

```cpp
#include <iostream>
#include <string>

class 不兼容类 {
public:
    不兼容类() {};
    ~不兼容类() {};
    std::string 功能() {
        return "一个接口不兼容的功能";
    }
};

class 适配器 {
private:
    不兼容类* 旧;
public:
    适配器() {};
    ~适配器() {};

    std::string 统一接口(不兼容类* 旧) {
        return 旧->功能();
    };
};

int main() {
    不兼容类* 旧 = new 不兼容类();
    适配器* 目标 = new 适配器();

    std::cout << 目标->统一接口(旧);
    
    return 0;
}
```

## 优点


## 缺点


## 典型应用



