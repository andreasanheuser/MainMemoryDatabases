#include <fstream>
#include <iostream>
#include <sstream>

// mmap stuff
#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <algorithm>


#include "table.h"
#include "datejd.h"
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
//        _columns.push_back(new Column<const char*>(c.getColumnName(), ColumnDef::ColumnType::TEXT));
        _columns.push_back(new TextColumn(c.getColumnName(), 4096));
        break;
      case ColumnDef::ColumnType::DATE:
        _columns.push_back(new Column<DateJd>(c.getColumnName(), ColumnDef::ColumnType::DATE));
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

// TODO: might leak - add proper resource handles
bool Table::loadDataFromFile(const std::string& aFd) {
  int fd = open(aFd.c_str(), O_RDONLY);

  if (-1 == fd) {
    // file opening failed
    return false;
  }

  struct stat buffer;
  int status = fstat(fd, &buffer);

  char* map = (char*)mmap(0, buffer.st_size, PROT_READ, MAP_SHARED, fd, 0);

  if (MAP_FAILED == map) {
    close(fd);
    return false;
  }

  char* start = map;
  char* end = nullptr;

  int columnCount = _columns.size();
  int i{0};

  while (start < map + buffer.st_size) {
    // skip empty tokens at linebreak
    if(i == columnCount) {
      i = 0;
      start = end + 2;
      continue;
    }

    end = std::find(start, map + buffer.st_size, '|');

    if(!_columns[i++]->insertValue(start, end)) {
      throw "Fileload failed"; //TODO: throw proper exceptions
    }

    start = end + 1;
  }

  if (-1 == munmap(map, buffer.st_size)) {
    // error during unmapping occured
    // handle how?
  }
  close(fd);

  return true;

/*  
  std::ifstream lIfs (aFd, std::ifstream::in);

  if (!lIfs.is_open()) 
    return false;

  std::string lCurrentLine;
  while (getline(lIfs, lCurrentLine)) {
    insertTuple(lCurrentLine, '|');
  }
  lIfs.close();

  return true;
*/
}

bool Table::insertTuple(const std::string& aTuple, const char aDelim)
{
/*
  std::stringstream lss(aTuple);
  std::string lItem;

  int i{0};
  while (std::getline(lss, lItem, aDelim)) {
    if(!_columns[i++]->insertValue(lItem))
      throw "Fileload failed";
  }
*/
  return true;
}

void Table::printDataToScreen() const {
/*  
  std::cout << "Table: " << _tableName << ", Records: " << size() << std::endl;
  for (ColumnBase* b : _columns) {
    std::cout << (*b);
  }
  std::cout << std::endl;
*/
  std::cout << "Records: " << size() << std::endl;
}

}
