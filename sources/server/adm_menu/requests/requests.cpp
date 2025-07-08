#include <string>
#include <filesystem>

#include "menu.h"
#include "utils.h"

void ListRequest::PreparingTheList() {
    auto root_path_requests = CreateRootDir("database/requests/");
    std::filesystem::directory_iterator iterator = std::filesystem::directory_iterator(root_path_requests);

    for (; iterator != std::filesystem::end(iterator); iterator++) {
        list_requests_.push_back(iterator->path().string());
    }
}


void ListRequest::OutputTheList() {
    std::cout << "\nRequests:" << std::endl;
    for (int i = 0; i < list_requests_.size(); i++) {
        std::cout << i + 1 << ". " << ExtractionNameDB(list_requests_[i]) << std::endl;
    }
}


// Список запросов на регистрацию
int ListRequest::Execute() {
    PreparingTheList();
    OutputTheList();

    while (list_requests_.size() > 0 && Actions() != 0) {
        OutputTheList();
    }
    if (list_requests_.size() == 0) {
        std::cout << "\nThe list of registration requests is empty" << std::endl;
        return 0;
    }
    return 0;
}
