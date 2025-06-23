#include <string>
#include <filesystem>

#include "menu.h"
#include "utils.h"

void ListUsers::Preparing_the_list() {
    // Подготовка списка
    auto root_path_users = CreateRootDir("database/users/");
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator(root_path_users);

    for (; iterator != std::filesystem::end(iterator); iterator++) {
        list_users_.push_back(iterator->path().string());
    }
}

void ListUsers::Output_the_list() {

    // Вывод списка
    std::cout << "\nUsers:" << std::endl;
    for (int i = 0; i < list_users_.size(); i++) {
        std::cout << i + 1 << ". " << ExtractionNameDB(list_users_[i]) << std::endl;

    }
}

// Список Пользователей
int ListUsers::Execute() {
    Preparing_the_list();
    Output_the_list();

    while (list_users_.size() > 0 && Actions() != 0) {
        // Вывод списка
        std::cout << "\nUsers:" << std::endl;
        Output_the_list();
        Actions();
    }
    if (list_users_.size() == 0) {
        std::cout << "\nThe list of registration users is empty" << std::endl;
        return 0;
    }
    return 0;
}
