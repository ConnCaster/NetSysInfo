#pragma once
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>

// Вопросы:
/*
* 1. Как записать в файл .json несколько экземпляров одной структуры
* Пример {
  "Person_1" : {
    "id" : "1",
    "name": "hhhh",
    "serial": "5454"
  },
  "Person_2": {
    "id" : "2",
    "name": "sasa",
    "serial": "as5454"
  }
}
 * 2. Как автоматически при записи в БД присваивать ID ?
 */

class IDataBase  {
public:
    virtual ~IDataBase() = default;

    virtual int write(const nlohmann::json &content) = 0;
    virtual int read(nlohmann::json* content) = 0;
};

class FileDB final : public IDataBase {
private:
    std::fstream bd_file;
public:
    FileDB(){}

    int write(const nlohmann::json &content) override {
        bd_file.open("/home/user/Projects/C++/Client-Server/Database.json", std::ios::app);
        if (bd_file.is_open()) {
            bd_file << content << std::endl;
        } else {
            std::cerr << "[ERROR] The database has not opened" << std::endl;
            return 0;
        }
        bd_file.close();
        return 1;
    }

    int read(nlohmann::json* content) override {
        bd_file.open("/home/user/Projects/C++/Client-Server/Database.json", std::ios::in);
        if (bd_file.is_open()) {
            bd_file >> *content;
        } else {
            std::cerr << "[ERROR] The database has not opened" << std::endl;
            return 0;
        }
        bd_file.close();
        return 1;
    }

    ~FileDB() override = default;
};
