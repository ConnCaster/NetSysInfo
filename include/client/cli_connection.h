#pragma once

#include <iostream>
#include <unistd.h>
#include <nlohmann/json.hpp>
#include <sys/socket.h>
#include "utils.h"

constexpr unsigned int buf_size = 512;

class Conection {
private:
    int socket_fd_{0};
    std::array<unsigned char, buf_size> input_buffer_;
    std::array<unsigned char, buf_size> output_buffer_;
public:
    explicit Conection(const int sock_fd);

    ~Conection() {
        shutdown(socket_fd_,2);
        close(socket_fd_);
    }

private:
    void DoStart();
    void Recv_msg();
    void Send_msg(int connection_socket, const nlohmann::json &send_json);
};