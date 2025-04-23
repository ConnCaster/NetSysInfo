#include <fstream>
#include <iostream>

#include "utils.h"


// Для вывода текущего времени
std::string Time(const std::time_t now) {
    const tm *ltm {localtime(&now)};
    return "[" + std::to_string(ltm->tm_mday) + ":" + std::to_string(ltm->tm_mon) + ":" + std::to_string(1900 + ltm->tm_year) +
        " " + std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec) + "] ";
}

/*********************************************************************************************************************************************/

// Для корректировки имени
std::string ExtractionNameJson (const std::string& path) {
    int sizeName = path.size() - (path.find_last_of("/") + (path.size() - path.find(".json") + 1));

    return path.substr(path.find_last_of("/") + 1,sizeName);
}

std::string ExtractionNameDB(const std::string& path) {
    int sizeName = path.size() - (path.find_last_of("/") + (path.size() - path.find(".json") + 1));

    std::string created_db =  path.substr(path.find_last_of("/") + 1,sizeName) + ".db";

    return created_db;
}
/*********************************************************************************************************************************************/

// TODO: sub_path = "database/request/" -> "/home/user/dir/database/request/"

std::filesystem::path CreateRootDir(const std::string& sub_path) {
    auto curr_path = std::filesystem::path("/home/user/Projects/C++/Client-Server/cmake-build-debug");

    curr_path /= sub_path;
    if (!exists(curr_path)) {
        std::filesystem::create_directories(curr_path);
    }
    return curr_path;
}

/*******************************************************************************************************************************************/

// TODO (Viktor): Добавить деструктор для unique (decltype) Прочитать про это в книжке "42 совета ..."


/*********************************************************************************************************************************************/
