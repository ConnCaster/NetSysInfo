#ifndef INSERT_DIRECTOR_H
#define INSERT_DIRECTOR_H

#include <sql_database/directors/director.h>
#include "sql_database/builders/builder.h"


class InsertDirector : public IDirector {
private:
    IBuilder& builder_;
public:
    explicit InsertDirector(IBuilder& builder)
        : builder_(builder){}

    void CreateSqliteRequest(const std::string &table_name, const std::vector<std::string> &columns_names, const std::pair<std::string,std::string> &columns_values) const {
        builder_.SetTableName(table_name);
        builder_.SetColumnsNames(columns_names);
        builder_.SetValues(columns_values);
    }

    void SetBuilder(IBuilder &builder) override {
        builder_ = builder;
    }
};


#endif //INSERT_DIRECTOR_H
