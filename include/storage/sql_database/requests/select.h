#ifndef SELECT_H
#define SELECT_H

#include <vector>

#include "sql_requests.h"

class Select : public ISQLRequest{
private:
    std::string request_{"SELECT"};
    std::string table_name_;
    std::vector<std::string> column_names_;
public:
    explicit Select() = default;
    ~Select() override = default;

    void AddTableName(const std::string& table_name) override {
        table_name_ = table_name;
    }

    void AddColumns(const std::vector<std::string>& columns) override {
        column_names_ = columns;
    }

    std::string GetRequestPlainText() override;
};



#endif //SELECT_H
