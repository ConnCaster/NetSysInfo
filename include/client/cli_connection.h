#pragma once

#include <unistd.h>
#include <nlohmann/json.hpp>
#include <sys/socket.h>

using json = nlohmann::json;

constexpr unsigned int buf_size = 512;
constexpr std::string_view kIdKey = "id_cmd";

class Conection {
private:
    int socket_fd_{0};
    std::array<unsigned char, buf_size> input_buffer_;
    std::array<unsigned char, buf_size> output_buffer_;
public:
    explicit Conection(const int sock_fd);

    void SetOutputBuffer(const std::string &answer) {
        std::copy(answer.begin(), answer.end(), output_buffer_.data() + index_null_ter_());
    }

    ~Conection() {
        shutdown(socket_fd_,2);
        close(socket_fd_);
    }

private:
    int index_null_ter_();
    void DoStart();
    void RecvMsg();
    void SendMsg(const json &send_json);
};