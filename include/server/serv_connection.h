#pragma once

#include <iostream>
#include <nlohmann/json.hpp>
#include <sys/socket.h>
#include "utils.h"
#include "factory.h"

constexpr unsigned int buf_size = 512;

class Conection {
private:
    int connection_socket_{0};
    int socket_fd_{0};
    std::array<unsigned char, buf_size> input_buffer_;
    std::array<unsigned char, buf_size> output_buffer_;

public:
    explicit Conection(const int client_socket);
private:
    void DoStart();
    void Recv_msg();
    void Send_msg(const nlohmann::json &send_json);
};