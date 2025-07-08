#ifndef SELECT_DIRECTOR_H
#define SELECT_DIRECTOR_H


#include "sql_database/directors/director.h"
#include "sql_database/builders/builder.h"

class SelectDirector : public IDirector {
private:
    IBuilder* builder_;
public:
    explicit SelectDirector(IBuilder& builder)
        : builder_(&builder){}

    void CreateSqliteRequest(const std::string &table_name, const std::vector<std::string> &columns_names) const {
        builder_->SetTableName(table_name);
        builder_->SetColumnsNames(columns_names);
    }

    void SetBuilder(IBuilder &builder) override {
        builder_ = &builder;
    }

};

#endif //SELECT_DIRECTOR_H
