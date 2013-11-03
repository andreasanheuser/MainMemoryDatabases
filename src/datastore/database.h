#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>
#include <sstream>
#include <exception>

#include <iostream>
#include <fstream>
#include "table.h"

namespace datastore {

	class Database {
	
	private:
	std::string _dbPath;
//	std::vector <Table*> _tables;
		
	public:
	Database(const DatabaseDef& aDatabaseDef);
	~Database();
	
	void addTable(const std::string&, const std::string&);
	
	void readDBInfo(const std::string& adbPath);

	}; 

}

#endif
