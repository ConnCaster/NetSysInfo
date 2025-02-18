#include "factory.h"
#include "file_handler.h"
#include "utils.h"

using json = nlohmann::json;


bool MemberInfo::execute(json &j_cli_json) {
    auto member_size = j_cli_json["response"].get<unsigned int>();
    while (member_size / 1000000) {
        member_size /= 1000000;
    }
    auto root_path_users = CreateRootDir("database/users/");
    std::filesystem::path user{root_path_users.string() + std::string(j_cli_json["auth"]["username"]) + ".json"};

    json j_input_data;
    j_input_data["member"] = j_cli_json["response"].get<std::string>();

    FileDB file_db(user);
    file_db.write(j_input_data);
    return true;
}
