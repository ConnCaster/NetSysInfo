#ifndef BUILDER_H
#define BUILDER_H


#include "sql_database/requests/sql_requests.h"


class IBuilder {
public:
    virtual ~IBuilder() = default;

    virtual void SetTableName(const std::string& table_name) {}
    virtual void SetColumnsNames(const std::vector<std::string>& column_names) {}
    virtual void SetValues(const std::pair<std::string, std::string>& values) {}
    virtual void SetColumnsTypes(const std::map<std::string, std::string>& column_types) {}

    virtual ISQLRequest* GetRequest() = 0;

};


#endif //BUILDER_H
