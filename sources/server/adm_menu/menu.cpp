#include "menu.h"
#include <string>
#include <filesystem>
#include <vector>


void TurnOFF::Choice() {;
}

void ListRequest::Choice() {
    // Подготовка списка
    std::string extension = ".txt";
    std::vector<std::string> files;
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator("/home/user/Projects/C++/Client-Server/database/requests/");

    for (; iterator != std::filesystem::end(iterator); iterator++) {
        if (iterator->path().extension() == extension)
        {
            files.push_back(iterator->path().string());
        }
    }
    // Вывод списка
    for (int i = 0; i < files.size(); i++) {
        files[i].replace(0, 56, "");
        size_t start {files[i].find(".txt")};
        files[i].replace(start, 4, "");
        std::cout << i + 1 << ". " << files[i] << std::endl;
    }
    Desicion();
    // Действия со списком
    std::cout << "Please select an item:\n"
    << "0. Exit\n" << "1. Register a request\n" << "2. Deleted a request" << std::endl;
}

int main() {
    std::cout << "Please, select the appropriate item from the list below:\n"
    << "0. Turn off the Server\n" << "1. Display a list of registration requests" << std::endl;
    int adm_choice;
    std::cin >> adm_choice;
    if (const auto choice_main = MenuFactory::ChoiceFact(adm_choice)) {
        choice_main->Choice();
    }
}


