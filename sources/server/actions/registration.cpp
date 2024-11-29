#include "factory.h"
#include "server.h"

    // TODO (Viktor): Относительный путь

bool Registration::execute(nlohmann::json &cli_json) {
    auto auto_serial = cli_json["args"]["serial"];


    std::filesystem::path path{"/home/user/Projects/C++/Client-Server/database/" + std::string(auto_serial) + ".json"};
    if (!std::filesystem::exists(path)) {
        FileDB file_db(path);
        file_db.write(cli_json);
        return true;
    } else {
        return false;
    }
}
