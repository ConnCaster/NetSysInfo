#include "s_factory.h"
#include "utils.h"

#include "sql_database/builders/create_build.h"
#include "sql_database/builders/insert_builder.h"
#include "sql_database/directors/create_director.h"
#include "sql_database/directors/insert_director.h"

#include "SQLiteCpp/Database.h"
#include "file_database/file_database.h"


using json = nlohmann::json;

std::map<std::string, std::string> Registration::json_to_map(nlohmann::json &j_auth) {
    std::string serial_hard_disk = j_auth["auth"]["serial_hard_disk"];
    serial_hard_disk.back() = ' ';
    std::map<std::string, std::string> auth_values;
    auth_values["Hard disk serial number"] = serial_hard_disk;
    return auth_values;
}


bool Registration::execute(json &j_cli_json) {
    std::string check = j_cli_json.dump();

    auto root_path_users = CreateRootDir("database/users/");
    std::filesystem::path check_user{root_path_users.string() + std::string(j_cli_json["auth"]["username"]) + ".db3"};

    if (!std::filesystem::exists(check_user)) {
        auto root_path_requests= CreateRootDir("database/requests/");
        std::filesystem::path new_user_request{root_path_requests.string() + std::string(j_cli_json["auth"]["username"]) + ".db3"};

        const auto db_user = std::make_shared<SQLite::Database> (new_user_request, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

        CreateBuilder create_builder;
        CreateDirector create_director (create_builder);
        create_director.CreateSqliteRequest(users_data_, columns_name_, columns_values_);
        db_user->exec(create_builder.GetRequest()->GetRequestPlainText());

        InsertBuilder insert_builder;
        InsertDirector insert_director(insert_builder);
        columns_values_ = json_to_map(j_cli_json);
        for (const auto& element : columns_values_) {
            insert_director.CreateSqliteRequest(users_data_,columns_name_, element);
            db_user->exec(insert_builder.GetRequest()->GetRequestPlainText());
        }
        return true;
    } else {
        return false;
    }
}
