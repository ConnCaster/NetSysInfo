#pragma once
#include "server.h"

class Action {
public:
    virtual void execute(nlohmann::json& j) = 0;
    virtual ~Action() = default;
};

class Registration : public Action {
public:
    void execute(nlohmann::json& j) override;
};

class ActionFactory {
public:
    static Action* action_registr(const std::string& action) {
        if (action == "authUser") {
            return new Registration();
        }
        return nullptr;
    }
};