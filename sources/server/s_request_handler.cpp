#include <iostream>

#include "utils.h"
#include "s_factory.h"
#include "serv_connection.h"
#include "s_request_handler.h"

#include "sql_database/builders/select_builder.h"
#include "sql_database/directors/select_director.h"
#include "SQLiteCpp/Database.h"
#include "SQLiteCpp/Statement.h"

std::string ReqHandler::PathUserDB() {
    auto root_path_users_db = CreateRootDir("database/users/");
    root_path_users_db += ExtractionNameDB(j_input_buffer_["auth"]["username"] ) + ".db3";
    return root_path_users_db;
}

ReqHandler::ReqHandler(const std::array<unsigned char, buf_size>& buffer)
{
    j_input_buffer_ = json::parse(buffer.data());
    DoHandle();

}

void ReqHandler::SendResponse() {
    try {
        std::string path_users_db = PathUserDB();
        const auto db_user = std::make_shared<SQLite::Database> (path_users_db, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

        SelectBuilder select_count_builder;
        SelectDirector select_director(select_count_builder);
        select_director.CreateSqliteRequest("commands_table", {"COUNT(*)"});

        SQLite::Statement query(*db_user, select_count_builder.GetRequest()->GetRequestPlainText());
        query.executeStep();

        if (query.getColumn(0).getInt() == kEmptyTable) {
            j_output_buffer_[kResponseKey] = "End of the connection session";
            j_output_buffer_[kIdKey]= "0";
        } else {

            SelectBuilder all_select_builder;
            select_director.SetBuilder(all_select_builder);
            select_director.CreateSqliteRequest("commands_table", {"*"});

            SQLite::Statement query(*db_user, all_select_builder.GetRequest()->GetRequestPlainText());

            query.executeStep();
            j_output_buffer_[kResponseKey] = query.getColumn(0).getString();
            j_output_buffer_[kIdKey]= query.getColumn(1).getString();

            db_user->exec("DELETE FROM commands_table WHERE rowid = (SELECT rowid FROM commands_table LIMIT 1);");
        }

    } catch (const std::exception &e) {
        std::cerr << e.what() << std::endl;
    }
}


void ReqHandler::DoHandle() {
    if (!j_input_buffer_.contains(kDataKey)) {
        const auto action = CreateAction::CreateAct(id_cmd_registration);
        if (action->execute(j_input_buffer_)) {
            j_output_buffer_[kResponseKey] = "Your registration request has been accepted";
        } else {
            SendResponse();
        }
    } else {
        std::string str_tmp = j_input_buffer_["data"]["id_cmd"];
        const auto action = CreateAction::CreateAct(std::stoi(str_tmp));
        action->execute(j_input_buffer_);

        SendResponse();
    }
}