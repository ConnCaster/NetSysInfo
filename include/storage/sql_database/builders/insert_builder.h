#ifndef INSERT_BUILDER_H
#define INSERT_BUILDER_H

#include "sql_database/builders/builder.h"
#include "sql_database/requests/insert.h"

class InsertBuilder : public IBuilder {
private:
    std::unique_ptr<ISQLRequest> insert_;;
public:
    InsertBuilder()
        : insert_(std::make_unique<Insert>(Insert()) )
    {};

    ~InsertBuilder() override = default;

    void SetTableName(const std::string& table_name) override{
        insert_->AddTableName(table_name);
    }

    void SetColumnsNames(const std::vector<std::string>& column_names) override {
        insert_->AddColumns(column_names);
    }

    void SetValues(const std::pair<std::string, std::string>& values) override {
        insert_->AddValues(values);
    }

    ISQLRequest* GetRequest() override {
        return insert_.get();
    }
};


#endif //INSERT_BUILDER_H
