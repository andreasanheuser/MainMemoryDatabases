#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <vector>
#include <string>
#include <sstream>
#include <exception>

#include <iostream>
#include <fstream>

namespace datastore {

	class DBHandler {
	
	private:


	public:
	DBHandler();
	~DBHandler();
	
	void openDatabase(const std::string& afilePath);

	}; 

}

#endif
