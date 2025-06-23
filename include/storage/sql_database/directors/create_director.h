#ifndef CREATE_DIRECTOR_H
#define CREATE_DIRECTOR_H

#include "sql_database/directors/director.h"
#include "sql_database/builders/builder.h"

class CreateDirector : public IDirector {
private:
    IBuilder& builder_;
    public:
    explicit CreateDirector(IBuilder& builder)
        : builder_(builder){}

    void CreateSqliteRequest(const std::string &table_name, const std::vector<std::string> &columns_names, const std::map<std::string, std::string> &columns_types) const {
        builder_.SetTableName(table_name);
        builder_.SetColumnsNames(columns_names);
        builder_.SetColumnsTypes(columns_types);
    }

    void SetBuilder(IBuilder &builder) override {
        builder_ = builder;
    }

};
#endif //CREATE_DIRECTOR_H
