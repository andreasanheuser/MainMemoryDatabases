#include <fstream>
#include <iostream>

#include "table.h"
#include "column.cpp"
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
        _columns.push_back(new Column<std::string>(c.getColumnName(), ColumnDef::ColumnType::TEXT));
        break;
      case ColumnDef::ColumnType::DATE:
        _columns.push_back(new Column<Date>(c.getColumnName(), ColumnDef::ColumnType::DATE));
        break;
      default: throw "Unknown type";
    }
  }
}

Table::~Table()
{
  for (auto c : _columns) {
    delete c;
  }
}

bool Table::loadDataFromFile(const std::string& aFd) {
  std::ifstream lIfs (aFd, std::ifstream::in);

  if (!lIfs.is_open()) 
    return false;

  std::string lCurrentLine;
  while (getline(lIfs, lCurrentLine)) {
    std::vector<std::string> lTokens = tools::tokenize(lCurrentLine, '|');

    for (unsigned i = 0; i < _columns.size(); ++i) {
      if(!_columns[i]->insertValue(lTokens[i]))
        throw "Fileload failed"; 
    }
  }

  lIfs.close();

  return true;
}

void Table::printDataToScreen() const {
  std::cout << "Table: " << _tableName << ", Records: " << size() << std::endl;
  for (ColumnBase* b : _columns) {
    std::cout << (*b);
  }
  std::cout << std::endl;
}

}
