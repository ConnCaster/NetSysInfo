#include "c_request_handler.h"
#include "cli_connection.h"
#include "c_factory.h"

ReqHandler::ReqHandler(const std::array<unsigned char, buf_size>& buffer)
{
    j_input_buffer_ = nlohmann::json::parse(buffer.data());
    DoHandle();
}

void ReqHandler::DoHandle() {
    std::string tmp = j_input_buffer_["id_cmd"];
    int tmp_ = std::stoi(tmp);
    const auto action = CreateAction::CreateAct(tmp_);
    json j_response = action->execute();

    json j_resp = json::object({{"id_cmd", j_input_buffer_["id_cmd"]}, {"response", j_response["response"]}});

    if (j_input_buffer_["id_cmd"] == "0") {
        j_output_buffer = j_resp;
    } else {
        json j_array = json::array();
        j_array.push_back(j_resp);
        j_output_buffer = j_array;
    }
}
