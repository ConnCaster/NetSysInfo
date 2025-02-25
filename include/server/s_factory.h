#pragma once
#include <nlohmann/json.hpp>


class Action {
public:
    virtual bool execute(nlohmann::json& j) = 0;
    virtual ~Action() = default;
};

class Registration : public Action {
public:
    bool execute(nlohmann::json& j) override;
};

class MemberInfo  : public Action {
public:
    bool execute(nlohmann::json& j) override;
};

class ActionFactory {
public:
    static std::unique_ptr<Action> ActionFact(const int& id_cmd) {
        switch (id_cmd) {
            case 1:
                return std::make_unique<Registration>();
            case 2:
                return std::make_unique<MemberInfo>();
        }
    }
};