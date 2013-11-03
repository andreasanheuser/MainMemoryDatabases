#include "database.h"
#include "table.h"
#include "../tools/measure.h"

#include <vector>
#include <string>
#include <sstream>
#include <exception>

#include <iostream>
#include <fstream>

using namespace std;
using namespace tools;

namespace datastore {
/*
		Database::Database(const DatabaseDef& aDatabaseDef)
		: _dbName(aDatabaseDef.getDbName())
		{
			for(auto t : aDatabaseDef.getTableDefs()){
				_tables.push_back(new Table(t.getTableDef());
			}
		}
		
		Database::~Database(){
		  for (auto t : _tables) {
  			  delete t;
  			}
		}
*/

	Database::Database(){}
	
	Database::~Database(){}
	

		void Database::readDBInfo(const std::string& adbPath)
		: _dbPath(adbPath)
		{
			std::vector <std::string> table;
  			std::ifstream myfile (_dbPath);
         	if (myfile.is_open()) {
         		string atableLine;
    			while ( getline (myfile, atableLine) ){
      	 			table.push_back(atableLine);
    	 		}
    	 	myfile.close();
         	}
  		 	else cout << "Unable to open file" << endl;
  		 	
  		 	for (unsigned i=0;i<table.size();i+=2)
  		 		addTable(table[i],table[i+1]);
		}

		
		void Database::addTable(const std::string& atableName, const std::string& atablePath){
			TPCH lTpch;
  			Table lt(lTpch.getTableDef(atableName));
  			string lFile(atablePath);
  			cout << "Table: " << atableName << endl;

  			Measure lm;
  			double lStart = lm.startMeasure();

  			lt.loadDataFromFile(lFile);

  			double lEnd = lm.endMeasure();

  			lm.printMeasures(lStart, lEnd, lFile);
  
  			lt.printDataToScreen();
  			
		}	
}
