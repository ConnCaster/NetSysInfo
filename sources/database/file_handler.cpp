#include <file_handler.h>

int main() {

    FileDB s;
    nlohmann::json j{};
    std::cout << s.read(&j) << std::endl;
    std::cout << j << std::endl;
    std::string ss = j.dump();
    std::cout << ss <<std::endl;
}