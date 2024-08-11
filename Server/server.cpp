#include "server.h"

int main() {
    const int ret = start_server();
    if (ret == 1) {
        std::cerr << "[ERROR] The client could not be started" << std::endl;
    }
    return 0;
}

