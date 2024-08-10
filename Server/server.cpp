#include <server.h>


int main() {
    if (const int ret = strat_server(); ret == 1) {
        std::cerr << "[ERROR] The server could not be started" << std::endl;
    }
    return 0;
}
