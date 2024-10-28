#pragma once
#include "server.h"


class Conection {
private:
    int conection_socket_{0};

    void Recv_msg();

    nlohmann::json Send_msg();
public:
    Conection(const int client_socket)
        : conection_socket_(client_socket) {
        Recv_msg();
    }
    Conection(){}

};