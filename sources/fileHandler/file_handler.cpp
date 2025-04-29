#include <utils.h>

#include "file_handler.h"


FileDB::FileDB(const std::string &path)
    : db_log_("database"), db_file_{path, std::ios::out | std::ios::in | std::ios::app} {

    if (!db_file_.is_open()) {
        db_log_.Get_log() << Time() <<  "[File DataBase] Can't open database" << std::endl;
    } else {
        db_log_.Get_log() << Time() <<  "[File DataBase] Opened database successfully" << std::endl;
    }
}

SQliteDB::SQliteDB(const std::string &path)
    : db_file_(path.data(),  SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE), db_log_("database") {
    try {
        db_file_.exec(created_table_);
    } catch (std::exception &err_msg_) {
        db_log_.Get_log() << Time << " [Creatingtabl] "<< "SQLite exception: " << err_msg_.what() << std::endl;
    }
}

void SQliteDB::write(const nlohmann::json &content) {

    std::string name_cmd_str = content["name_cmd"];
    std::string id_cmd_str = content["id_cmd"].dump();

    try {
        db_file_.exec("INSERT INTO command_queue VALUES ('" + name_cmd_str + "','" + id_cmd_str + "')");
    } catch (std::exception &err_msg_) {
        db_log_.Get_log() << Time << " [Writing] " << "SQLite exception: " << err_msg_.what() << std::endl;
    }
}

void SQliteDB::read(nlohmann::json &content) {
    try {

        SQLite::Statement query(db_file_, "SELECT \"ID command\" FROM command_queue");
        query.executeStep();
        content["id_cmd"] = query.getColumn(first_row_in_the_table);

    }  catch (std::exception &err_msg_) {
        db_log_.Get_log() << Time << " [Reading] " << "SQLite exception: " << err_msg_.what() << std::endl;
    }
}

int SQliteDB::check_occupancy_table() {
    try {

        SQLite::Statement query(db_file_, "SELECT COUNT(*) FROM command_queue");
        query.executeStep();
        int res = query.getColumn(kFirstRowInTheTable);
        return res;

    }   catch (std::exception &err_msg_) {
        db_log_.Get_log() << Time << " [Reading] " << "SQLite exception: " << err_msg_.what() << std::endl;
    }
}

