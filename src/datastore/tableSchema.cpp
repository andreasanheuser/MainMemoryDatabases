#include "tableSchema.h"
#include "../tools/stringExtensions.h"
#include <fstream>
#include <iostream>

namespace datastore {

  ColumnDef::ColumnDef(const std::string& aColumnName, const ColumnType& aColumnType)
    : _columnName(aColumnName), _columnType(aColumnType)
  {
  }

  TableDef::TableDef(const std::string& aTabName, const std::vector<ColumnDef>& aColumnDefs)
    : _tabName(aTabName), _columnDefs(aColumnDefs)
  {
  }

  TableDef::TableDef(const std::string& aTabName, const std::string& aFilepath)
    : _tabName(aTabName){
      std::ifstream ifs(aFilepath, std::ifstream::in);
      std::string currentline;
      while(getline(ifs, currentline)){
        std::vector<std::string> tokens = tools::tokenize(currentline, ';');
        if(tokens[1] == "IDENTIFIER") _columnDefs.push_back(ColumnDef(tokens[0], ColumnDef::ColumnType::IDENTIFIER));
        if(tokens[1] == "INTEGER") _columnDefs.push_back(ColumnDef(tokens[0], ColumnDef::ColumnType::INTEGER));
        if(tokens[1] == "TEXT") _columnDefs.push_back(ColumnDef(tokens[0], ColumnDef::ColumnType::TEXT));
        if(tokens[1] == "DATE") _columnDefs.push_back(ColumnDef(tokens[0], ColumnDef::ColumnType::DATE));
        if(tokens[1] == "FLAG") _columnDefs.push_back(ColumnDef(tokens[0], ColumnDef::ColumnType::FLAG));
        if(tokens[1] == "DECIMAL") _columnDefs.push_back(ColumnDef(tokens[0], ColumnDef::ColumnType::DECIMAL));
      }
  }      

}
