#pragma once

#include "nlohmann/json.hpp"


class Action {
public:
    virtual void execute(nlohmann::json& j) = 0;
    virtual ~Action() = default;
};
