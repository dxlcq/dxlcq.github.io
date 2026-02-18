#include <boost/asio.hpp>
#include <iostream>

using namespace boost::asio;

int main(int argc, char* argv[]){
    // 1. 创建 io_context 上下文
    io_context io;
    // 创建端点
    ip::tcp::endpoint ep(ip::address::from_string(argv[1]), std::atoi(argv[2]));
    // 2. 创建接受器, 并且与 io 关联
    ip::tcp::acceptor acceptor(io, ep);
    
    while(true){
        // 3. 创建客户端连接用的 socket
        ip::tcp::socket socket(io);
        // 4. 等待客户端连接
        acceptor.accept(socket);

        while(true){
            char buf[512];
            memset(buf, '\0', sizeof buf);

            // 5. 接收数据
            socket.read_some(buffer(buf));
            std::cout << buf << std::endl;
            // 6. 发送数据
            std::cin.getline(buf, 512);
            socket.write_some(buffer(buf));
        }
    }

    return 0;
}