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
    int m_flag_check;
public:
    explicit FileDB(const std::string &serial) {
        std::string path{"/home/user/Projects/C++/Client-Server/database/"};
        path += serial + ".json";

        if(const UserManager manager(path); manager.Register()) {
            db_file.open(path, std::ios::out | std::ios::in | std::ios::app);
            m_flag_check = 1;
        } else {
            m_flag_check = 0;
        }
    }

    void write(const nlohmann::json& content) override {
        db_file << content;
    }

    void read(nlohmann::json& content) override {
        db_file >> content;
    }

    std::string check() const {
        if(m_flag_check) {
            return  "[Server] The user has been successfully registered";
        } else {
            return "[WARNING] The user is already registered";
        }
    }

    ~FileDB() override {
        db_file.close();
    };
};
