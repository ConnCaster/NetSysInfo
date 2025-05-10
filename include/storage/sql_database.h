#ifndef SQL_DATABASE_H
#define SQL_DATABASE_H

#include "itf_database.h"
#include "logger.h"
#include "SQLiteCpp/Database.h"

constexpr int kFirstRowInTheTable {0};

class SQliteDB  : public IDataBase {
private:
    SQLite::Database db_file_;
    Log db_log_;
    std::string created_table_ {"CREATE TABLE IF NOT EXISTS command_queue('Name of the command' TEXT, 'ID command' TEXT)"};
    std::string *err_msg_;

public:
    explicit SQliteDB(const std::string &path);

    inline void write(const json& content) override;

    inline void read(json& content) override;

    int check_occupancy_table();


    ~SQliteDB() override {
        remove("db_file_");
    };
};

#endif //SQL_DATABASE_H
