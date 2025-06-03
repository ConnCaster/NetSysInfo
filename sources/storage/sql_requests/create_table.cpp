#include "create_table.h"


CreateTable::CreateTable(std::string_view name_table, std::vector<std::vector<std::string>>& columns)
    : name_table_(name_table), columns_(columns) {
    std::string create_table = cmd_create_table_ + name_table_ + "(";

    for (int i {0}; i < columns_.size(); i++) {
        create_table += "'";
        create_table += *columns_[i].data();
    }
}
