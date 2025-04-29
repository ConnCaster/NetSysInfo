#include "s_request_handler.h"

#include <file_handler.h>
#include <iostream>
#include <utils.h>

#include "serv_connection.h"
#include "s_factory.h"

std::string ReqHandler::PathUserDB() {
    auto root_path_users_cmd_line = CreateRootDir("database/users_cmd_line/");
    root_path_users_cmd_line += ExtractionNameDB(j_input_buffer_["auth"]["username"]);
    return root_path_users_cmd_line;
}

ReqHandler::ReqHandler(const std::array<unsigned char, buf_size>& buffer)
{
    j_input_buffer_ = nlohmann::json::parse(buffer.data());
    DoHandle();

}

void ReqHandler::DoHandle() {

    if (!j_input_buffer_.contains(kDataKey)) {
        const auto action = CreateAction::CreateAct(id_cmd_registration);
        if (action->execute(j_input_buffer_)) {
            j_output_buffer_[kResponseKey] = "Your registration request has been accepted";
        } else {
            SQliteDB sql_check_response_cmd(PathUserDB());

            int check_occupancy_DB = sql_check_response_cmd.check_occupancy_table();
            if (check_occupancy_DB != kEmptyTable) {
                j_output_buffer_[kResponseKey] = "There is already such a user";
                sql_check_response_cmd.read(j_output_buffer_);
            } else {
                // TODO: Что если не будет заранее подготовленных запросов ????
            }
        }
    } else {

        const auto action = CreateAction::CreateAct(j_input_buffer_["data"].size() + 1); // TODO: ???
        action->execute(j_input_buffer_);

        SQliteDB sql_check_response_cmd(PathUserDB());

        int check_occupancy_DB = sql_check_response_cmd.check_occupancy_table();
        if (check_occupancy_DB != kEmptyTable) {
            //TODO: для этого kResponseKey нужен в sql.read возможность его наполнения, а не только id_cmd
            j_output_buffer_[kResponseKey] = "There is already such a user";
            sql_check_response_cmd.read(j_output_buffer_);
        } else {
            // TODO: Что если не будет заранее подготовленных запросов ????
        }
        j_output_buffer_[kResponseKey] = "";
        //sq_check_response_cmd.read(j_output_buffer_);
    }
}

// TODO: Нужно ли серверу постоянно отправлять результаты выполнения предыдущих ответов на запросы от клиента или только после регистрации достаточно??