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
        SendMsg(req_handler_ptr->GetResponse());
    }
}

void Conection::SendMsg(const json &j_send) {
    json auth_json;
    int end_flag{0};

    if (output_buffer_[0] != '\000') {

        if (j_send.is_object() && j_send["id_cmd"] == 0) {
            SetOutputBuffer(j_send.dump());
            end_flag = 1;
        } else {
            std::string auth_str{output_buffer_.begin(), output_buffer_.end()};
            auth_json = json::parse(auth_str);
            auth_json["data"] = j_send;
            SetOutputBuffer(auth_json.dump());
        }
    } else {
        SetOutputBuffer(j_send.dump());
    }

    if (const size_t transmitted = send(socket_fd_, output_buffer_.data(), output_buffer_.size(), 0); transmitted != output_buffer_.size()) {
        std::cerr << Time() << "[ERROR] not all data transmitted" << std::endl;
    }

    if (end_flag != 0) {
        return;
    } else {
        RecvMsg();
    }
}





