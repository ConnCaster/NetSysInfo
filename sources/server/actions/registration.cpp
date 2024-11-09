#include "factory.h"
#include "server.h"
#include "serv_connection.h"

    // TODO (Viktor): Относительный путь

bool Registration::execute(nlohmann::json &cli_json) {
    std::filesystem::path path{"/home/user/Projects/C++/Client-Server/database/" + cli_json["args"]["serial"].get<std::string>() + ".json"};
    if (!std::filesystem::exists(path)) {
        FileDB file_db(path);
        file_db.write(cli_json);
        return true;
    } else {
        return false;
    }
}
