#include <fstream>
#include <unordered_set>
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
    auto curr_path = std::filesystem::path("/home/user/Projects/C++/Client-Server/cmake-build-debug");

    curr_path /= sub_path;
    if (!exists(curr_path)) {
        std::filesystem::create_directories(curr_path);
    }

    return curr_path;
}

/*******************************************************************************************************************************************/

// TODO (Viktor): Добавить деструктор для unique (decltype) Прочитать про это в книжке "42 совета ..."

// Поиск наименования жесткого диска в системе
    std::string findDeviceHardDisk () {

    std::ifstream pathHardDisk ("/proc/mounts");
    if (!pathHardDisk.is_open()) std::cerr << "[ERROR] File not open" << std::endl;

    MountEntry hardDisk;

    while (!pathHardDisk.eof()) {
        pathHardDisk >> hardDisk;
        const std::unordered_set<std::string> kFsTypesSet{"ext2", "ext3", "ext4"};
        for (auto it : kFsTypesSet) {
            if (hardDisk.GetFsType() == it) {
                return hardDisk.GetDevice();
            }
        }
    }
}

    std::string SerialHardDdrive () {
    char c_serial[20];

    const std::string strPathHardDisk = "udevadm info --query=all --name=" + findDeviceHardDisk() + " | grep ID_SERIAL_SHORT";
    std::unique_ptr<FILE, decltype(&pclose)> fp (popen(strPathHardDisk.data(), "r"), pclose);

    if (fp == nullptr) std::cerr << "[ERROR] File not open" << std::endl;

    while (fgets(c_serial, sizeof(c_serial), fp.get()) != nullptr) {} // Почему-то не работает, если я вместо с_serial пишу str.data() (заранее созданный)

    // TODO (Viktor): нет проверки работы fgets()

    std::string s_serial{std::string(c_serial)}; //22413C462705

    return s_serial;
}

/*********************************************************************************************************************************************/

    std::string Nickname() {
    std::cout << "Enter your nickname: ";
    std::string nicknmae{};
    std::cin >> nicknmae;

    return nicknmae;
}

/*********************************************************************************************************************************************/
