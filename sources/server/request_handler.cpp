#include "request_handler.h"
#include "serv_connection.h"

#include <factory.h>

ReqHandler::ReqHandler(const std::array<unsigned char, 512> &buffer)
    : input_buffer_(buffer)
{

    j_input_buffer_ = nlohmann::json::parse(input_buffer_.data());
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
    json j_response = json::object({{"id_cmd"}, {"response"}});

    if (!j_input_buffer_.contains(kDataKey)) {
        if (const auto action = ActionFactory::ActionFact(1)) {
            if( action->execute(j_input_buffer_)) {
                j_response["response"] = "Your registration request has been accepted";
                //Send_msg(j_response);
            } else {
                j_response["id_cmd"] = 1;
                j_response["answer"] = "There is already such a user";
                //Send_msg(answer);
            }
        } else {
            // TODO: проверка учетных данных + обработка ответа
        }
    }
}