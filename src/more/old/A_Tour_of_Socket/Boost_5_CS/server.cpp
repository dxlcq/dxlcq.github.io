#include "Headers/TcpServer.h"

int main(int argc, char* argv[]){
    TcpServer server(boost::asio::io_context(), boost::asio::ip::tcp::endpoint(boost::asio::ip::address::from_string(argv[1]),std::atoi(argv[2])));
    return 0;
}