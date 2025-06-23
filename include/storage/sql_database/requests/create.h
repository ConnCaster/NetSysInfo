#ifndef CREATE_H
#define CREATE_H

#include <unordered_map>
#include <vector>

#include "sql_requests.h"


class CreateTable : public ISQLRequest{
private:
    std::string table_name_;
    std::string request_{"CREATE TABLE IF NOT EXISTS"};
    std::unordered_map<std::string, std::string> columns_and_types_;
public:
    explicit CreateTable() = default;
    ~CreateTable() override = default;

    void AddTableName(const std::string& table_name) override {
        table_name_ = table_name;
    }

    void AddColumns(const std::vector<std::string>& columns) override {
        for (const auto& column_name : columns) {
            columns_and_types_[column_name] = {};
        }
    }

    void AddColumnTypes(const std::map<std::string, std::string> &column_types) override {
        for (const auto& [column_name , column_type] : column_types) {
            if (columns_and_types_.contains(column_name)) {
                columns_and_types_[column_name] = column_type;
            }
        }
    }

    std::string GetRequestPlainText() override {
        request_ += " " + table_name_ + " (";
        for (const auto& [column_name, column_type] : columns_and_types_) {
            request_ += "'" + column_name + "' " + column_type + ",";
        }
        request_.back() = ')';

        return request_;
    }
};



#endif //CREATE_H
