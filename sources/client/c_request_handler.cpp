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
    const auto action = ActionFactory::ActionFact(j_input_buffer_["id_cmd"]);
    json j_response = action->execute();
    std::cout << j_response << std::endl;
    json j_id_cmd;
    j_id_cmd["id_cmd"] = j_input_buffer_["id_cmd"].dump();
    std::cout << j_id_cmd << std::endl;

    j_output_buffer["data"] = { {j_id_cmd}, {j_response} };
    //j_output_buffer["data"] = {{"id_cmd" , "2"}, {"response", "16"}};
}