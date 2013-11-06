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
      
    private:
      Table(const Table&) = delete;
      Table& operator=(const Table&) = delete;

    public:
      // load data from file aFd into table
      bool loadDataFromFile(const std::string& aFd);

      // writes data row wise to file aFd
      void writeDataToFile(const std::string& aFd);

      // prints data column wise to screen
      void printDataToScreen() const;

      // returns number of tuples in table
      int size() const { return _columns[0] ? _columns[0]->size() : -1; }

      // removes all data from table
      void clear();

    private:
      std::string _tableName;
      std::vector<ColumnBase*> _columns;
  };

}

#endif
