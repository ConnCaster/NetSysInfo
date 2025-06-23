#include "../../../include/storage/file_database/file_database.h"

FileDB::FileDB(const std::string &path)
    : db_log_("database"), db_file_{path, std::ios::out | std::ios::in | std::ios::app} {

    if (!db_file_.is_open()) {
        db_log_.Get_log() << Time() <<  "[File DataBase] Can't open database" << std::endl;
    } else {
        db_log_.Get_log() << Time() <<  "[File DataBase] Opened database successfully" << std::endl;
    }
}