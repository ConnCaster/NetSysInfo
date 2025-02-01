#include "menu.h"

#include <thread>

std::mutex mtx;

void menu() {
    mtx.lock();
    int adm_choice {-1};
    while (adm_choice != 0) {
        std::cout << "\nPlease, select the appropriate item from the list below:\n"
        << "0. Turn off the Server\n" << "1. Turn on the Server\n" << "2. Display a list of registration requests\n"
        << "3. Display the list of users\n" << ">> ";
        std::cin >> adm_choice;
        if (const auto choice_main = MenuFactory::ChoiceFact(adm_choice)) {
            mtx.unlock();
            choice_main->Choice();
        }
    }
}


int main() {

    std::thread start (menu);
    std::thread menu_upravleniya (menu);

    menu_upravleniya.join();
    start.join();

    return 0;
}


