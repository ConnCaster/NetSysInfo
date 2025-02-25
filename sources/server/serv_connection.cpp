#include "serv_connection.h"
#include "request_handler.h"
#include "utils.h"
#include "factory.h"



Conection::Conection(const int client_socket)
    : connection_socket_(client_socket), input_buffer_{}, output_buffer_{} {

    // Для записи дествий сервера
    auto root_path_log = CreateRootDir("../../../log/server.txt");
    log.open(root_path_log, std::ios::in | std::ios::out | std::ios::app);

    DoStart();
}

void Conection::DoStart() {
    Recv_msg();
}

void Conection::Recv_msg() {
    // Получение сообщения от пользователя
    if (const ssize_t received = recv(connection_socket_, input_buffer_.data(), 512, 0); received <= 0) {
        log << Time() << "[ERROR] Error recv()" << std::endl;
        return;
    }

    try {
        std::unique_ptr<ReqHandler> req_handler_ptr = std::make_unique<ReqHandler>(input_buffer_);
    } catch (...) {
        // TODO: подумать об обработке Exception.
        //  Можно ли продолжать исполнение,
        //  если handler не сконструировался и данные не обработались
    }


    // Обработка действия
//    if (const auto action = ActionFactory::ActionFact(action_str)) {
//        nlohmann::json answer;
//        if( action->execute(cli_json)) {
//            answer["answer"] = "You have successfully registered";
//            Send_msg(answer);
//        } else {
//            answer["answer"] = "There is already such a user";
//            Send_msg(answer);
//        }
//    }
    //Send_msg();
}

void Conection::Send_msg(const nlohmann::json &send_json) {
    // TODO (Viktor): Сериализация строки data

    SetOutputBuffer(send_json.dump());

    if (const size_t transmitted = send(connection_socket_, output_buffer_.data(), output_buffer_.size(), 0); transmitted != output_buffer_.size()) {
    log << Time() << "[ERROR] not all data transmitted" << std::endl;
    }
    //Recv_msg()
}


