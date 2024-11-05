#pragma once
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <nlohmann/json.hpp>
#include "utils.h"
#include "connection.h"


class Client {
private:
    int sock_fd_{0};
    uint16_t port_;
    struct sockaddr_in addr_{}; // sockaddr_in - это тип данных, который используется для хранения адреса сокета
public:
    explicit Client(uint16_t port);

    void Run() const;

    /*
    // Для отправки JSON на сервер
    nlohmann::json cli_json;
    cli_json["action"] = "authUser";
    cli_json["args"] = { {"name", nickname()}, {"serial", serial_hard_drive()} };

    const std::string str_json = cli_json.dump();

    if (const size_t transmitted = send(sock_fd, str_json.data(), str_json.size(), 0); transmitted != str_json.size()) {
        std::cerr << m_time() << "[ERROR] Not all data transmitted" << cli_json.size() << " BYTES" << std::endl;
        return 1;
    }


    // Для получения данных от сервера
    char buffer[64] = {'\0'};
    if (const ssize_t received = recv(sock_fd, buffer, sizeof(buffer), 0); received <= 0) {
        std::cerr << m_time() << "[ERROR] Error recv()" << std::endl;
    }
    std::cout << m_time() << "[SERVER] " << buffer << std::endl;*/
};