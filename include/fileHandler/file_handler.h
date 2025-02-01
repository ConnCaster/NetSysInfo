#pragma once
#include <fstream>
#include <nlohmann/json.hpp>


class IDataBase  {
public:
    virtual ~IDataBase() = default;

    virtual void write(const nlohmann::json &content) = 0;
    virtual void read(nlohmann::json &content) = 0;
};

class FileDB final : public IDataBase {
private:
    std::fstream db_file_;
    int is_open_;
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
