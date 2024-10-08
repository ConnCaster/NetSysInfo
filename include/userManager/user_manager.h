#pragma once
#include <iostream>
#include <filesystem>

class UserManager {
private:
    std::string m_path;
public:
    explicit UserManager(const std::string& path)
    :m_path(path) {}

    int Register() const {
        if (IsRegistered(m_path)) {
            return 1;
        } else {
            return 0;
        }
    }

private:
    static bool IsRegistered(const std::filesystem::path& p, std::filesystem::file_status s = std::filesystem::file_status{}) {
        if(std::filesystem::status_known(s) ? std::filesystem::exists(s) : std::filesystem::exists(p)) {
            return false;
        } else {
            return true;
        }
    }
};