#include "menu.h"
#include "server.h"
#include "utils.h"
#include <string>
#include <filesystem>
#include <vector>

// TODO [Victor] : Общий путь для файла через флаги компиляции (флаги условной компиляции) СMake

// Выключение сервера
int TurnOff::Choice() {
    exit(0);
}
// Включение сервера
int TurnOn::Choice() {
    try {
        Server server(5000);
        server.Run();

    }
    catch (const std::runtime_error err) {
        std::cerr << err.what() << std::endl;
    }
    catch (...) {
        std::cerr << "[ERROR] [SERVER] Unknown exception" << std::endl;
    }
    return 0;
}

// Действия со списком Запросов на регистрацию
int ListRequest::Actions(std::vector<std::string> &user) {
    std::cout << "\nPlease select an item:\n"
    << "0. Back\n" << "1. Register a request\n" << "2. Deleted a request\n" << ">> ";
    int act;
    std::cin >> act;
    switch (act) {
        case 0:
            return 0;
        case 1: {
            std::cout << "\nSelect the request number: ";
            int num;
            std::cin >> num;
            while (num > user.size() || num < 1) {
                std::cout << "\nThere is no request under this number\nSelect the request number: ";
                std::cin >> num;
            }

            std::string new_path {"/home/user/Projects/C++/Client-Server/database/users/" + ExtractionName(user[num - 1]) + ".json"};
            try {
                std::filesystem::rename(user[num - 1], new_path);
            }
            catch (...) {
                std::cerr << "Error during user registration" << std::endl;
            }

            user.erase(user.begin() + (num-1));

            return 1; // Регистрация
        }
        case 2: {
            std::cout << "\nSelect the request number: ";
            int num;
            std::cin >> num;
            while (num > user.size()) {
                std::cout << "\nThere is no request under this number\nSelect the request number: ";
                std::cin >> num;
            }

            std::string command {"rm " + user[num - 1]};
            system(command.data());

            user.erase(user.begin() + (num-1));

            return 1; // Удаление
        }
    }
}

// Действия со списком Пользователей
int ListUsers::Actions(std::vector<std::string> &user) {
    std::cout << "\nPlease select an item:\n"
    << "0. Back\n" << "1. Deleted a user\n" << ">> ";
    int des;
    std::cin >> des;
    switch (des) {
        case 0:
            return 0;
        case 1: {
            std::cout << "\nSelect the user number: ";
            int num;
            std::cin >> num;
            while (num > user.size() || num < 1) {
                std::cout << "\nThere is no user under this number\nSelect the request number: ";
                std::cin >> num;
            }

            std::string command {"rm " + user[num - 1]};
            system(command.data());

            user.erase(user.begin() + (num-1));

            return 1; // Удаление
        }
    }
}

// Список запросов на регистрацию
int ListRequest::Choice() {
    // Подготовка списка
    std::vector<std::string> requests_users;
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator("/home/user/Projects/C++/Client-Server/database/requests/");

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

        //Actions(requests_users);
    }
    if (requests_users.size() == 0) {
        std::cout << "\nThe list of registration requests is empty" << std::endl;
        return 0;
    }
    return 0;
}

// Список Пользователей
int ListUsers::Choice() {
    // Подготовка списка
    std::vector<std::string> list_users;
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator("/home/user/Projects/C++/Client-Server/database/users/");

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

int main() {
    int adm_choice {-1};
    while (adm_choice != 0) {
        std::cout << "\nPlease, select the appropriate item from the list below:\n"
        << "0. Turn off the Server\n" << "1. Turn on the Server\n" << "2. Display a list of registration requests\n"
        << "3. Display the list of users\n" << ">> ";
        std::cin >> adm_choice;
        if (const auto choice_main = MenuFactory::ChoiceFact(adm_choice)) {
            choice_main->Choice();
        }
    }

    return 0;
}


