#include <string>
#include <filesystem>

#include "menu.h"
#include "utils.h"

int ListRequest::RequestChoice() {
    std::cout << "\nSelect the request number: ";
    int num_request;
    std::cin >> num_request;
    while (num_request > list_requests_.size() || num_request < 1) {
        std::cout << "\nThere is no request under this number\nSelect the request number: ";
        std::cin >> num_request;
    }
    return num_request;
}

int ListRequest::ActionChoise() {
    std::cout << "\nPlease select an item:\n"
    << "0. Back\n" << "1. Register a request\n" << "2. Deleted a request\n" << ">> ";
    int decision;
    std::cin >> decision;
    return decision;
}

// Действия со списком Запросов на регистрацию
int ListRequest::Actions() {

    int num_request = RequestChoice();
    int decision = ActionChoise();

    switch (decision) {
        case 0:
            return 0;
        case 1: {
            auto root_path_users = CreateRootDir("database/users/");
            std::string new_path{root_path_users.string() + ExtractionNameJson(list_requests_[num_request - 1]) + ".json"};
            try {
                std::filesystem::rename(list_requests_[num_request - 1], new_path);
            }
            catch (...) {
                std::cerr << "Error during user registration" << std::endl;
            }

            list_requests_.erase(list_requests_.begin() + (num_request-1));

            return 1; // Регистрация
        }
        case 2: {
            std::string command {"rm " + list_requests_[num_request - 1]};
            system(command.data());

            list_requests_.erase(list_requests_.begin() + (num_request-1));

            return 1; // Удаление
        }
    }
}

// Список запросов на регистрацию
int ListRequest::Execute() {
    // Подготовка списка
    auto root_path_requests = CreateRootDir("database/requests/");
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator(root_path_requests);

    for (; iterator != std::filesystem::end(iterator); iterator++) {
        list_requests_.push_back(iterator->path().string());
    }

    // Вывод списка
    std::cout << "\nRequests:" << std::endl;
    for (int i = 0; i < list_requests_.size(); i++) {
        std::cout << i + 1 << ". " << ExtractionNameJson(list_requests_[i]) << std::endl;
    }

    while (list_requests_.size() > 0 && Actions() != 0) {
        // Вывод списка
        std::cout << "\nRequests:" << std::endl;
        for (int i = 0; i < list_requests_.size(); i++) {
            std::cout << i + 1 << ". " << ExtractionNameJson(list_requests_[i]) << std::endl;
        }
    }
    if (list_requests_.size() == 0) {
        std::cout << "\nThe list of registration requests is empty" << std::endl;
        return 0;
    }
    return 0;
}
