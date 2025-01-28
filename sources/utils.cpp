#include "../include/utils.h"

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