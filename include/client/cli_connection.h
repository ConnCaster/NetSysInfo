#pragma once

#include <unistd.h>
#include <nlohmann/json.hpp>
#include <sys/socket.h>

constexpr unsigned int buf_size = 512;

class Conection {
private:
    int socket_fd_{0};
    std::array<unsigned char, buf_size> input_buffer_;
    std::array< char, buf_size> output_buffer_;
public:
    explicit Conection(const int sock_fd);

    void SetOutputBuffer(const std::string &answer) {
    strcpy(output_buffer_.data(), answer.data());
    }

    ~Conection() {
        shutdown(socket_fd_,2);
        close(socket_fd_);
    }

private:
    void DoStart();
    void RecvMsg();
    void SendMsg(const nlohmann::json &send_json);
};