#include "request_handler.h"
#include "serv_connection.h"

#include <factory.h>

ReqHandler::ReqHandler(const std::array<unsigned char, buf_size>& buffer)
{
    j_input_buffer_ = nlohmann::json::parse(buffer.data());
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

    if (!j_input_buffer_.contains(kDataKey)) {
        const auto action = ActionFactory::ActionFact(1);
        if (action->execute(j_input_buffer_)) {
            j_output_buffer[kResponseKey] = "Your registration request has been accepted";
        } else {
            j_output_buffer[kResponseKey] = "There is already such a user";
            j_output_buffer[kIdKey] = 2;
        }
    } else {
        const auto action = ActionFactory::ActionFact(j_input_buffer_["data"].size());
        action->execute(j_input_buffer_);
        j_output_buffer[kIdKey] = j_input_buffer_["data"].size() + 1;
    }
}