#include <string>
#include <filesystem>

#include "menu.h"
#include "utils.h"



// Действия со списком Пользователей
int ListUsers::Actions(std::vector<std::string> &list_user) {
    std::cout << "\nPlease select an item:\n"
    << "0. Back\n" << "1. Deleted a user\n" << ">> ";
    int decision;
    std::cin >> decision;
    switch (decision) {
        case 0:
            return 0;
        case 1: {
            std::cout << "\nSelect the user number: ";
            int num_user;
            std::cin >> num_user;
            while (num_user > list_user.size() || num_user < 1) {
                std::cout << "\nThere is no user under this number\nSelect the request number: ";
                std::cin >> num_user;
            }

            std::string command {"rm " + list_user[num_user - 1]};
            system(command.data());

            list_user.erase(list_user.begin() + (num_user-1));

            return 1; // Удаление
        }
    }
}

// Список Пользователей
int ListUsers::Choice() {
    // Подготовка списка
    std::vector<std::string> list_users;
    auto root_path_users = CreateRootDir("database/users/");
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator(root_path_users);

    for (; iterator != std::filesystem::end(iterator); iterator++) {
        list_users.push_back(iterator->path().string());
    }

    // Вывод списка
    std::cout << "\nUsers:" << std::endl;
    for (int i = 0; i < list_users.size(); i++) {
        std::cout << i + 1 << ". " << ExtractionName(list_users[i]) << std::endl;

    }

    while (list_users.size() > 0 && Actions(list_users) != 0) {
        // Вывод списка
        std::cout << "\nUsers:" << std::endl;
        for (int i = 0; i < list_users.size(); i++) {
            std::cout << i + 1 << ". " << ExtractionName(list_users[i]) << std::endl;
        }
        Actions(list_users);
    }
    if (list_users.size() == 0) {
        std::cout << "\nThe list of registration users is empty" << std::endl;
        return 0;
    }
    return 0;
}
