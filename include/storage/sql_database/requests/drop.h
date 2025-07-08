#ifndef DROP_H
#define DROP_H

#include "sql_requests.h"


class Drop : public ISQLRequest{
private:
    std::string request_{"DROP TABLE"};
    std::string table_name_;
    std::vector<std::string> column_names_;
public:
    explicit Drop() = default;
    ~Drop() override = default;

    void AddTableName(const std::string& table_name) override {
        table_name_ = table_name;
    }

    std::string GetRequestPlainText() override {
        request_ += " " + table_name_;
        return request_;
    };
};




#endif //DROP_H
