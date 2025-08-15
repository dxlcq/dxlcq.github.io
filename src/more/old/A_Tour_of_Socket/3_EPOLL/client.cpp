#include "Headers/Sock.h"

int main(int argc, char const *argv[]){
    jiao::Sock client("", 0);
    client.Conn("127.0.0.1", std::atoi(argv[1]));

    while(true){
        std::cout << "请输入: ";
        std::string msg;
        std::cin >> msg;

        client.Send(msg);
    }

    return 0;
}