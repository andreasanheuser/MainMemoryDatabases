#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <vector>
#include <string>
#include <sstream>
#include <exception>

#include <iostream>
#include <fstream>

#include "database.h"

namespace datastore {

	class DBHandler {
	
	private:
        std::vector<Database*> _databases;

	public:
	DBHandler(const std::string& aDatabaseDefinitions);
	~DBHandler();
	
	void createDatabase(const std::string& afilePath);

	}; 

}

#endif
