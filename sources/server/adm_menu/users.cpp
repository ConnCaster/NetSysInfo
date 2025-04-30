#include <string>
#include <filesystem>

#include "sql_database.h"
#include "menu.h"
#include "utils.h"

int ListUsers::RequestChoice() {
    int id_cmd;
    std::cout << "\nChoose the information you are interested in from the suggested options:\n" <<
        "1. The user's name and serial number of his hard drive;\n" <<
        "2. The amount of user RAM\n" << ">> ";
    std::cin >> id_cmd;
    while (id_cmd < id_cmd_min_ || id_cmd > id_cmd_max_) {
        std::cout << "\nThere is no such item, please select an item from the suggested options\n" << ">> ";
        std::cin >> id_cmd;
    }
    return id_cmd;
}

std::string ListUsers::ReturnNameCmd (int id_cmd) {
    switch (id_cmd) {
        case 1:
            return "The users name and serial number of his hard drive";
        case 2:
            return "The amount of user RAM";
    }
}

int ListUsers::UserChoice() {
    if (list_users_.size() == 0) {
        std::cout << "\nThe list of registration users is empty" << std::endl;
        return 0;
    }
    std::cout << "\nSelect the user number: ";
    int num_user;
    std::cin >> num_user;
    while (num_user > list_users_.size() || num_user < 1) {
        std::cout << "\nThere is no user under this number\nSelect the request number: ";
        std::cin >> num_user;
    }
    return num_user;
}

int ListUsers::ActionChoise() {
    std::cout << "\nPlease select an item:\n"
    << "0. Back\n" << "1. Deleted this user\n" << "2. Send a request to the client for information\n" << ">> ";
    int decision;
    std::cin >> decision;

    return decision;
}

// Действия со списком Пользователей
int ListUsers::Actions() {
    int num_user = UserChoice();

    int decision = ActionChoise();

    switch (decision) {
        case 0:
            return 0;
        case 1: {
            std::string command {"rm " + list_users_[num_user - 1]};
            system(command.data());

            list_users_.erase(list_users_.begin() + (num_user-1));

            return 1; // Удаление
        }
        case 2: {
            auto root_path_users_cmd_line = CreateRootDir("database/users_cmd_line/");
            root_path_users_cmd_line += ExtractionNameDB(list_users_[num_user - 1]);
            SQliteDB sql_user_record_cmd(root_path_users_cmd_line);

            int id_cmd = RequestChoice();

            json j_request_cmd = json::object({{"name_cmd", ReturnNameCmd(id_cmd)}, {"id_cmd", id_cmd}});

            sql_user_record_cmd.write(j_request_cmd);

            return 2;
        }
    }
}

// Список Пользователей
int ListUsers::Execute() {
    // Подготовка списка
    auto root_path_users = CreateRootDir("database/users/");
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator(root_path_users);

    for (; iterator != std::filesystem::end(iterator); iterator++) {
        list_users_.push_back(iterator->path().string());
    }

    // Вывод списка
    std::cout << "\nUsers:" << std::endl;
    for (int i = 0; i < list_users_.size(); i++) {
        std::cout << i + 1 << ". " << ExtractionNameJson(list_users_[i]) << std::endl;

    }

    while (list_users_.size() > 0 && Actions() != 0) {
        // Вывод списка
        std::cout << "\nUsers:" << std::endl;
        for (int i = 0; i < list_users_.size(); i++) {
            std::cout << i + 1 << ". " << ExtractionNameJson(list_users_[i]) << std::endl;
        }
        Actions();
    }
    if (list_users_.size() == 0) {
        std::cout << "\nThe list of registration users is empty" << std::endl;
        return 0;
    }
    return 0;
}
