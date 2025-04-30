#ifndef LOGER_H
#define LOGER_H

#include <fstream>
#include <utils.h>

static auto path_log = CreateRootDir("log/");

class Log {
private:
std::fstream log_;

public:
    explicit Log(std::string name_log);

    std::fstream Get_log() {
        return std::move(log_);
    }

    ~Log() {
        log_.close();
    }
};


#endif //LOGER_H
