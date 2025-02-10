#include <fstream>
#include <iostream>

#include "cli_connection.h"
#include "utils.h"


Conection::Conection(const int sock_fd)
    : socket_fd_(sock_fd), input_buffer_(), output_buffer_() {
    DoStart();
}

void Conection::DoStart() {

    nlohmann::json im_json;
    im_json["action"] = "authUser";

    im_json["args"] = { {"name", Nickname()}, {"serial", SerialHardDdrive()} };
    SendMsg(im_json);
}

void Conection::RecvMsg() {
    // Получение сообщения от сервера
    if (const ssize_t received = recv(socket_fd_, input_buffer_.data(), 512, 0); received <= 0) {
        std::cerr << Time() << "[ERROR] Error recv()" << std::endl;
        return;
    }

    // Парс JSON
    nlohmann::json answer = nlohmann::json::parse(input_buffer_.data());

    std::cout <<Time() << "[SERVER] " << answer["answer"] << std::endl;

}

void Conection::SendMsg(const nlohmann::json &send_json) {

    SetOutputBuffer(send_json.dump());
    if (const size_t transmitted = send(socket_fd_, output_buffer_.data(), output_buffer_.size(), 0); transmitted != output_buffer_.size()) {
        std::cerr << Time() << "[ERROR] not all data transmitted" << std::endl;
    }
    RecvMsg();
}


