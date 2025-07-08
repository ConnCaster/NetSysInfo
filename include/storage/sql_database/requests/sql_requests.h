#ifndef SQL_REQUESTS_H
#define SQL_REQUESTS_H

#include <map>
#include <string>
#include <vector>

class ISQLRequest {
public:
    virtual ~ISQLRequest() = default;

    virtual void AddTableName(const std::string& table_name) {}
    virtual void AddColumns(const std::vector<std::string>& columns) {}
    virtual void AddValues(const std::pair<std::string, std::string>& values) {}
    virtual void AddColumnTypes(const std::map<std::string, std::string> &column_types) {}

    virtual std::string GetRequestPlainText() = 0;

};


#endif //SQL_REQUESTS_H
