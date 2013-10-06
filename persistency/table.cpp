#include <fstream>
#include <iostream>
#include "table.h"
#include "column.cpp"
#include "../tools/stringExtensions.h"

namespace persistency {

Table::Table(const std::string& tableName, unsigned numColumns, 
    const std::vector<std::pair<std::string, ColumnBase::ColumnType>>&  columnNameTypeLookup)
  : _tableName(tableName), _numColumns(numColumns)
{
  if (_numColumns != columnNameTypeLookup.size())
    throw "Column number mismatch";

  // initialize columns with name and type
  for (auto c : columnNameTypeLookup) {
    switch (c.second) {
      case ColumnBase::ColumnType::INTEGER:
        _columns.push_back(new Column<int>(c.first, ColumnBase::ColumnType::INTEGER));
        break;
      case ColumnBase::ColumnType::STRING:
        _columns.push_back(new Column<std::string>(c.first, ColumnBase::ColumnType::STRING));
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

bool Table::loadDataFromFile(const std::string& fd) {
  std::ifstream ifs (fd, std::ifstream::in);

  if (!ifs.is_open()) 
    return false;

  std::string currentLine;
  while (getline(ifs, currentLine)) {
    std::vector<std::string> tokens = tools::tokenize(currentLine, '|');

    for (unsigned i = 0; i < _columns.size(); ++i) {
      if(!_columns[i]->insertValue(tokens[i]))
        throw "Fileload failed"; 
    }
  }

  ifs.close();

  return true;
}

void Table::printDataToScreen() const {
  std::cout << "Table: " << _tableName << ", Records: " << size() << std::endl;
  for (int i = 0; i < _columns[0]->size(); ++i) {
    for (ColumnBase* b : _columns) {
      std::cout << (*b)[i] << " | ";
    }
    std::cout << std::endl;
  }
}

int Table::size() const {
  return _columns[0] ? _columns[0]->size() : -1;
}

}
