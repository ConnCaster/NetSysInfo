#include <string>
#include <filesystem>

#include "menu.h"
#include "utils.h"

void ListUsers::PreparingTheList() {
    // Подготовка списка
    auto root_path_users = CreateRootDir("database/users/");
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator(root_path_users);

    for (; iterator != std::filesystem::end(iterator); iterator++) {
        list_users_.push_back(iterator->path().string());
    }
}

void ListUsers::OutputTheList() {
    std::cout << "\nUsers:" << std::endl;
    for (int i = 0; i < list_users_.size(); i++) {
        std::cout << i + 1 << ". " << ExtractionNameDB(list_users_[i]) << std::endl;

    }
}

// Список Пользователей
int ListUsers::Execute() {
    PreparingTheList();
    OutputTheList();

    while (list_users_.size() > 0 && Actions() != 0) {
        OutputTheList();
    }
    if (list_users_.size() == 0) {
        std::cout << "\nThe list of registration users is empty" << std::endl;
        return 0;
    }
    return 0;
}
