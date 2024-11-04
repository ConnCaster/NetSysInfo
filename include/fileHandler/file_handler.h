#pragma once
#include <fstream>
#include <nlohmann/json.hpp>
#include <filesystem>
#include "user_manager.h"
#include "server.h"


class IDataBase  {
public:
    virtual ~IDataBase() = default;

    virtual void write(const nlohmann::json &content) = 0;
    virtual void read(nlohmann::json &content) = 0;
};

class FileDB final : public IDataBase {
private:
    std::fstream db_file_;
    int flag_;
public:
    explicit FileDB(const std::string &serial);

    void write(const nlohmann::json& content) override {
        db_file_ << content;
    }

    void read(nlohmann::json& content) override {
        db_file_ >> content;
    }

    int Get_flag_() {
        return flag_;
    }

    ~FileDB() override {
        db_file_.close();
    };
};
