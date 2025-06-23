
#ifndef SELECT_BUILDER_H
#define SELECT_BUILDER_H

#include <vector>

#include "sql_database/builders/builder.h"
#include "sql_database/requests/select.h"

class SelectBuilder : public IBuilder {
private:
    std::unique_ptr<ISQLRequest> select_;;
public:
    SelectBuilder()
        : select_(std::make_unique<Select>(Select()) )
    {};
    void SetTableName(const std::string& table_name) override {
        select_->AddTableName(table_name);
    }

    void SetColumnsNames(const std::vector<std::string>& column_names) override {
        select_->AddColumns(column_names);
    };

    ISQLRequest* GetRequest() override {
        return select_.get();
    }
};


#endif //SELECT_BUILDER_H
