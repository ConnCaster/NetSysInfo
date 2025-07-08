#ifndef CREATE_TABLE_BUILD_H
#define CREATE_TABLE_BUILD_H

#include "sql_database/builders/builder.h"
#include "sql_database/requests/create.h"
#include "SQLiteCpp/Database.h"




class CreateBuilder : public IBuilder {
private:
    CreateTable* create_table_;
public:
    CreateBuilder()
        : create_table_(new CreateTable{})
    {};

    ~CreateBuilder() override = default;

    void SetTableName(const std::string& table_name) override{
        create_table_->AddTableName(table_name);
    }

    void SetColumnsNames(const std::vector<std::string>& column_names) override {
        create_table_->AddColumns(column_names);
    };

    void SetColumnsTypes(const std::map<std::string, std::string>& column_types) override {
        create_table_->AddColumnTypes(column_types);
    };

    // CREATE TABLE IF NOT EXISTS new_table2 (id Integer);
    ISQLRequest* GetRequest() override {
        return create_table_;
    }
};



#endif //CREATE_TABLE_BUILD_H
