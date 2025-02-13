#ifndef CLIENT_SERVER_REQUEST_HANDLER_H
#define CLIENT_SERVER_REQUEST_HANDLER_H

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

// вложенные ключи в "auth"
constexpr std::string_view kIdKey = "id_cmd";
constexpr std::string_view kResponseKey = "response";

class ReqHandler {
public:
    ReqHandler(const std::array<unsigned char, kBufSize>& buffer);
private:
    void DoHandle();
private:
    std::array<unsigned char, kBufSize> input_buffer_;
    json j_input_buffer_;
};

#endif //CLIENT_SERVER_REQUEST_HANDLER_H
