#include <vector>
#include <string>
#include <iostream>

#include "database.h"
#include "table.h"
#include "tableSchema.h"
#include "../tools/timer.h"

namespace datastore {

  Database::Database(const std::string& aDatabaseName)
    : _dbName(aDatabaseName)
  {
  }
		
  Database::~Database()
  {
    for(auto t : _tables)
    {
      delete t;
    }
  }
	
  bool Database::addTable(const TableDef& aTableDef)
  {	
    const TableDef &lTableDef = aTableDef;
    _tables.push_back(new Table(lTableDef));

    // TODO: handle possible parsing exceptions when creating table schema from file
    return true;
  }	

  void Database::loadDataIntoTable(const std::string& aTableName, const std::string& aTableContentPath)
  {
    std::cout << "Table: " << aTableName << std::endl;

    tools::Timer timer;
    timer.start();
			
    _tables.back()->loadDataFromFile(aTableContentPath);
			
    timer.stop();

    timer.printResults(aTableContentPath);
	
    // for testing only. use only with small tables as this will output a lot to screen
    //_tables.back()->printDataToScreen();
  }

}
