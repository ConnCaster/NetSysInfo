#ifndef DROP_DIRECTOR_H
#define DROP_DIRECTOR_H

#include "sql_database/directors/director.h"
#include "sql_database/builders/builder.h"

class DropDirector : public IDirector {
private:
    IBuilder& builder_;
public:
    explicit DropDirector(IBuilder& builder)
        : builder_(builder){}

    ~DropDirector() = default;

    void CreateSqliteRequest(const std::string &table_name) const {
        builder_.SetTableName(table_name);
    }
    void SetBuilder(IBuilder &builder) override {
        builder_ = builder;
    }

};
#endif //DROP_DIRECTOR_H
