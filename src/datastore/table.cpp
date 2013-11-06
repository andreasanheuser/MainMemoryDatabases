#include <fstream>
#include <iostream>

#include "table.h"
#include "datejd.h"
#include "mmaphandle.h"
#include "../tools/stringExtensions.h"

namespace datastore {


  Table::Table(const TableDef& aTableDef)
    : _tableName(aTableDef.getTableName())
  {
    // initialize columns with name and type
    for (auto c : aTableDef.getColumnDefs()) {
      switch (c.getColumnType()) {
        case ColumnDef::ColumnType::IDENTIFIER:
          _columns.push_back(new Column<int>(c.getColumnName(), ColumnDef::ColumnType::INTEGER));
          break;
        case ColumnDef::ColumnType::INTEGER:
          _columns.push_back(new Column<int>(c.getColumnName(), ColumnDef::ColumnType::INTEGER));
          break;
        case ColumnDef::ColumnType::DECIMAL:
          _columns.push_back(new Column<double>(c.getColumnName(), ColumnDef::ColumnType::DECIMAL));
          break;
        case ColumnDef::ColumnType::FLAG:
          _columns.push_back(new Column<char>(c.getColumnName(), ColumnDef::ColumnType::FLAG));
          break;
        case ColumnDef::ColumnType::TEXT:
          _columns.push_back(new TextColumn(c.getColumnName(), 4096));
          break;
        case ColumnDef::ColumnType::DATE:
          _columns.push_back(new Column<DateJd>(c.getColumnName(), ColumnDef::ColumnType::DATE));
          break;
        default: throw UnknownColumnTypeException();
      }
    }
  }

  Table::~Table()
  {
    for (auto c : _columns) {
      delete c;
    }
  }

  bool Table::loadDataFromFile(const std::string& aFd) 
  {
    try {
      MmapHandle m{aFd};

      char* map{m.getMmap()};
      char* start = map;
      char* end = map;

      unsigned long columnCount{_columns.size()};
      unsigned long mapSize{m.size()};
      int i{0};

      while (start < map + mapSize) {
      // skip empty tokens at linebreak
        if (i == columnCount) {
          i = 0;
          start = end + 2;
          continue;
        }

        if(!_columns[i++]->insertValue(start, end)) {
          throw ColumnInsertException();
        }

        start = end + 1;
      }

      return true;
    }
    catch (std::exception& e) {
      std::cout << e.what() << std::endl;
      clear();
      return false;
    }
  }

  void Table::writeDataToFile(const std::string& aFd)
  {

  }

  void Table::printDataToScreen() const 
  {
    if (0 == size()) return;

    std::cout << "Table: " << _tableName << ", Records: " << size() << std::endl;
    for (ColumnBase* b : _columns) {
      std::cout << (*b);
    }
    std::cout << std::endl;
  }

  void Table::clear()
  {
    for (auto c : _columns)
      c->clear();
  }

}
