#include <iostream>

#include "list_info_req.h"

int RequestChoice() {
    int id_cmd;
    std::cout << "\nChoose the information you are interested in from the suggested options:\n" <<
        "1. The user's name and serial number of his hard drive;\n" <<
        "2. The amount of user RAM\n" << ">> ";
    std::cin >> id_cmd;
    while (id_cmd < idCmdMin || id_cmd > idCmdMax) {
        std::cout << "\nThere is no such item, please select an item from the suggested options\n" << ">> ";
        std::cin >> id_cmd;
    }
    return id_cmd;
}
