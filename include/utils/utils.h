#pragma once

#include <filesystem>


// Для вывода текущего времени
std::string Time(const std::time_t now = std::time(nullptr));

/*********************************************************************************************************************************************/

// Для корректировки имени
std::string ExtractionName (const std::string& path);

/*********************************************************************************************************************************************/

// Для получения данных о ЖД
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

/*********************************************************************************************************************************************/

// Для создания общего пути
std::filesystem::path CreateRootDir(const std::string& sub_path);

/*********************************************************************************************************************************************/

// Получение серийного номера жесткого диска
std::string SerialHardDdrive ();

/*********************************************************************************************************************************************/

// Для ввода никнейма
std::string Nickname();

/*********************************************************************************************************************************************/

