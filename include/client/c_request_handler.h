#ifndef CLIENT_REQUEST_HANDLER_H
#define CLIENT_REQUEST_HANDLER_H

#include <array>
#include <nlohmann/json.hpp>

constexpr unsigned int kBufSize = 512;

using json = nlohmann::json;

// ключи верхнего уровня ответа клиента
constexpr std::string_view kAuthKey = "auth";
constexpr std::string_view kDataKey = "data";

// вложенные ключи в "auth"
constexpr std::string_view kUsernameKey = "username";
constexpr std::string_view kSerialHardDiskKey = "serial_hard_disk";

// вложенные ключи в "data"
//constexpr std::string_view kIdKey = "id_cmd";
constexpr std::string_view kResponseKey = "response";

// индификаторы команд
constexpr int id_cmd_member_info {2};

class ReqHandler {
public:
    explicit ReqHandler(const std::array<unsigned char, kBufSize>& buffer);

    json GetResponse() {
        return j_output_buffer;
    }
private:
    void DoHandle();
private:
    json j_input_buffer_;
    json j_output_buffer ;
};

#endif //CLIENT_REQUEST_HANDLER_H
