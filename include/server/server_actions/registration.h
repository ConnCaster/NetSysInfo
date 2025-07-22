#ifndef REGISTRATION_H
#define REGISTRATION_H

#include "s_factory.h"


class Registration : public Action {
public:
    void execute(nlohmann::json& j) override;
    std::map<std::string, std::string> json_to_map(nlohmann::json& j);
private:
    const std::string users_data_ {"users_data"};
    const std::vector<std::string> columns_name_ {"Value", "Name attribute"};
    std::map<std::string, std::string> columns_values_;
};


#endif //REGISTRATION_H
