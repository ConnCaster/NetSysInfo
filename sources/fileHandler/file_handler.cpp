#include "file_handler.h"

FileDB::FileDB(const std::string &path)
    : is_open_{true}, db_file_{path, std::ios::out | std::ios::in | std::ios::app}
{}