#ifndef DIRECTOR_H
#define DIRECTOR_H

#include "sql_database/builders/builder.h"


class IDirector {
public:
    virtual ~IDirector() = default;
    virtual void CreateSqliteRequest() {};
    virtual void SetBuilder(IBuilder& builder) = 0;
};

#endif //DIRECTOR_H
