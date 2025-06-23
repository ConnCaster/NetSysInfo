#include "sql_database/requests//select.h"

std::string Select::GetRequestPlainText() {
    for (const auto& column_name : column_names_) {
        request_ += " " + column_name + ",";
    }
    request_.back() = ' ';

    request_ += "FROM " + table_name_;
    // SELECT COUNT(*) FROM commands_table
    return request_;
}
