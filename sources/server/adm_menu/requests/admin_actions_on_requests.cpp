#include <filesystem>
#include <algorithm>

#include "utils.h"
#include "adm_menu/menu.h"


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
            std::string new_path{root_path_users.string() + ExtractionNameDB(list_requests_[num_request - 1]) + ".db3"};
            try {
                std::filesystem::rename(list_requests_[num_request - 1], new_path);
            } catch (...) {
                std::cerr << "Error during user registration" << std::endl;
            }

            auto end_element = std::remove(list_requests_.begin(), list_requests_.end(), list_requests_[num_request-1]);
            list_requests_.erase(end_element);

            return 1; // Регистрация
        }
        case 2: {
            std::string command{"rm " + list_requests_[num_request - 1]};
            system(command.data());


            auto end_element = std::remove(list_requests_.begin(), list_requests_.end(), list_requests_[num_request-1]);
            list_requests_.erase(end_element);

            return 1; // Удаление
        }
    }
}
