#include <fstream>
#include <iostream>
#include <unordered_set>

#include "c_factory.h"

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

// Поиск наименования жесткого диска в системе
std::string findDeviceHardDisk () {

        std::ifstream path_hard_disk ("/proc/mounts");
        if (!path_hard_disk.is_open()) std::cerr << "[ERROR] File not open" << std::endl;

        MountEntry hard_disk;

        while (!path_hard_disk.eof()) {
            path_hard_disk >> hard_disk;
            const std::unordered_set<std::string> kFsTypesSet{"ext2", "ext3", "ext4"};
            for (auto it : kFsTypesSet) {
                if (hard_disk.GetFsType() == it) {
                    return hard_disk.GetDevice();
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

std::string Nickname() {
        std::cout << "Enter your nickname: ";
        std::string nicknmae{};
        std::cin >> nicknmae;

        return nicknmae;
    }

json Authentication::execute() {
    json j_auth;
    j_auth["auth"] = { {"username", Nickname()}, {"serial_hard_disk", SerialHardDdrive()} };
    return j_auth;
}
