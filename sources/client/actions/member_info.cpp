#include <fstream>
#include <iostream>
#include <unordered_set>

#include "c_factory.h"

using json = nlohmann::json;

// Для получения данных об объёме оперативной памяти
class MemberEntry {
public:
    MemberEntry() = default;

    friend std::istream& operator>> (std::istream& in, MemberEntry& obj);

    std::string GetKey() const {
        return key_;
    }

    int GetValue() const {
        return value_ / kb_to_Gb_;
    }


private:
    std::string key_;
    int value_;
    int kb_to_Gb_ {1000000};
};

inline std::istream &operator>>(std::istream &in, MemberEntry& obj) {
    in >> obj.key_ >> obj.value_;
    return in;
}

int findMemberInfo () {
    std::ifstream path_member ("/proc/meminfo");
    if (!path_member.is_open()) std::cerr << "[ERROR] File not open" << std::endl;

    MemberEntry member_size{};
    while (!path_member.eof()) {
        path_member >> member_size;
        const std::string kFsTypesSet{"MemTotal:"};
            if (member_size.GetKey() == kFsTypesSet) {
                return member_size.GetValue();
        }
    }
}

json MemberInfo::execute() {
    json j_mem;
    std::string str_member_size = std::to_string(findMemberInfo());
    j_mem["response"] = str_member_size;
    return j_mem;
}
