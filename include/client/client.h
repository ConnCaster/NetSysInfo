#pragma once
#include <iostream>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <nlohmann/json.hpp>
#include "utils.h"
#include "cli_connection.h"


class Client {
private:
    int sock_fd_{0};
    uint16_t port_;
    struct sockaddr_in addr_{}; // sockaddr_in - это тип данных, который используется для хранения адреса сокета
public:
    explicit Client(uint16_t port);

    void Run() const;

    ~Client() {
        close(sock_fd_);
    }
};