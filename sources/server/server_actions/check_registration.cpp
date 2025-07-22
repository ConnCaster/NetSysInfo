#include "check_registration.h"
#include "utils.h"


bool CheckRegistration::IfRegistration()  {
    std::string check = j_cli_auth_.dump();
    auto root_path_users = CreateRootDir("database/users/");
    std::filesystem::path check_user{root_path_users.string() + std::string(j_cli_auth_["auth"]["username"]) + ".db3"};
    if (std::filesystem::exists(check_user)) {
        return true;
    } else {
        return false;
    }
}