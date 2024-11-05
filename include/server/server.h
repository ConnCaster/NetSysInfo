#pragma once
#include <iostream>
#include <arpa/inet.h>
#include <sys/socket.h>    // Для использования Socket()
#include <netinet/in.h>    // Для использования sockaddr_in
#include <ctime>           // Для определения даты и времени
#include <fstream>          // Чтобы работать с файлами
#include <nlohmann/json.hpp> // Для использования JSON
#include "file_handler.h"
#include "action.h"
#include "connection.h"
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

/*
inline int start_server() {


    // Работа с клиентом
    int client_socket = 0;
    socklen_t addr_len = sizeof addr;
    while ((client_socket = accept(sock_fd, reinterpret_cast<struct sockaddr *>(&addr), &addr_len))) {
        // Accept() используется для принятия запроса на соединение,
        // полученного в сокете, который прослушивало приложение.
        if (client_socket == -1) {
            std::cerr << m_time() << "[ERROR] Accept error" << std::endl;
            return 1;
        }

        // Если подключится клиент, выводим уведомление
        std::cout << m_time() << "[SERVER] Accepted new connection from client with an " << inet_ntoa(addr.sin_addr)
                  << ":" << ntohs(addr.sin_port) << std::endl;

        // Для отправки данных клиенту
        std::string msg{"Hello! I,m Server"};
        if (const size_t transmitted = send(client_socket, msg.data(), msg.size(), 0); transmitted != msg.size()) {
            std::cerr << m_time() << "[ERROR] not all data transmitted" << std::endl;
            return 1;
        }

        // Для получения данных от клиента
        unsigned char buffer[512] = {'\0'};
        if (const ssize_t received = recv(client_socket, buffer, 512, 0); received <= 0) {
            std::cerr << m_time() << "[ERROR] Error recv()" << std::endl;
        }
        // Парс JSON
        nlohmann::json _json = nlohmann::json::parse(buffer);

        Writing_to_the_database(_json);

    }
    return 0;
}*/
