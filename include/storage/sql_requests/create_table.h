#ifndef CREATE_TABLE_H
#define CREATE_TABLE_H

#include <string>
#include <vector>

class CreateTable {
private:
    std::string cmd_create_table_{"CREATE TABLE IF NOT EXISTS "};
    std::string name_table_;
    std::vector<std::vector<std::string>> columns_;
public:
    explicit CreateTable(std::string_view name_table, std::vector<std::vector<std::string>>& columns);

    void AddColumn(std::string_view name_column);

};

#endif //CREATE_TABLE_H
