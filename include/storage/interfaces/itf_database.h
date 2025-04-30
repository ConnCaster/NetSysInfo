#ifndef ITF_DATABASE_H
#define ITF_DATABASE_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;


class IDataBase  {
public:
    virtual ~IDataBase() = default;
    virtual void write(const json &content) = 0;
    virtual void read(json &content) = 0;
};



#endif //ITF_DATABASE_H
