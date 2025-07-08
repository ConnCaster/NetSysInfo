#include "c_request_handler.h"
#include "cli_connection.h"
#include "c_factory.h"

ReqHandler::ReqHandler(const nlohmann::json& j_server)
    : j_input_buffer_(j_server)
{
    DoHandle();
}

void ReqHandler::DoHandle() {
    std::string id_key = j_input_buffer_[kIdKey];
    const auto action = CreateAction::CreateAct(std::stoi(id_key));
    json j_response = action->execute();

    json j_resp = json::object({{"id_cmd", j_input_buffer_[kIdKey]}, {"response", j_response[kResponseKey]}});

    if (j_input_buffer_[kIdKey] == kIdCmdEndSession) {
        j_output_buffer = j_resp;
    } else {
        json j_array = json::object();
        j_array = (j_resp);
        j_output_buffer = j_array;
    }
}
