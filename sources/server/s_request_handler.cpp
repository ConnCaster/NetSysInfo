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

void ReqHandler::DoHandle() {

    if (!j_input_buffer_.contains(kDataKey)) {
        const auto action = CreateAction::CreateAct(id_cmd_registration);
        if (action->execute(j_input_buffer_)) {
            j_output_buffer_[kResponseKey] = "Your registration request has been accepted";
        } else {
            SelectBuilder select_count_builder;
            SelectDirector select_director(select_count_builder);
            select_director.CreateSqliteRequest("commands_table", {"COUNT(*)"});

            if (select_count_builder.GetRequest()->GetRequestPlainText() == kEmptyTable) {
                // Придумать действия, если нет запросов к клиенту
            } else {
                try {
                    std::string path_users_db = PathUserDB();
                    const auto db_user = std::make_shared<SQLite::Database> (path_users_db, SQLite::OPEN_READWRITE|SQLite::OPEN_CREATE);

                    SelectBuilder all_select_builder;
                    select_director.SetBuilder(all_select_builder);
                    select_director.CreateSqliteRequest("commands_table", {"*"});

                    SQLite::Statement query(*db_user, all_select_builder.GetRequest()->GetRequestPlainText());

                    query.executeStep();
                    std::string check_res = query.getColumn(0);
                    std::string check_res2 = query.getColumn(1);
                    j_output_buffer_[kResponseKey] = query.getColumn(0);
                    j_output_buffer_[kIdKey]= query.getColumn(1);

                    db_user->exec("DELETE FROM commands_table WHERE rowid = (SELECT rowid FROM commands_table LIMIT 1);");

                } catch (const std::exception &e) {
                    std::cerr << e.what() << std::endl;
                }
            }
            /*SQliteDB sql_check_response_cmd(PathUserDB());

            int check_occupancy_DB = sql_check_response_cmd.check_occupancy_table();
            if (check_occupancy_DB != kEmptyTable) {
                j_output_buffer_[kResponseKey] = "There is already such a user";
                sql_check_response_cmd.read(j_output_buffer_);
            } else {
                // TODO: Что если не будет заранее подготовленных запросов ????
            }*/
        }
    } else {

        /*
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
        //sq_check_response_cmd.read(j_output_buffer_);*/
    }
}

// TODO: Нужно ли серверу постоянно отправлять результаты выполнения предыдущих ответов на запросы от клиента или только после регистрации достаточно??