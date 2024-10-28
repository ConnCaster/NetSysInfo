#pragma once
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include "user_manager.h"

class IDataBase  {
public:
    virtual ~IDataBase() = default;

    virtual void write(const nlohmann::json &content) = 0;
    virtual void read(nlohmann::json &content) = 0;
};

class FileDB final : public IDataBase {
private:
    std::fstream db_file;
public:
    explicit FileDB(const std::string &serial) {
        std::string path{"/home/user/Projects/C++/Client-Server/database/"};
        path += serial + ".json";

        if(const UserManager manager(path); manager.Register()) {
            db_file.open(path, std::ios::out | std::ios::in | std::ios::app);
        }
    }

    void write(const nlohmann::json& content) override {
        db_file << content;
    }

    void read(nlohmann::json& content) override {
        db_file >> content;
    }

    ~FileDB() override {
        db_file.close();
    };
};
