#include "client.h"


int main() {

    try {
        Client client(5000);
        client.Run();
    }
    catch (const std::runtime_error err) {
        Log client_log("client");
        client_log.Get_log() << err.what() << std::endl;
    }
    catch (...) {
        Log client_log("client");
        client_log.Get_log() << "[ERROR] [CLIENT] Unknown exception" << std::endl;
    }



    return 0;
}

