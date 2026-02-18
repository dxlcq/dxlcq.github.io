#include "../HEADERS/Accepter.h"

using namespace jiao;

Accepter::Accepter(const int& sock){
    client_addr     = new SockAddr("", 0);
    Accepter::sock = sock;
}

Accepter::~Accepter(){
    delete client_addr;
}

int Accepter::ac(){
    return accept(sock, (sockaddr*)client_addr->get_addr(), client_addr->get_addr_len());
}