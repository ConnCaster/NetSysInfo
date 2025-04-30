#include "logger.h"

Log::Log(std::string name_log)
    : log_(path_log.string() + name_log + ".txt", std::ios::in | std::ios::out | std::ios::app){}