#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <map>

#include "tableSchema.h"
#include "column.h"

namespace datastore {

  class Table {
    public:
      Table(const TableDef& aTableDef);
      ~Table();

      bool loadDataFromFile(const std::string& aFd);
      void printDataToScreen() const;
      int size() const { return _columns[0] ? _columns[0]->size() : -1; }

    private:
      std::string _tableName;
      std::vector<ColumnBase*> _columns;

      Table(const Table&) = delete;
      Table& operator=(const Table&) = delete;
  };

}

#endif
