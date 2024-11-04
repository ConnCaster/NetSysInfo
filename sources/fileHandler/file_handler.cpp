#include "file_handler.h"

FileDB::FileDB(const std::string &serial) {
    std::filesystem::path path{"/home/user/Projects/C++/Client-Server/database/"};
    path += serial + ".json";

    if(const UserManager manager(path); manager.Register()) {
        db_file_.open(path, std::ios::out | std::ios::in | std::ios::app);
        flag_ = 1;
    } else {
        flag_ = 0;
    }
}