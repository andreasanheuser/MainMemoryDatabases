#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>

#include "tableSchema.h"
#include "table.h"

class Table;

namespace datastore {

  class Database {
    public:
      Database(const std::string& aDatabaseName);
      ~Database();

      bool addTable(const TableDef& aTableDef);
	  void loadDataIntoTable(const std::string&, const std::string&);
    
    private:
      std::string _dbName;
      std::vector<Table*> _tables;
  };
 
}

#endif
