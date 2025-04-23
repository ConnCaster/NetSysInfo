#include <iostream>
#include <utils.h>

#include "file_handler.h"
#include "sqlite3.h"
#include "loger.h"

//TODO: Сделать класс ЛОГ и переделать на правильную инициализацию полей в конструкторе SQLite

FileDB::FileDB(const std::string &path)
    : db_file_{path, std::ios::out | std::ios::in | std::ios::app} {
    Log db_log ("database");

    if (!db_file_.is_open()) {
        db_log.Get_log() << Time() <<  "[File DataBase] Can't open database" << std::endl;
    } else {
        db_log.Get_log() << Time() <<  "[File DataBase] Opened database successfully" << std::endl;
    }
}

SQliteDB::SQliteDB(const std::string &path) {
    Log db_log ("database");

    is_open_ = sqlite3_open(path.data(), &db_file_);

    if( is_open_ ) {
        db_log.Get_log() << Time() <<  "[SQlite] Can't open database: " << sqlite3_errmsg(db_file_) << std::endl;
    } else {
        db_log.Get_log() << Time() <<  "[SQlite] Opened database successfully" << std::endl;
    }

    int rc = sqlite3_exec(db_file_, created_table_.c_str(), NULL, NULL, &errMsg_);
    if( rc != SQLITE_OK ){
        db_log.Get_log() << Time() << "[SQlite] " << errMsg_ << std::endl;
        sqlite3_free(errMsg_);
    } else {
        db_log.Get_log() << Time() << "[SQlite] Table created successfully" << std::endl;;
    }
}

void SQliteDB::write(const nlohmann::json &content) {
    Log db_log ("database");

    /*
    std::string name_cmd = content["name_cmd"];

    КАК ДОБАВЛЯТЬ ЦЕЛОЧИСЛЕННЫЕ ЗНАЧЕНИЯ В БД???
    std::string id_cmd_str = content["id_cmd"].dump();
    int id_cmd_int = std::stoi(id_cmd_str);
    */

    std::string insert_str = "INSERT INTO command_queue ('Name of the command', 'ID command') VALUES ('" +
    content["name_cmd"].dump() + "','" + content["id_cmd"].dump() + "');";

    int rc = sqlite3_exec(db_file_, insert_str.c_str(), NULL, 0, &errMsg_);
    if (rc != SQLITE_OK) {
        db_log.Get_log() << Time() << "[SQlite] Error Insert:" << errMsg_ << std::endl;
        sqlite3_free(errMsg_);
    }
    else {
        db_log.Get_log() << Time() << "[SQlite] Records created Successfully!" << std::endl;
    }
}

static int readCallback(void *outInt, int argc, char **argv, char **azColName) {
    // void *NotUsed - передается 4-й аргумент из sqlite3_exec
    // int argc - количество стобцов ?
    //char **argv - значение столбца ?
    // char **azColName - название столбца
        int* int_check = static_cast<int*>(outInt);
        *int_check = std::stoi(argv[1]);

    return 0;
}

void SQliteDB::read(nlohmann::json &content) {
    Log db_log ("database");

    std::string select_str = "SELECT * FROM command_queue";
    int outInt;

    int rc = sqlite3_exec(db_file_, select_str.c_str(), readCallback, &outInt, &errMsg_);
    if (rc != SQLITE_OK) {
        db_log.Get_log() << Time() << "[SQlite] Error Insert:" << errMsg_ << std::endl;
        sqlite3_free(errMsg_);
    }
    else {
        db_log.Get_log() << Time() << "[SQlite] Records created Successfully!" << std::endl;
    }

    content["id_cmd"] = outInt;

}
