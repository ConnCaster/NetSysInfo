#pragma once
#include <unistd.h>
#include <netinet/in.h>
#include <nlohmann/json.hpp>


class Client {
private:
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