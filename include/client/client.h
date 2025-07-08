#pragma once
#include <unistd.h>
#include <netinet/in.h>

#include "logger.h"

class Client {
private:
    Log client_log_;
    int sock_fd_{0};
    uint16_t port_;
    struct sockaddr_in addr_{}; // sockaddr_in - это тип данных, который используется для хранения адреса сокета
public:
    explicit Client(uint16_t port);

    void Run() ;

    int SetSockFd();

    ~Client() {
        close(sock_fd_);
    }
};