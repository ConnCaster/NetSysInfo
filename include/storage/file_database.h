#ifndef FILE_DATABASE_H
#define FILE_DATABASE_H

#include <fstream>

#include "itf_database.h"
#include "logger.h"



class FileDB  : public IDataBase {
private:
    Log db_log_;
    std::fstream db_file_;
public:
    explicit FileDB(const std::string &path);

    inline void write(const json& content) override {
        db_file_ << content;
    }

    inline void read(json& content) override {
        db_file_ >> content;
    }

    ~FileDB() override {
        db_file_.close();
    };
};



#endif //FILE_DATABASE_H
