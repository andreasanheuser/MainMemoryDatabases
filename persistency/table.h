#ifndef TABLE_H
#define TABLE_H

#include <vector>
#include <string>
#include <map>
#include "column.h"

namespace persistency {

  class Table {
    public:
      Table(const std::string& tableName, unsigned numColumns, 
          const std::vector<std::pair<std::string, ColumnBase::ColumnType>>& columnNameTypeLookup);
      ~Table();

      bool loadDataFromFile(const std::string& fd);
      void printDataToScreen() const;
      int size() const;

    private:
      std::string _tableName;
      unsigned _numColumns;
      std::vector<ColumnBase*> _columns;

  };

}

#endif
