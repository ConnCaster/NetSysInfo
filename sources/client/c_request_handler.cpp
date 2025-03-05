#include "c_request_handler.h"

#include <iostream>
#include <variant>

#include "cli_connection.h"
#include "c_factory.h"

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
    const auto action = CreateAction::CreateAct(j_input_buffer_["id_cmd"]);
    json j_response = action->execute();

    json j_resp = json::object({{"id_cmd", j_input_buffer_["id_cmd"]}, {"response", j_response["response"]}});

    if (j_input_buffer_["id_cmd"] == 0) {
        j_output_buffer = j_resp;
    } else {
        json j_array = json::array();
        j_array.push_back(j_resp);
        j_output_buffer = j_array;
    }
}
