#include "action.h"

void Registration::execute(nlohmann::json &j) {
    {
        FileDB file_db(j["args"]["serial"].get<std::string>());
        file_db.write(j["args"]);
    }
}
