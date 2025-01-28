#include "factory.h"
#include "server.h"

#include "utils.h"

    // TODO (Viktor): Относительный путь

bool Registration::execute(nlohmann::json &cli_json) {
    auto root_path_users = CreateRootDir("database/users/");
    auto root_path_requests= CreateRootDir("database/requests/");
    std::filesystem::path checkUser{root_path_users.string() + std::string(cli_json["args"]["name"]) + ".json"};
    if (!std::filesystem::exists(checkUser)) {
        std::filesystem::path newUserRequest{root_path_requests.string() + std::string(cli_json["args"]["name"]) + ".json"};
        FileDB file_db(newUserRequest);
        file_db.write(cli_json);
        return true;
    } else {
        return false;
    }
}
