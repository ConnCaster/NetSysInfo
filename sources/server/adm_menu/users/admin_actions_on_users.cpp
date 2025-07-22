#include <algorithm>

#include "adm_menu/menu.h"
#include "utils.h"
#include "nlohmann/json.hpp"

#include "sql_database/builders/create_build.h"
#include "sql_database/builders/insert_builder.h"
#include "sql_database/builders/drop_builder.h"

#include "sql_database/directors/insert_director.h"
#include "sql_database/directors/create_director.h"
#include "sql_database/directors/drop_director.h"

int ListUsers::RequestChoice() {
    int id_cmd;
    std::cout << "\nChoose the information you are interested in from the suggested options:\n" <<
        "1. The user's name and serial number of his hard drive;\n" <<
        "2. The amount of user RAM\n" << ">> ";
    std::cin >> id_cmd;
    while (id_cmd < id_cmd_min_ || id_cmd > id_cmd_max_) {
        std::cout << "\nThere is no such item, please select an item from the suggested options\n" << ">> ";
        std::cin >> id_cmd;
    }
    return id_cmd;
}

std::string ListUsers::ReturnNameCmd (const int id_cmd) {
    switch (id_cmd) {
        case 1:
            return "The users name and serial number of his hard drive";
        case 2:
            return "The amount of user RAM";
    }
}

int ListUsers::UserChoice() {
    if (list_users_.size() == 0) {
        std::cout << "\nThe list of registration users is empty" << std::endl;
        return 0;
    }
    std::cout << "\nSelect the user number: ";
    int num_user;
    std::cin >> num_user;
    while (num_user > list_users_.size() || num_user < 1) {
        std::cout << "\nThere is no user under this number\nSelect the request number: ";
        std::cin >> num_user;
    }
    return num_user;
}

int ListUsers::ActionChoise() {
    std::cout << "\nPlease select an item:\n"
    << "0. Back\n" << "1. Deleted this user\n" << "2. Send a request to the client for information\n" << ">> ";
    int decision;
    std::cin >> decision;
    while (decision > 2 || decision < -1) {
        std::cout << "\nYou have chosen an inappropriate action.: ";
        std::cin >> decision;
    }
    return decision;
}

// Действия со списком Пользователей
int ListUsers::Actions() {
    const int num_user = UserChoice();
    const std::string name_user {list_users_[num_user - 1]};
    auto root_path_users_db = CreateRootDir("database/users/");
    root_path_users_db += ExtractionNameDB(name_user) + ".db3";

    try {
        const auto db_user = std::make_shared<SQLite::Database> (root_path_users_db, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

        int decision = ActionChoise();

        switch (decision) {
            case 0:
                return 0; // Назад
            case 1: {
                std::string command {"rm " + list_users_[num_user - 1]};
                system(command.data());


                auto new_end = std::remove(list_users_.begin(), list_users_.end(), list_users_[num_user - 1]);
                list_users_.erase(new_end, list_users_.end());

                DropBuilder drop_builder;
                DropDirector drop_director(drop_builder);
                drop_director.CreateSqliteRequest(kCmdTable);
                db_user->exec(drop_builder.GetRequest()->GetRequestPlainText());

                return 1; // Удаление
            }
            case 2: {
                CreateBuilder create_builder;
                CreateDirector create_director (create_builder);
                create_director.CreateSqliteRequest(kCmdTable, list_names_columns_, list_types_columns);
                db_user->exec(create_builder.GetRequest()->GetRequestPlainText());

                // Выбираем нужную команду
                int number_cmd = RequestChoice();
                std::string key_name_cmd = ReturnNameCmd(number_cmd);
                std::pair<std::string, int> columns_values {key_name_cmd, number_cmd};
                // И отправляем ее в БД
                InsertBuilder insert_builder;
                InsertDirector insert_director(insert_builder);
                insert_director.CreateSqliteRequest(kCmdTable, list_names_columns_, columns_values);
                db_user->exec(insert_builder.GetRequest()->GetRequestPlainText());

                return 2; // Добавление запроса для пользователя
            }
        }
    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}