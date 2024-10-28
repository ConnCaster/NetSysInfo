#pragma once
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctime>
#include <nlohmann/json.hpp>

// Для использования даты и времени
inline std::string m_time(const time_t now = time(nullptr)) {
    const tm *ltm {localtime(&now)};
    return "[" + std::to_string(ltm->tm_mday) + ":" + std::to_string(ltm->tm_mon) + ":" + std::to_string(1900 + ltm->tm_year) +
        " " + std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec) + "] ";
}

// Получение серийного номера жесткого диска
inline std::string serial_hard_drive () {
    char c_serial[20];

    FILE *fp = popen("udevadm info --query=all --name=/dev/sda  | grep ID_SERIAL_SHORT", "r");
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

inline int start_client() {
    // Файловый дескриптор сокета
    const int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET указывает семейство протоколов IPv4
    // SOCK_STREAM опрделяет тип сокета TCP
    // 0 - протокол по умолчанию

    if (sock_fd == -1) {
        std::cerr << m_time() << "[ERROR] Socket()" << std::endl;
        return 1;
    }

    // Определяем адрес сервера
    struct sockaddr_in addr{}; // sockaddr_in - это тип данных, который используется для хранения адреса сокета
    addr.sin_family = AF_INET; // AF_INET указывает семейство протоколов IPv4
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(5000); // htons(): эта функция используется для преобразования беззнакового целого числа
    // из машинного порядка байтов в сетевой порядок байтов.
    // 5000 - порт, который клиент будет искать на сервере, чтобы подключиться

    // Соеденение с сервером
    if (const int ret = connect(sock_fd, reinterpret_cast<const struct sockaddr*>(&addr),sizeof(addr)); ret == -1) {
        std::cerr << m_time() << "[ERROR] Connection ERROR to " << inet_ntoa(addr.sin_addr) << std::endl;
        return 1;
    }

    std::cout << m_time() << "[CLIENT] Connection to " << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port)
    << " established!" << std::endl;

    /*
    // Для получения данных от сервера
    char buffer[64] = {'\0'};
    if (const ssize_t received = recv(sock_fd, buffer, sizeof(buffer), 0); received <= 0) {
        std::cerr << m_time() << "[ERROR] Error recv()" << std::endl;
    }
    std::cout << m_time() << "[SERVER] " << buffer << std::endl;*/

    // Для отправки JSON на сервер
    nlohmann::json cli_json;
    cli_json["action"] = "authUser";
    cli_json["args"] = { {"name", nickname()}, {"serial", serial_hard_drive()} };

    const std::string str_json = cli_json.dump();

    if (const size_t transmitted = send(sock_fd, str_json.data(), str_json.size(), 0); transmitted != str_json.size()) {
        std::cerr << m_time() << "[ERROR] Not all data transmitted" << cli_json.size() << " BYTES" << std::endl;
        return 1;
    }
    return 0;
}