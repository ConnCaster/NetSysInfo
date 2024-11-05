#pragma once
#include <iostream>
#include <filesystem>

class UserManager {
private:
    std::string m_path;
public:
    explicit UserManager(const std::string& path)
    :m_path(path) {}

    int Register() {
        return IsRegistered();
    }

private:
     bool IsRegistered() const {
        return std::filesystem::exists(m_path);
     }
};