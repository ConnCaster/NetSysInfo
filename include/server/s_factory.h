#pragma once

#include "nlohmann/json.hpp"


class Action {
public:
    virtual bool execute(nlohmann::json& j) = 0;
    virtual ~Action() = default;
};

class Registration : public Action {
public:
    bool execute(nlohmann::json& j) override;
    std::map<std::string, std::string> json_to_map(nlohmann::json& j);
private:
     const std::string users_data_ {"users_data"};
     const std::vector<std::string> columns_name_ {"Value", "Name attribute"};
     std::map<std::string, std::string> columns_values_;
};

class MemberInfo  : public Action {
public:
    bool execute(nlohmann::json& j) override;
};

class CreateAction {
public:
    static std::unique_ptr<Action> CreateAct(const int& id_cmd) {
        switch (id_cmd) {
            case 1:
                return std::make_unique<Registration>();
            case 2:
                return std::make_unique<MemberInfo>();
        }
    }
};