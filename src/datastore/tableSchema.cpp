#include "tableSchema.h"
#include "../tools/stringExtensions.h"

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
      std::ifstream ifs{aFilepath, std::ifstream::in};
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
   
/*
  DatabaseDef::DatabaseDef(const std::string& aDbName, const std::map<TableDef>& aTableDefs)
	: _dbDefName(aDbName), _tableDefs(aTableDefs)
  {
  }
*/
  TPCH::TPCH()
  {

    std::vector<ColumnDef> lcd = {ColumnDef("R_REGIONKEY", ColumnDef::ColumnType::IDENTIFIER),
                            ColumnDef("R_NAME", ColumnDef::ColumnType::TEXT),
                            ColumnDef("R_COMMENT", ColumnDef::ColumnType::TEXT)};
    TableDef ltd{"Region", lcd};
    _tableDefs.insert(std::pair<std::string, TableDef>("Region", ltd));

    std::vector<ColumnDef> lcd2 = {ColumnDef("L_ORDERKEY", ColumnDef::ColumnType::IDENTIFIER),
                              ColumnDef("L_PARTKEY", ColumnDef::ColumnType::IDENTIFIER),
                              ColumnDef("L_SUPPKEY", ColumnDef::ColumnType::IDENTIFIER),
                              ColumnDef("L_LINENUMBER", ColumnDef::ColumnType::INTEGER),
                              ColumnDef("L_QUANTITY", ColumnDef::ColumnType::DECIMAL),
                              ColumnDef("L_EXTENDEDPRICE", ColumnDef::ColumnType::DECIMAL),
                              ColumnDef("L_DISCOUNT", ColumnDef::ColumnType::DECIMAL),
                              ColumnDef("L_TAX", ColumnDef::ColumnType::DECIMAL),
                              ColumnDef("L_RETURNFLAG", ColumnDef::ColumnType::FLAG),
                              ColumnDef("L_LINESTATUS", ColumnDef::ColumnType::FLAG),
                              ColumnDef("L_SHIPDATE", ColumnDef::ColumnType::DATE),
                              ColumnDef("L_COMMITDATE", ColumnDef::ColumnType::DATE),
                              ColumnDef("L_RECEIPTDATE", ColumnDef::ColumnType::DATE),
                              ColumnDef("L_SHIPINSTRUCT", ColumnDef::ColumnType::TEXT),
                              ColumnDef("L_SHIPMODE", ColumnDef::ColumnType::TEXT),
                              ColumnDef("L_COMMENT", ColumnDef::ColumnType::TEXT)};
    TableDef ltd2{"Lineitem", lcd2};
    _tableDefs.insert(std::pair<std::string, TableDef>("Lineitem", ltd2));
    
//  	std::vector<DatabaseDef> ldd = {"tpch@0_1", lcd}; 

  }
}
