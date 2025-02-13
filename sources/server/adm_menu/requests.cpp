#include <string>
#include <filesystem>

#include "menu.h"
#include "utils.h"


// Действия со списком Запросов на регистрацию
int ListRequest::Actions(std::vector<std::string> &list_requests) {
    std::cout << "\nPlease select an item:\n"
    << "0. Back\n" << "1. Register a request\n" << "2. Deleted a request\n" << ">> ";
    int decision;
    std::cin >> decision;
    switch (decision) {
        case 0:
            return 0;
        case 1: {
            std::cout << "\nSelect the request number: ";
            int num_request;
            std::cin >> num_request;
            while (num_request > list_requests.size() || num_request < 1) {
                std::cout << "\nThere is no request under this number\nSelect the request number: ";
                std::cin >> num_request;
            }

            auto root_path_users = CreateRootDir("../../../database/users/");
            std::string new_path{root_path_users.string() + ExtractionName(list_requests[num_request - 1]) + ".json"};
            try {
                std::filesystem::rename(list_requests[num_request - 1], new_path);
            }
            catch (...) {
                std::cerr << "Error during user registration" << std::endl;
            }

            list_requests.erase(list_requests.begin() + (num_request-1));

            return 1; // Регистрация
        }
        case 2: {
            std::cout << "\nSelect the request number: ";
            int num_request;
            std::cin >> num_request;
            while (num_request > list_requests.size()) {
                std::cout << "\nThere is no request under this number\nSelect the request number: ";
                std::cin >> num_request;
            }

            std::string command {"rm " + list_requests[num_request - 1]};
            system(command.data());

            list_requests.erase(list_requests.begin() + (num_request-1));

            return 1; // Удаление
        }
    }
}

// Список запросов на регистрацию
int ListRequest::Choice() {
    // Подготовка списка
    std::vector<std::string> requests_users;
    auto root_path_requests = CreateRootDir("database/requests/");
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator(root_path_requests);

    for (; iterator != std::filesystem::end(iterator); iterator++) {
        requests_users.push_back(iterator->path().string());
    }

    // Вывод списка
    std::cout << "\nRequests:" << std::endl;
    for (int i = 0; i < requests_users.size(); i++) {
        std::cout << i + 1 << ". " << ExtractionName(requests_users[i]) << std::endl;
    }

    while (requests_users.size() > 0 && Actions(requests_users) != 0) {
        // Вывод списка
        std::cout << "\nRequests:" << std::endl;
        for (int i = 0; i < requests_users.size(); i++) {
            std::cout << i + 1 << ". " << ExtractionName(requests_users[i]) << std::endl;
        }
    }
    if (requests_users.size() == 0) {
        std::cout << "\nThe list of registration requests is empty" << std::endl;
        return 0;
    }
    return 0;
}
