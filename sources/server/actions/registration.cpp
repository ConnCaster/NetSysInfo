#include "factory.h"
#include "server.h"

    // TODO (Viktor): Относительный путь

bool Registration::execute(nlohmann::json &cli_json) {

    std::filesystem::path checkUser{"/home/user/Projects/C++/Client-Server/database/users/" + std::string(cli_json["args"]["name"]) + ".json"};
    if (!std::filesystem::exists(checkUser)) {
        std::filesystem::path newUserRequest{"/home/user/Projects/C++/Client-Server/database/requests/" + std::string(cli_json["args"]["name"]) + ".json"};
        FileDB file_db(newUserRequest);
        file_db.write(cli_json);
        return true;
    } else {
        return false;
    }
}
