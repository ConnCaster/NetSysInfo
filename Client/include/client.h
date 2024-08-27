#pragma once
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <ctime>
#include <nlohmann/json.hpp>

inline std::string m_time(const time_t now = time(nullptr)) {
    const tm *ltm {localtime(&now)};
    return "[" + std::to_string(ltm->tm_mday) + ":" + std::to_string(ltm->tm_mon) + ":" + std::to_string(1900 + ltm->tm_year) +
        " " + std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec) + "] ";
}

class  User {
private:
    std::string m_nickname{};
public:
    static std::string nickname() {
        std::cout << "Enter your nickname: ";
        std::string name;
        std::cin >> name;
        return name;
    }
};

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

    const int ret = connect(sock_fd, reinterpret_cast<const struct sockaddr*>(&addr),sizeof(addr));
        if (ret == -1) {
        std::cerr << m_time() << "[ERROR] Connection ERROR to " << inet_ntoa(addr.sin_addr) << std::endl;
        return 1;
    }

    std::cout << m_time() << "[CLIENT] Connection to " << inet_ntoa(addr.sin_addr) << ":" << ntohs(addr.sin_port)
    << " established!" << std::endl;

    //JSON
    nlohmann::json my_json;
    my_json["name"] = User::nickname();

    // Для отправки данных на сервер
    const std::string msg{"Hello! I,m Client # 1"};
    if (const size_t transmitted = send(sock_fd, msg.data(), msg.size(), 0); transmitted != msg.size()) {
        std::cerr << m_time() << "[ERROR] not all data transmitted" << std::endl;
        return 1;
    }

    // Для получения данных от сервера
    char buffer[64] = {'\0'};
    if (const ssize_t received = recv(sock_fd, buffer, sizeof(buffer), 0); received <= 0) {
        std::cerr << m_time() << "[ERROR] Error recv()" << std::endl;
    }
    std::cout << m_time() << "[SERVER] " << buffer << std::endl;

    return 0;
}