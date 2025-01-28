#include "utils.h"
#include <iostream>

// Для вывода текущего времени
std::string Time(const std::time_t now) {
    const tm *ltm {localtime(&now)};
    return "[" + std::to_string(ltm->tm_mday) + ":" + std::to_string(ltm->tm_mon) + ":" + std::to_string(1900 + ltm->tm_year) +
        " " + std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec) + "] ";
}

/*********************************************************************************************************************************************/

// Для корректировки имени
std::string ExtractionName (const std::string& path) {
    int sizeName = path.size() - (path.find_last_of("/") + (path.size() - path.find(".json") + 1));

    return path.substr(path.find_last_of("/") + 1,sizeName);
}

/*********************************************************************************************************************************************/

// TODO: sub_path = "database/request/" -> "/home/user/dir/database/request/"
/*
 * Формирует путь к директории путем склеивания пути к директории, в которой запущено cli-приложение
 * и пути, переданного аргументом
 * Пример:
 *          "database/request/" -> "/home/user/dir/database/request/"
 */
std::filesystem::path CreateRootDir(const std::string& sub_path) {
    auto curr_path = std::filesystem::current_path();
    curr_path /= sub_path;
    if (!exists(curr_path)) {
        std::filesystem::create_directories(curr_path);
    }
    return curr_path;
}