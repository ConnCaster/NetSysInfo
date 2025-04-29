#pragma once
#include <fstream>
#include <nlohmann/json.hpp>

#include "../log/loger.h"
#include "SQLiteCpp/Database.h"

using json = nlohmann::json;
constexpr int kFirstRowInTheTable {0};

class IDataBase  {
public:
    virtual ~IDataBase() = default;
    virtual void write(const nlohmann::json &content) = 0;
    virtual void read(nlohmann::json &content) = 0;
};

class FileDB  : public IDataBase {
private:
    Log db_log_;
    std::fstream db_file_;
public:
    explicit FileDB(const std::string &path);

    inline void write(const nlohmann::json& content) override {
        db_file_ << content;
    }

    inline void read(nlohmann::json& content) override {
        db_file_ >> content;
    }

    ~FileDB() override {
        db_file_.close();
    };
};

class SQliteDB  : public IDataBase {
private:
    SQLite::Database db_file_;
    Log db_log_;
    std::string created_table_ {"CREATE TABLE IF NOT EXISTS command_queue('Name of the command' TEXT, 'ID command' TEXT)"};
    std::string *err_msg_;

public:
    explicit SQliteDB(const std::string &path);

    inline void write(const nlohmann::json& content) override;

    inline void read(nlohmann::json& content) override;

    int check_occupancy_table();


    ~SQliteDB() override {
        remove("db_file_");
    };
};
