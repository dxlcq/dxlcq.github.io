#include "Headers/Sock.h"

int main(int argc, char const *argv[]){
    jiao::Sock Server("", 0);
    Server.Conn("127.0.0.1", std::atoi(argv[1]));

    while(true){
        std::string msg;
        std::cin >> msg;
        Server.Send(msg);
        std::cout << Server.Recv() << std::endl;
    }

    return 0;
}