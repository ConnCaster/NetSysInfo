#include "request_handler.h"

ReqHandler::ReqHandler(const std::array<unsigned char, 512> &buffer)
    : input_buffer_(buffer)
{

    j_input_buffer_ = nlohmann::json::parse(input_buffer_.data());
    std::string action_str{};
    DoHandle();
}

/*
 *
 * j_input_buffer_ json:
 * I. Клиент дожидается регистрации:
 *          {
 *              "auth": {
 *                  "username": "<username>",
 *                  "serial_hard_disk": "<serial_hard_disk>"
 *              }
 *          }
 *
 * II. Клиент авторизован и присылает результаты исполнения команд:
 *          {
 *              "auth": {
 *                  "username": "<username>",
 *                  "serial_hard_disk": "<serial_hard_disk>"
 *              },
 *              "data": [
 *                  {
 *                  "id_cmd": 1,
 *                  "response": "<response>"
 *                  },
 *                  ... ,
 *                  {
 *                  "id_cmd": INT_MAX,
 *                  "response": "<response>"
 *                  }
 *              ]
 *          }
 */
void ReqHandler::DoHandle() {
    json j_response = json::object({{"key", "value"}, {"key", "value"}});
    if (!j_input_buffer_.contains(kDataKey)) {
        // TODO: авторизация
    } else {
        // TODO: проверка учетных данных + обработка ответа
    }
}