#include "action.h"
#include "server.h"
#include "connection.h"

bool Registration::execute(nlohmann::json &j) {
    const std::string arg = j["args"]["serial"].get<std::string>();
        FileDB file_db(arg);

        if (file_db.Get_flag_() == 1) {
            file_db.write(j["args"]);
            return true;
        } else {
            return false;
        }

}
