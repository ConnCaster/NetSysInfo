#include "menu.h"


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


