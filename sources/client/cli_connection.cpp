#include <fstream>

#include "cli_connection.h"

#include <iostream>

#include "c_request_handler.h"
#include "utils.h"
#include "c_factory.h"

Conection::Conection(const int sock_fd)
    : client_log_("client"), socket_fd_(sock_fd), input_buffer_(), output_buffer_() {
    DoStart();
}

void Conection::DoStart() {
    const auto auth_ptr {std::make_unique<Authentication>()};
    SendMsg(auth_ptr->execute());
}

void Conection::RecvMsg() {
    // Получение сообщения от сервера
    try {
        if (const ssize_t received = recv(socket_fd_, input_buffer_.data(), 512, 0); received <= 0) {
            client_log_.Get_log() << Time() << "[ERROR] Error recv()" << std::endl;
            return;
        }
        // Парс JSON
        json j_server = nlohmann::json::parse(input_buffer_.data());
        if (j_server.contains(kIdKey)) {
            const auto req_handler_ptr{std::make_unique<ReqHandler>(j_server)};
            SendMsg(req_handler_ptr->GetResponse());
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}

void Conection::SendMsg(const json &j_send) {
    try {
        json auth_json;

        if (output_buffer_[0] != '\000') {

            if (j_send.is_object() && j_send[kIdKey] == kIdCmdEndSession) {
                SetOutputBuffer(j_send.dump());
            } else {
                std::string auth_str{output_buffer_.begin(), output_buffer_.end()};
                auth_json = json::parse(auth_str);
                auth_json[kDataKey] = j_send;
                SetOutputBuffer(auth_json.dump());
            }
        } else {
            SetOutputBuffer(j_send.dump());
        }

        if (const size_t transmitted = send(socket_fd_, output_buffer_.data(), output_buffer_.size(), 0); transmitted != output_buffer_.size()) {
            client_log_.Get_log() << Time() << "[ERROR] not all data transmitted" << std::endl;
        }

        if (j_send.contains(kIdKey) && j_send[kIdKey] == kIdCmdEndSession) {
            client_log_.Get_log() << Time() << "[Server] There are no requests for your profile in the queue" << std::endl;
            return;
        } else {
            RecvMsg();
        }
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }
}