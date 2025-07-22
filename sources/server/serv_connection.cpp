#include "serv_connection.h"
#include "s_request_handler.h"
#include "utils.h"


Conection::Conection(const int client_socket)
    : server_log_("server"), connection_socket_(client_socket), input_buffer_{}, output_buffer_{} {
    DoStart();

}

void Conection::DoStart() {
    Recv_msg();
}

void Conection::Recv_msg() {
    // Получение сообщения от пользователя
    if (const ssize_t received = recv(connection_socket_, input_buffer_.data(), 512, 0); received <= 0) {
        server_log_.Get_log() << Time() << "[ERROR] Error recv()" << std::endl;
        return;
    }

    try {
        const auto req_handler_ptr {std::make_unique<ReqHandler>(input_buffer_)};
        Send_msg(req_handler_ptr->GetResponse());
    } catch (const std::exception& err)  {
        server_log_.Get_log() << Time() << "[ERROR] " << err.what() << std::endl;

        // TODO: подумать об обработке Exception.
        //  Можно ли продолжать исполнение,
        //  если handler не сконструировался и данные не обработались
    }
}

void Conection::Send_msg(const nlohmann::json &send_json) {
    SetOutputBuffer(send_json.dump());

    if (const size_t transmitted = send(connection_socket_, output_buffer_.data(), output_buffer_.size(), 0); transmitted != output_buffer_.size()) {
    server_log_.Get_log() << Time() << "[ERROR] not all data transmitted" << std::endl;
    }
    Recv_msg();
}


