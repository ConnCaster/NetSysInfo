#ifndef INSERT_H
#define INSERT_H

#include <vector>

#include "sql_requests.h"

class Insert : public ISQLRequest {
private:
    std::string request_{"INSERT INTO"};
    std::string table_name_;
    std::vector<std::string> column_names_;
    std::pair<std::string, std::string> values_;
public:
    explicit Insert() = default;
    ~Insert() override = default;

    void AddTableName(const std::string& table_name) override {
        table_name_ = table_name;
    }

    void AddColumns(const std::vector<std::string>& columns) override {
        column_names_ = columns;
    }

    void AddValues(const std::pair<std::string, std::string> &values) override {
        values_ = values;
    }

    std::string GetRequestPlainText() override;
};

#endif //INSERT_H
