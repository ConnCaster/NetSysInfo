#include <iostream>
#include <client.h>
#include <thread>
#include <arpa/inet.h>

#include "cli_connection.h"
#include "utils.h"


Client::Client(const uint16_t port)
    : port_(port) {
    // Файловый дескриптор сокета
    sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET указывает семейство протоколов IPv4
    // SOCK_STREAM опрделяет тип сокета TCP
    // 0 - протокол по умолчанию

    if (sock_fd_ == -1) {
        std::cerr << Time() << "[ERROR] Socket()" << std::endl;
    }
    // Определяем адрес сервера
    addr_.sin_family = AF_INET; // AF_INET указывает семейство протоколов IPv4
    addr_.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr_.sin_port = htons(5000); // htons(): эта функция используется для преобразования беззнакового целого числа
    // из машинного порядка байтов в сетевой порядок байтов.
    // 5000 - порт, который клиент будет искать на сервере, чтобы подключиться

}

void Client::Run()  {
    // Соеденение с сервером
    while (true) {
        int ret = connect(sock_fd_, reinterpret_cast<const struct sockaddr*>(&addr_),sizeof(addr_));
        if (ret == -1) {
            std::cerr << Time() << "[ERROR] Connection ERROR to " << inet_ntoa(addr_.sin_addr) << std::endl;
        } else {
            std::cout << Time() << "[CLIENT] Connection to " << inet_ntoa(addr_.sin_addr) << ":" << ntohs(addr_.sin_port)
            << " established!" << std::endl;

            std::unique_ptr<Conection> connect_ptr = std::make_unique<Conection>(sock_fd_);
        }
        std::this_thread::sleep_for(std::chrono::seconds (5));

        sock_fd_ = (socket(AF_INET, SOCK_STREAM, 0));
        if (sock_fd_ == -1) {
            std::cerr << Time() << "[ERROR] Socket()" << std::endl;
        }
    }
}

