#include "sql_database/requests/insert.h"

//INSERT INTO table_name (column_name, ... , column_name) VALUES (value1, value2, value3, ...);

std::string Insert::GetRequestPlainText() {
    request_ += " " + table_name_ + "(";
    for (const auto& column_name : column_names_) {
        request_ += " '" + column_name + "',";
    }
    request_.back() = ')';

    request_ += " " + std::string("VALUES") + "(";
    request_ += " '" + std::to_string(values_.second) + "', '" + values_.first + "' )";
    return request_;
}