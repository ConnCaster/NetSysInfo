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

static int callback(void *check, int argc, char **argv, char **azColName) {
    // void *NotUsed - передается 4-й аргумент из sqlite3_exec
    // int argc - количество стобцов ?
    //char **argv - значение столбца ?
    // char **azColName - название столбца
    int* int_check = static_cast<int*>(check);
    *int_check = std::stoi(argv[0]);
    return 0;
}

void ReqHandler::DoHandle() {

    if (!j_input_buffer_.contains(kDataKey)) {
        const auto action = CreateAction::CreateAct(id_cmd_registration);
        if (action->execute(j_input_buffer_)) {
            j_output_buffer_[kResponseKey] = "Your registration request has been accepted";
        } else {
            SQliteDB sq_check_response_cmd(PathUserDB());
            // int check_occupancy_DB;
            // int rc = sqlite3_exec(sq_check_response_cmd.GetDB(), cmd_check_DB_.c_str(), callback, &check_occupancy_DB, NULL);

            j_output_buffer_[kResponseKey] = "There is already such a user";
            sq_check_response_cmd.read(j_output_buffer_);

            std::cout << j_output_buffer_ << std::endl;

            /*if (check_occupancy_DB) {
                j_output_buffer_[kResponseKey] = "There is already such a user";
                sq_check_response_cmd.read(j_output_buffer_);
            } else {
                // TODO: Что если не будет заранее подготовленных запросов ????
            }*/

        }
    } else {
        SQliteDB sq_check_response_cmd(PathUserDB());
        //sq_check_response_cmd.read(j_output_buffer_);

        const auto action = CreateAction::CreateAct(j_input_buffer_["data"].size() + 1); // TODO: ???
        action->execute(j_input_buffer_);


        j_output_buffer_[kResponseKey] = "";
        sq_check_response_cmd.read(j_output_buffer_);

    }
}

// TODO: Нужно ли серверу постоянно отправлять результаты выполнения предыдущих ответов на запросы от клиента или только после регистрации достаточно??