

#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>

// TODO: 1) port uint16?
//       2) ip uint32_t?
//       3) accept args


int main() {

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        std::cout << "[ERROR] Socket()" << std::endl;
        return 1;
    }

    int optval = 1;
    int ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
    if (ret == -1) {
        std::cout << "Setsockopt error" << std::endl;
        return 1;
    }

    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_port = htons(5000);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    ret = bind(sock_fd, reinterpret_cast<const struct sockaddr*>(&addr), sizeof(addr));
    if (ret == -1) {
        std::cout << "Bind error" << std::endl;
        return 1;
    }

    ret = listen(sock_fd, 5);
    if (ret == -1) {
        std::cout << "Listen error" << std::endl;
        return 1;
    }

    int client_socket = 0;
    while (client_socket = accept(sock_fd, nullptr, nullptr)) {
        if (client_socket == -1) {
            std::cout << "Accept error" << std::endl;
            return 1;
        }
        puts("[SERVER] Accepted new connection from client");
        char buffer[64] = {'\0'};
        int received = recv(client_socket, buffer, 64, 0);
        if (received <= 0) {
            puts("Error recv()");
        }
        std::cout << buffer << std::endl;
    }

    return 0;
}