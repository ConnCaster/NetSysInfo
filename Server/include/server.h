#pragma once
#include <iostream>
#include <sys/socket.h>    // Для использования Socket()
#include <netinet/in.h>

inline int strat_server() {
    // Файловый дескриптор сокета
    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);      // Почему отсчет сокетов начинается с 3 ?

    // AF_INET указывает семейство протоколов IPv4
    // SOCK_STREAM опрделяет тип сокета TCP

    if (sock_fd == -1) {
        std::cout << "[ERROR] Socket()" << std::endl;
        return 1;
    }

    // Чтобы сервер не привязывался к адресу (который может быть в состоянии ожидания, SO_REUSEADDR, сразу после отключения
    //отвязывает сервер от адреса и следовательно его можно повторно запустить по тому же адресу)
    int optval = 1;
    int ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (ret == -1) {
        std::cout << "[ERROR] Setsockopt error" << std::endl;
        return 1;
    }

    // Определяем адрес сервера
    struct sockaddr_in addr{}; // sockaddr_in - это тип данных, который используется для хранения адреса сокета
    addr.sin_family = AF_INET;     // AF_INET указывает семейство протоколов IPv4
    addr.sin_port = htons(5000); // htons(): эта функция используется для преобразования беззнакового целого числа
    // из машинного порядка байтов в сетевой порядок байтов.
    // 5000 - порт, который будет слушать наш сервер
    addr.sin_addr.s_addr = htonl(INADDR_ANY);    //INADDR_ANY: используется, когда мы не хотим привязывать наш сокет
    // к какому-либо конкретному IP-адресу и вместо этого заставляем его
    // прослушивать все доступные IP-адреса.

    // Чтобы присвоить файловому дескриптору сокета локальный адрес
    ret = bind(sock_fd, reinterpret_cast<const struct sockaddr*>(&addr), sizeof(addr));
    // reinterpret_cast - для преобразования указателя на sockaddr_in в указатель sockaddr
    if (ret == -1) {
        std::cout << "[ERROR] Bind error" << std::endl;
        return 1;
    }

    // Для прослушивания сокета
    ret = listen(sock_fd, 5);
    // sock_fd - какой сокет слушать
    // 5 - сколько запросов на подключение может быть помещены в очередь, прежде чем будут отклонены дальнейшие запросы
    if (ret == -1) {
        std::cout << "[ERROR] Listen error" << std::endl;
        return 1;
    }

    // Работа с клиентом
    int client_socket = 0;
    while (client_socket = accept(sock_fd, nullptr, nullptr)) { // Accept() используется для принятия запроса на соединение,
        // полученного в сокете, который прослушивало приложение.
        if (client_socket == -1) {
            std::cout << "[ERROR] Accept error" << std::endl;
            return 1;
        }

        // Если подключится клиент, выводим уведомление
        puts("[SERVER] Accepted new connection from client");

        // Для получения данных от клиента
        char buffer[64] = {'\0'};
        int received = recv(client_socket, buffer, 64, 0); // recv - Считывает N байт в buffer из client_socket.
        if (received <= 0) {
            puts("[ERROR] Error recv()");
        }
        std::cout << buffer << std::endl;
    }
    return 0;
}
