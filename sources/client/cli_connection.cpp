#include <fstream>
#include <iostream>

#include "cli_connection.h"
#include "c_request_handler.h"
#include "utils.h"
#include "c_factory.h"


Conection::Conection(const int sock_fd)
    : socket_fd_(sock_fd), input_buffer_(), output_buffer_() {
    DoStart();
}

void Conection::DoStart() {
    const auto auth_ptr {std::make_unique<Authentication>()};
    std::cout << auth_ptr->execute();
    SendMsg(auth_ptr->execute());
}

void Conection::RecvMsg() {
    // Получение сообщения от сервера
    if (const ssize_t received = recv(socket_fd_, input_buffer_.data(), 512, 0); received <= 0) {
        std::cerr << Time() << "[ERROR] Error recv()" << std::endl;
        return;
    }
    // Парс JSON
    json j_server = nlohmann::json::parse(input_buffer_.data());
    if (j_server.contains(kIdKey)) {
        const auto req_handler_ptr {std::make_unique<ReqHandler>(input_buffer_)};
        std::cout << req_handler_ptr->GetResponse();
        SendMsg(req_handler_ptr->GetResponse());
    }
}

void Conection::SendMsg(const json &send_json) {

    SetOutputBuffer(send_json.dump());
    if (const size_t transmitted = send(socket_fd_, output_buffer_.data(), output_buffer_.size(), 0); transmitted != output_buffer_.size()) {
        std::cerr << Time() << "[ERROR] not all data transmitted" << std::endl;
    }
    RecvMsg();
}

int Conection::index_null_ter_() {
    int it{0};
    if (output_buffer_[it] != '\000') {
        while (output_buffer_[it] != '\000') {
            it++;
        }
        output_buffer_[it - 1] = ',';
        return it;
    } else {
        return it;
    }
}




