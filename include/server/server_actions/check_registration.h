#pragma once
#include "nlohmann/json.hpp"

using json = nlohmann::json;

class CheckRegistration {
private:
    json j_cli_auth_;
public:
    explicit CheckRegistration(json &j_cli_auth)
        :j_cli_auth_(j_cli_auth) {}

    bool IfRegistration();
};