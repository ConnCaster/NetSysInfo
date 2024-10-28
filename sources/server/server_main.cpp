#include "server.h"

// Останавливается на методе Run

int main() {
    try {
        Server server(5000);
        server.Run();

    }
    catch (const std::runtime_error err) {
        std::cerr << err.what() << std::endl;
    }
    catch (...) {
        std::cerr << "[ERROR] Unknown exception" << std::endl;
    }



    return 0;
}

