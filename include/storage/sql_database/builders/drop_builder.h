 #ifndef DROP_BUILDER_H
 #define DROP_BUILDER_H

#include "sql_database/requests/drop.h"
#include "sql_database/builders/builder.h"

 class DropBuilder : public IBuilder {
 private:
     std::unique_ptr<ISQLRequest> drop_table_;
 public:
     DropBuilder()
        : drop_table_(std::make_unique<Drop>(Drop()) )
     {};

     ~DropBuilder() override = default;

     void SetTableName(const std::string& table_name) override{
         drop_table_->AddTableName(table_name);
     }

     ISQLRequest* GetRequest() override {
         return drop_table_.get();
     }
 };


 #endif //DROP_BUILDER_H
