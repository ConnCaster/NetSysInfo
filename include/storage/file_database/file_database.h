#ifndef FILE_DATABASE_H
#define FILE_DATABASE_H

#include <fstream>

#include "logger.h"
#include "nlohmann/json.hpp"

class FileDB {
private:
    Log db_log_;
    std::fstream db_file_;
public:
    explicit FileDB(const std::string &path);

    inline void write(const nlohmann::json& content) {
        db_file_ << content;
    }

    inline void read(nlohmann::json& content) {
        db_file_ >> content;
    }

    ~FileDB() {
        db_file_.close();
    };
};



#endif //FILE_DATABASE_H
