#include "server.h"

// Сборка сервера
Server::Server(uint16_t port)
    : port_(port) {
    // Файловый дескриптор сокета
    sock_fd_ = socket(AF_INET, SOCK_STREAM, 0);
    // AF_INET указывает семейство протоколов IPv4
    // SOCK_STREAM опрделяет тип сокета TCP
    // 0 - протокол по умолчанию

    if (sock_fd_== -1) {
        std::cerr << Time() << "[ERROR] Socket()" << std::endl;
        throw std::runtime_error("[ERROR] Socket()");
    }

    // Чтобы сервер не привязывался к адресу (который может быть в состоянии ожидания, SO_REUSEADDR, сразу после отключения
    //отвязывает сервер от адреса и следовательно его можно повторно запустить по тому же адресу)
    constexpr int optval = 1;
    int ret = setsockopt(sock_fd_, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (ret == -1) {
        std::cerr << Time() << "[ERROR] Setsockopt error" << std::endl;
        throw std::runtime_error("[ERROR] Setsockopt error");
    }

    // Определяем адрес клиента
    addr_.sin_family = AF_INET;     // AF_INET указывает семейство протоколов IPv4
    addr_.sin_port = htons(5000); // htons(): эта функция используется для преобразования беззнакового целого числа
    // из машинного порядка байтов в сетевой порядок байтов.
    // 5000 - порт, который будет слушать наш сервер
    addr_.sin_addr.s_addr = htonl(INADDR_ANY);    //INADDR_ANY: используется, когда мы не хотим привязывать наш сокет
    // к какому-либо конкретному IP-адресу и вместо этого заставляем его
    // прослушивать все доступные IP-адреса.

    // Чтобы привязать файловой дескриптор сокета к выброному домену
    ret = bind(sock_fd_, reinterpret_cast<const struct sockaddr*>(&addr_), sizeof(addr_));
    // reinterpret_cast - для преобразования указателя на sockaddr_in в указатель sockaddr
    if (ret == -1) {
        std::cerr << Time() << "[ERROR] Bind error" << std::endl;
        throw std::runtime_error("[ERROR] Bind error");
    }

    // Для прослушивания сокета
    ret = listen(sock_fd_, 5);
    // sock_fd - какой сокет слушать
    // 5 - сколько запросов на подключение может быть помещены в очередь, прежде чем будут отклонены дальнейшие запросы
    if (ret == -1) {
        std::cerr << Time() << "[ERROR] Listen error" << std::endl;
        throw std::runtime_error("[ERROR] Listen error");
    }
}

// Запуск сервера
void Server::Run() {
    // Работа с клиентом
    socklen_t addr_len = sizeof(addr_);
    client_socket_ = accept(sock_fd_, reinterpret_cast<struct sockaddr *>(&addr_), &addr_len);
        // Accept() используется для принятия запроса на соединение,
        // полученного в сокете, который прослушивало приложение.
        if (client_socket_ == -1) {
            std::cerr << Time() << "[ERROR] Accept error" << std::endl;
            return;
        }

    // Если подключится клиент, выводим уведомление
    std::cout << Time() << "[SERVER] Accepted new connection from client with an " << inet_ntoa(addr_.sin_addr)
              << ":" << ntohs(addr_.sin_port) << std::endl;

    Conection conect(Get_client_socket_());
}
