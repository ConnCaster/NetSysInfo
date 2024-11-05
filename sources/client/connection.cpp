#include "connection.h"


Conection::Conection(const int sock_fd)
    : socket_fd_(sock_fd) {
    DoStart();
}

// Получение серийного номера жесткого диска
inline std::string serial_hard_drive () {
    char c_serial[20];
    std::string str_serial{}; // ????

    FILE *fp = popen("udevadm info --query=all --name=/dev/nvme0n1p1  | grep ID_SERIAL_SHORT", "r");
    if (fp == nullptr) std::cerr << "[ERROR] File not open" << std::endl;

    while (fgets(c_serial, sizeof(c_serial), fp) != nullptr) {} // Почему-то не работает, если я вместо с_serial пишу str.data() (заранее созданный)
    //нет проверки работы fgets()

    std::string s_serial{std::string(c_serial)}; //22413C462705

    if (const int status = pclose(fp); status == -1) std::cerr <<  "[ERROR] File not close" << std::endl;

    return s_serial;
}

// Для ввода никнейма
inline std::string nickname() {
    std::cout << "Enter your nickname: ";
    std::string nicknmae{};
    std::cin >> nicknmae;

    return nicknmae;
}

void Conection::DoStart() {
    nlohmann::json im_json;
    im_json["action"] = "authUser";
    im_json["args"] = { {"name", nickname()}, {"serial", serial_hard_drive()} };
    std::string test_str = im_json.dump();
    Send_msg(socket_fd_, im_json);
}

void Conection::Recv_msg() {
    // Получение сообщения от пользователя
    if (const ssize_t received = recv(socket_fd_, input_buffer_.data(), 512, 0); received <= 0) {
        std::cerr << Time() << "[ERROR] Error recv()" << std::endl;
        return;
    }
    // Парс JSON
    nlohmann::json answer = nlohmann::json::parse(input_buffer_.data());
    std::cout <<Time() << "[SERVER] " << answer["answer"] << std::endl;
    //Send()
}

void Conection::Send_msg(const int connection_socket, const nlohmann::json &send_json) {
    // TODO (Viktor): Сериализация строки data
    // Не смог привязать output
    // А что если тип не string?

    const std::string str_json = send_json.dump();
    if (const size_t transmitted = send(connection_socket, str_json.data(), str_json.size(), 0); transmitted != str_json.size()) {
        std::cerr << Time() << "[ERROR] not all data transmitted" << std::endl;
    }
    Recv_msg();
}


