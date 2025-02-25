#include "serv_connection.h"
#include "s_request_handler.h"
#include "utils.h"



Conection::Conection(const int client_socket)
    : connection_socket_(client_socket), input_buffer_{}, output_buffer_{} {

    // Для записи дествий сервера
    auto root_path_log = CreateRootDir("log/");
    log.open(root_path_log.string() + "server.txt", std::ios::in | std::ios::out | std::ios::app);


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
        const auto req_handler_ptr {std::make_unique<ReqHandler>(input_buffer_)};
        Send_msg(req_handler_ptr->GetResponse());
    } catch (const std::exception& err)  {
        // При втором заходе некорректный json приходит
        int flag{};
        // TODO: подумать об обработке Exception.
        //  Можно ли продолжать исполнение,
        //  если handler не сконструировался и данные не обработались
    }
}

void Conection::Send_msg(const nlohmann::json &send_json) {
    // TODO (Viktor): Сериализация строки data

    SetOutputBuffer(send_json.dump());

    if (const size_t transmitted = send(connection_socket_, output_buffer_.data(), output_buffer_.size(), 0); transmitted != output_buffer_.size()) {
    log << Time() << "[ERROR] not all data transmitted" << std::endl;
    }

    Recv_msg();
}


