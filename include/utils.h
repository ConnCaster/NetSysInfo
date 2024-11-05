#pragma once

#include <iostream>

inline std::string Time(const time_t now = time(nullptr)) {
    const tm *ltm {localtime(&now)};
    return "[" + std::to_string(ltm->tm_mday) + ":" + std::to_string(ltm->tm_mon) + ":" + std::to_string(1900 + ltm->tm_year) +
        " " + std::to_string(ltm->tm_hour) + ":" + std::to_string(ltm->tm_min) + ":" + std::to_string(ltm->tm_sec) + "] ";
}
