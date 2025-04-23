#pragma once
#include <fstream>
#include <sqlite3.h>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class IDataBase  {
public:
    virtual ~IDataBase() = default;
    virtual void write(const nlohmann::json &content) = 0;
    virtual void read(nlohmann::json &content) = 0;
};

class FileDB  : public IDataBase {
private:
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
    std::string created_table_ {"CREATE TABLE IF NOT EXISTS command_queue('Name of the command' TEXT, 'ID command' INT)"};
    char* errMsg_;
    sqlite3 *db_file_;
    int is_open_;
public:
    explicit SQliteDB(const std::string &path);

    inline void write(const nlohmann::json& content) override;

    inline void read(nlohmann::json& content) override;

    sqlite3* GetDB() {
        return db_file_;
    }

    ~SQliteDB() override {
        sqlite3_close(db_file_);
    };
};
