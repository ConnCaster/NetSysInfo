#include "add_member_info.h"
#include "file_database/file_database.h"
#include "utils.h"

#include "../../SQLiteCpp/include/SQLiteCpp/Database.h"
#include "sql_database/builders/create_build.h"
#include "sql_database/builders/insert_builder.h"
#include "sql_database/directors/create_director.h"
#include "sql_database/directors/insert_director.h"

using json = nlohmann::json;

std::pair<std::string, int> MemberInfo::json_to_map(nlohmann::json &j_auth) {
    std::pair<std::string, int> member_values("The amount of RAM", j_auth["data"]["response"].get<int>());
    return member_values;
}


void MemberInfo::execute(json &j_cli_json) {
    std::string check = j_cli_json.dump();

    auto root_path_users = CreateRootDir("database/users/");
    root_path_users += std::string(j_cli_json["auth"]["username"]) + ".db3";


    const auto db_user = std::make_shared<SQLite::Database> (root_path_users, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

    CreateBuilder create_builder;
    CreateDirector create_director (create_builder);
    create_director.CreateSqliteRequest(users_data_, columns_name_, columns_values_);
    db_user->exec(create_builder.GetRequest()->GetRequestPlainText());

    InsertBuilder insert_builder;
    InsertDirector insert_director(insert_builder);
    columns_values_ = json_to_map(j_cli_json);
        insert_director.CreateSqliteRequest(users_data_,columns_name_, element);
        db_user->exec(insert_builder.GetRequest()->GetRequestPlainText());
}
