#pragma once
#include <netinet/in.h>    // Для использования sockaddr_in
#include <unistd.h>

#include "logger.h"


class Server {
private:
    Log server_log_;
    uint16_t port_;
    struct sockaddr_in addr_{};
    int sock_fd_;
    int client_socket_{0};
public:
    explicit Server(uint16_t port);

    void Run();

    int Get_client_socket_() {
        return client_socket_;
    }

    ~Server() {
        close(sock_fd_);
    }
};