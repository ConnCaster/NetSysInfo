#include "connection.h"


Conection::Conection(const int client_socket)
    : conection_socket_(client_socket) {
    DoStart();
}

void Conection::DoStart() {
    Recv_msg();
}

void Conection::Recv_msg() {
    // Получение сообщения от пользователя
    if (const ssize_t received = recv(conection_socket_, input_buffer_.data(), 512, 0); received <= 0) {
        std::cerr << Time() << "[ERROR] Error recv()" << std::endl;
        return;
    }

    // Парс JSON
    nlohmann::json cli_json = nlohmann::json::parse(input_buffer_.data());

    std::string action_str{};
    try {
        action_str = cli_json["action"].get<std::string>();
    } catch (...) {
        return;
    }

    // Обработка действия
    if (const auto action = ActionFactory::Action_(action_str)) {
        nlohmann::json answer;
        if( action->execute(cli_json)) {
            answer["answer"] = "You have successfully registered";
            Send_msg(conection_socket_,answer);
        } else {
            answer["answer"] = "There is already such a user";
            Send_msg(conection_socket_, answer);
        }
    }
}

    void Conection::Send_msg(const int connection_socket, const nlohmann::json &send_json) {
    // TODO (Viktor): Сериализация строки data
    // Не смог привязать output
    // А что если тип не string?

    const std::string str_json = send_json.dump();

    if (const size_t transmitted = send(connection_socket, str_json.data(), str_json.size(), 0); transmitted != str_json.size()) {
        std::cerr << Time() << "[ERROR] not all data transmitted" << std::endl;
    }
}


