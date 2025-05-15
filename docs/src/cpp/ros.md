# 一种跨平台模块化软件通讯机制

## 参考

* [ROS的最简单安装——鱼香一键安装](https://blog.csdn.net/m0_73745340/article/details/135281023)

<br>

---


## roscore

启动 ROS Master、Parameter Server 和 rosout

<br>

---



## hello ros

1. 初始化工作空间

    ```sh
    mkdir -p ~/hello_ros/src
    cd ~/hello_ros
    catkin_make
    source devel/setup.bash
    ```
    
    * `src` 是必须的

2. 创建 ros 包

    ```sh
    cd ~/hello_ros/src
    catkin_create_pkg hello std_msgs roscpp
    cd ..
    catkin_make
    source devel/setup.bash
    cd ~/hello_ros/src/hello
    ```

    * 创建一个 `hello` 的 ros 包，并指定依赖

3. 发布者

    ```sh
    vim publisher_node.cpp
    ```

    ```cpp
    #include "ros/ros.h"
    #include "std_msgs/String.h"

    int main(int argc, char **argv) {
        ros::init(argc, argv, "simple_publisher");
        ros::NodeHandle nh;

        // 创建发布者对象
        ros::Publisher pub = nh.advertise<std_msgs::String>("chatter", 1000);

        ros::Rate loop_rate(10);  // 10 Hz
        int count = 0;

        while (ros::ok()) {
            std_msgs::String msg;
            msg.data = "Hello, ROS! " + std::to_string(count);

            ROS_INFO("%s", msg.data.c_str());

            // 发布消息
            pub.publish(msg);

            ros::spinOnce();
            loop_rate.sleep();
            ++count;
        }

        return 0;
    }
    ```

4. 订阅者

    ```sh
    vim subscriber_node.cpp
    ```

    ```cpp
    #include "ros/ros.h"
    #include "std_msgs/String.h"

    // 回调函数，处理接收到的消息
    void chatterCallback(const std_msgs::String::ConstPtr& msg) {
        ROS_INFO("I heard: [%s]", msg->data.c_str());
    }

    int main(int argc, char **argv) {
        ros::init(argc, argv, "simple_subscriber");
        ros::NodeHandle nh;

        // 创建订阅者对象
        ros::Subscriber sub = nh.subscribe("chatter", 1000, chatterCallback);

        // 进入循环，等待回调
        ros::spin();

        return 0;
    }
    ```

5. 编译

    ```sh
    vim CMakeLists.txt
    ```

    ```txt
    add_executable(publisher_node publisher_node.cpp)
    target_link_libraries(publisher_node ${catkin_LIBRARIES})

    add_executable(subscriber_node subscriber_node.cpp)
    target_link_libraries(subscriber_node ${catkin_LIBRARIES})
    ```

    ```sh
    cd ~/hello_ros
    catkin_make
    source devel/setup.bash
    ```

6. 运行

    ```sh
    roscore
    rosrun hello publisher_node
    rosrun hello subscriber_node
    ```