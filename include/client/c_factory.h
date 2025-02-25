#pragma once
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Action {
public:
    virtual json execute() = 0;
    virtual ~Action() = default;
};

class Authentication : public Action {
public:
    json execute() override;
};

class MemberInfo  : public Action {
public:
    json execute() override;
};

class ActionFactory {
public:
    static std::unique_ptr<Action> ActionFact(const int& id_cmd) {
        switch (id_cmd) {
            case 1:
                return std::make_unique<Authentication>();
            case 2:
                return std::make_unique<MemberInfo>();
        }
    }
};