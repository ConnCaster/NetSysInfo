#pragma once
#include "server.h"

class Action {
public:
    virtual bool execute(nlohmann::json& j) = 0;
    virtual ~Action() = default;
};

class Registration : public Action {
public:
    bool execute(nlohmann::json& j) override;
};

class ActionFactory {
public:
    static auto ActionFact(const std::string &action) {
        if (action == "authUser") {
            return std::unique_ptr<Action>(new Registration());
        }
    }
};