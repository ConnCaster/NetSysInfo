#include <iostream>

#include "client.h"


int main() {
    try {
        Client client(5000);
        client.Run();
    }
    catch (const std::runtime_error err) {
        std::cerr << err.what() << std::endl;
    }
    catch (...) {
        std::cerr << "[ERROR] [CLIENT] Unknown exception" << std::endl;
    }



    return 0;
}

