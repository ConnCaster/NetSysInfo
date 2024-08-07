#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

int main() {

    int sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (sock_fd == -1) {
        std::cout << "[ERROR] Socket()" << std::endl;
        return 1;
    }

    struct sockaddr_in addr{};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_port = htons(5000);

    int ret = connect(sock_fd, reinterpret_cast<const struct sockaddr*>(&addr), sizeof(addr));
    if (ret == -1) {
        std::cout << "[ERROR] Connection ERROR to " << inet_ntoa(addr.sin_addr) << std::endl;
        return 1;
    }
    std::cout << "[CLIENT] Connection to " << inet_ntoa(addr.sin_addr) << " established!" << std::endl;

    std::string msg{"HELLO FROM CLIENT!"};
    size_t transmitted = send(sock_fd, msg.data(), msg.size(), 0);
    if (transmitted != msg.size()) {
        std::cout << "[ERROR] not all data transmitted" << std::endl;
        return 1;
    }
    std::cout << "[CLIENT] Msg is transmitted successfully" << std::endl;

    char buffer[64] = {'\0'};
    size_t recieved = recv(sock_fd, buffer, 64, 0);
    if (recieved <= 0) {
        std::cout << "[ERROR] answer from server error" << std::endl;
        return 1;
    }
    close(sock_fd);

    return 0;
}