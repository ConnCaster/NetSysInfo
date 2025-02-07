#include "factory.h"
#include "file_handler.h"
#include "utils.h"

bool Registration::execute(nlohmann::json &cli_json) {
    auto root_path_users = CreateRootDir("../../../database/users/");
    std::filesystem::path check_user{root_path_users.string() + std::string(cli_json["args"]["name"]) + ".json"};

    if (!std::filesystem::exists(check_user)) {
        auto root_path_requests= CreateRootDir("../../../database/requests/");
        std::filesystem::path new_user_request{root_path_requests.string() + std::string(cli_json["args"]["name"]) + ".json"};
        FileDB file_db(new_user_request);
        file_db.write(cli_json);
        return true;
    } else {
        return false;
    }
}
