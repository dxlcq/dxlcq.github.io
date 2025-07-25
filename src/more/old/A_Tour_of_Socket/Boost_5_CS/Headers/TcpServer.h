#pragma once

#include <boost/asio.hpp>
#include <iostream>
#include <cstring>

using namespace boost::asio;

class Connection{   // 连接
public:
    Connection(io_context& io): socket(io){};
    ~Connection(){
        std::cout << socket.native_handle() << " 连接释放!" << std::endl;
    };

    ip::tcp::socket socket;

    void start_read(){
        // 异步读取数据
        socket.async_read_some(buffer(data, sizeof data),
            [this](const boost::system::error_code& ec, std::size_t len){
                if(!ec){
                    data[len] = '\0';
                    std::cout << socket.native_handle() << " 收到消息: " << data << std::endl;
                    start_read();
                }else{
                    std::cout << socket.native_handle() << " 读取错误! " << ec.message() << " " << error::operation_aborted << std::endl;
                    copy.reset();
                    return ;
                }
            });
    }

    void start_write(){
        // 异步发送数据
        char data_copy[1024];
        strcpy(data_copy, data);
        memset(data, '\0', sizeof data);

        socket.async_write_some(buffer(data_copy, strlen(data_copy)),
            [this](const boost::system::error_code& ec, std::size_t len){
                if(!ec && copy.use_count() != 0){
                    start_write();
                }
                else{
                    std::cout << socket.native_handle() << " 发送错误! " << ec.message() << " " << error::operation_aborted << std::endl;
                    return ;
                }
            });
    }

    std::shared_ptr<Connection> copy;
private:
    char data[1024];
};

class TcpServer{    // 服务器
public:
    TcpServer(io_context io, ip::tcp::endpoint ep):
        _io(io), _ac(io, ep){
        start();
        _io.run();
    };
    ~TcpServer(){};
private:
    void start(){
        // 创建一个新的连接
        auto new_conn = std::make_shared<Connection>(_io);
        new_conn -> copy = new_conn;

        // 异步接收连接
        _ac.async_accept(new_conn->socket,
            [this, new_conn](const boost::system::error_code& ec){
                if(!ec){
                    std::cout << "新连接 " << new_conn->socket.remote_endpoint().address() << ":" << new_conn->socket.remote_endpoint().port() << " " << new_conn->socket.native_handle() << std::endl;
                    new_conn->start_read(), new_conn->start_write();  
                    //_cs.push_back(new_conn);
                }
                // 重新开始接收连接
                start();
        });
    }

    //std::vector<std::shared_ptr<Connection>> _cs;   // 所有的连接

    io_context&         _io;
    ip::tcp::acceptor   _ac;
};