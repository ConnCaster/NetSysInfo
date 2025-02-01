#pragma once
#include <netinet/in.h>    // Для использования sockaddr_in
#include <fstream>
#include <unistd.h>



class Server {
private:
    std::fstream log;
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
        log.close();
        close(sock_fd_);
    }
};