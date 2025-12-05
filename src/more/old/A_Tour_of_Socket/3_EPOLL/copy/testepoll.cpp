#include <sys/socket.h> //for socket
#include <arpa/inet.h>  //for htonl htons
#include <sys/epoll.h>  //for epoll_ctl
#include <unistd.h>     //for close
#include <fcntl.h>      //for fcntl
#include <errno.h>      //for errno
#include <iostream>     //for cout

class fd_object
{
public:
    fd_object(int fd) { listen_fd = fd; }
    ~fd_object() { close(listen_fd); }
private:
    int listen_fd;
};

/*
./epoll for lt mode
and
./epoll 1 for et mode
*/
int main(int argc, char* argv[])
{
    //create a socket fd
    int listen_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (listen_fd == -1)
    {
        std::cout << "create listen socket fd error." << std::endl;
        return -1;
    }
    fd_object obj(listen_fd);

    //set socket to non-block
    int socket_flag = fcntl(listen_fd, F_GETFL, 0);
    socket_flag |= O_NONBLOCK;
    if (fcntl(listen_fd, F_SETFL, socket_flag) == -1)
    {
        std::cout << "set listen fd to nonblock error." << std::endl;
        return -1;
    }

    //init server bind info
    int port = 51743;
    struct sockaddr_in bind_addr;
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind_addr.sin_port = htons(port);
    if (bind(listen_fd, (struct sockaddr *)&bind_addr, sizeof(bind_addr)) == -1)
    {
        std::cout << "bind listen socket fd error." << std::endl;
        return -1;
    }

    //start listen
    if (listen(listen_fd, SOMAXCONN) == -1)
    {
        std::cout << "listen error." << std::endl;
        return -1;
    }
    else
        std::cout << "start server at port [" << port << "] with [" << (argc <= 1 ? "LT" : "ET") << "] mode." << std::endl;

    //create a epoll fd
    int epoll_fd = epoll_create(88);
    if (epoll_fd == -1)
    {
        std::cout << "create a epoll fd error." << std::endl;
        return -1;
    }

    epoll_event listen_fd_event;
    listen_fd_event.data.fd = listen_fd;
    listen_fd_event.events = EPOLLIN;
    if (argc > 1) listen_fd_event.events |= EPOLLET;

    //add epoll event for listen fd
    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, listen_fd, &listen_fd_event) == -1)
    {
        std::cout << "epoll ctl error." << std::endl;
        return -1;
    }

    while (true)
    {
        epoll_event epoll_events[1024];
        int n = epoll_wait(epoll_fd, epoll_events, 1024, 1000);

        if (n < 0)
            break;
        else if (n == 0) //timeout
            continue;

        for (int i = 0; i < n; ++i)
        {
            if (epoll_events[i].events & EPOLLIN)//trigger read event
            {
                if (epoll_events[i].data.fd == listen_fd)
                {
                    //accept a new connection
                    struct sockaddr_in client_addr;
                    socklen_t client_addr_len = sizeof(client_addr);
                    int client_fd = accept(listen_fd, (struct sockaddr*)&client_addr, &client_addr_len);
                    if (client_fd == -1)
                        continue;

                    socket_flag = fcntl(client_fd, F_GETFL, 0);
                    socket_flag |= O_NONBLOCK;
                    if (fcntl(client_fd, F_SETFL, socket_flag) == -1)
                    {
                        close(client_fd);
                        std::cout << "set client fd to non-block error." << std::endl;
                        continue;
                    }

                    epoll_event client_fd_event;
                    client_fd_event.data.fd = client_fd;
                    client_fd_event.events = EPOLLIN | EPOLLOUT;
                    if (argc > 1) client_fd_event.events |= EPOLLET;

                    if (epoll_ctl(epoll_fd, EPOLL_CTL_ADD, client_fd, &client_fd_event) == -1)
                    {
                        std::cout << "add client fd to epoll fd error." << std::endl;
                        close(client_fd);
                        continue;
                    }

                    std::cout << "accept a new client fd [" << client_fd << "]." << std::endl;
                }
                else
                {
                    std::cout << "EPOLLIN event triggered for client fd [" << epoll_events[i].data.fd << "]." << std::endl;

                    char recvbuf[1024] = { 0 };
                    int m = recv(epoll_events[i].data.fd, recvbuf, 1024, 0); // only read 1 bytes when read event triggered

                    if (m == 0 || (m < 0 && errno != EWOULDBLOCK && errno != EINTR))
                    {
                        if (epoll_ctl(epoll_fd, EPOLL_CTL_DEL, epoll_events[i].data.fd, NULL) != -1)
                            std::cout << "the client fd [" << epoll_events[i].data.fd << "] disconnected." <<  std::endl;
                        close(epoll_events[i].data.fd);
                    }

                    std::cout << "recv data from client fd [" << epoll_events[i].data.fd << "] and data is [" << recvbuf << "]." << std::endl;
                }
            }
            else if (epoll_events[i].events & EPOLLOUT)
            {
                if (epoll_events[i].data.fd == listen_fd) //trigger write event
                    continue;

                std::cout << "EPOLLOUT event triggered for client fd [" << epoll_events[i].data.fd << "]." << std::endl;
            }
        }
    }

    return 0;
}