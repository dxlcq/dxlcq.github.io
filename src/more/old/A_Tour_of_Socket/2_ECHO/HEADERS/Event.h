#pragma once

#include <functional>
#include <sys/socket.h>
#include <unistd.h>
#include <fcntl.h>
#include <set>

#include "Tool.h"
#include "SockAddr.h"
#include "Accepter.h"

namespace jiao{

class Event
{

public:
    Event(const std::string& ip="0.0.0.0", const int& port=10086);
    ~Event();
    void loop(std::function<std::string(std::string)> deal);

private:
    std::set<int> cs;
    Accepter* acer;

    std::string recvMsg(const int& client);
    int sendMsg(const int& client, const std::string& msg);
    char buf[1024];

    int sock;
    SockAddr* addr;
};

}