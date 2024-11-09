#pragma once
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>    // Для использования Socket()
#include <netinet/in.h>    // Для использования sockaddr_in
#include <ctime>           // Для определения даты и времени
#include <fstream>          // Чтобы работать с файлами
#include <nlohmann/json.hpp> // Для использования JSON
#include "file_handler.h"
#include "factory.h"
#include "serv_connection.h"
#include "utils.h"


class Server {
private:
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
};