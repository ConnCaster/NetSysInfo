#pragma once

#include <iostream>
#include <unordered_set>
#include <filesystem>

// Для вывода текущего времени
inline std::string Time(const time_t now = time(nullptr)) {
    const tm *ltm {localtime(&now)};
    return "[" + std::to_string(ltm->tm_mday) + ":" + std::to_string(ltm->tm_mon) + ":" + std::to_string(1900 + ltm->tm_year) +
        " " + std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec) + "] ";
}

// Для корректировки имени
inline std::string ExtractionName (const std::string& path) {
    int sizeName = path.size() - (path.find_last_of("/") + (path.size() - path.find(".json") + 1));

    return path.substr(path.find_last_of("/") + 1,sizeName);
}

// Для нахождени расположения ЖД
const std::unordered_set<std::string> kFsTypesSet{"ext2", "ext3", "ext4"};

class MountEntry {
public:
    MountEntry() = default;

    friend std::istream& operator>> (std::istream& in, MountEntry& obj);

    std::string GetFsType() const {
        return fs_type_;
    }

    std::string GetDevice() const {
        return device_;
    }

    std::string GetMountDev() const {
        return mount_dev_;
    }

private:
    std::string device_;
    std::string mount_dev_;
    std::string fs_type_;
    std::string options_;
    int flag1_;
    int flag2_;
};

inline std::istream &operator>>(std::istream &in, MountEntry& obj) {
    in >> obj.device_ >> obj.mount_dev_ >> obj.fs_type_ >> obj.options_ >> obj.flag1_ >> obj.flag2_;
    return in;
}

std::filesystem::path CreateRootDir(const std::string& sub_path);
