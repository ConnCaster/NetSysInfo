#include "conection.h"

void Conection::Recv_msg() {
    // Получение сообщения от пользователя
    unsigned char buffer[512] = {'\0'};
    if (const ssize_t received = recv(conection_socket_, buffer, 512, 0); received <= 0) {
        std::cerr << m_time() << "[ERROR] Error recv()" << std::endl;
    }

    // Парс JSON
    nlohmann::json cli_json = nlohmann::json::parse(buffer);

    // Обработка действия
    Action* action = ActionFactory::action_registr(cli_json["action"]);
    if (action) {
        action->execute(cli_json);
        delete action;
    } else {
        std::cout << "There is no such action!\n";
    }
}


