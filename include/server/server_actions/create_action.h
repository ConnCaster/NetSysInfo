#pragma once

#include "registration.h"
#include "add_member_info.h"

class CreateAction {
public:
    static std::unique_ptr<Action> CreateAct(const int& id_cmd) {
        switch (id_cmd) {
            case 0:
                return nullptr;
            case 1:
                return std::make_unique<Registration>();
            case 2:
                return std::make_unique<MemberInfo>();
        }
    }
};
