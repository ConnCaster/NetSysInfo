#include "s_factory.h"
#include "file_database/file_database.h"
#include "utils.h"


bool MemberInfo::execute(nlohmann::json &j_cli_json) {
    auto root_path_users = CreateRootDir("database/users/");
    std::filesystem::path user{root_path_users.string() + std::string(j_cli_json["auth"]["username"]) + ".json"};

    nlohmann::json j_input_data = nlohmann::json::object();

    j_input_data["member"] = j_cli_json["data"].begin().value().back();

    FileDB file_db(user);
    file_db.write(j_input_data);
    return true;
}
