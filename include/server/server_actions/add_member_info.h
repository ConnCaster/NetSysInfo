#pragma once

#include "s_factory.h"
#include "nlohmann/json_fwd.hpp"

constexpr std::string_view name() { return "add_member_info"; }

class MemberInfo  : public Action {
public:
    void execute(nlohmann::json& j) override;
    std::map<std::string, int> json_to_map(nlohmann::json& j);
private:
    const std::string users_data_ {"users_data"};
    const std::vector<std::string> columns_name_ {"Value", "Name attribute"};
    const std::map<std::string, std::string> columns_values_;
};
