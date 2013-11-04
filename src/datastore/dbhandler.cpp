#include "dbhandler.h"
#include "database.h"

#include <vector>
#include <string>
#include <sstream>
#include <exception>

#include <iostream>
#include <fstream>
#include "../tools/stringExtensions.h"

using namespace std;

namespace datastore {

		DBHandler::DBHandler(const std::string& aDatabaseDefinitions)
                {
                  std::ifstream ifs{aDatabaseDefinitions, std::ifstream::in};
                  std::string currentline;
                  while(std::getline(ifs, currentline)){
                    std::vector<std::string> tokens = tools::tokenize(currentline,';');
                    _databases.push_back(new Database(tokens[0]));
                  }
                }
		DBHandler::~DBHandler(){}

                /*
  		void DBHandler::createDatabase(const std::string& afilePath){
  			std::vector <std::string> dbName;
    		std::vector <std::string> dbPath;
  			int lines_read = 0;
  			string line;
  			ifstream myfile (afilePath);
  			if (myfile.is_open()){
    			while ( getline (myfile,line) ){
      				if (lines_read % 2 == 0){
        				dbName.push_back(line);
      				}
      				else{
        				dbPath.push_back(line);
      				}
      				++ lines_read;
    			}
    			myfile.close();
  			}
  			else cout << "Unable to open file"; 

			int z = 1;
			for (auto i : dbName) {
   				cout << z << ". " << i << endl;
   				++z;
  			}

  			cout << "Please select database:" << endl;
  			int dbNumber;
  			cin >> dbNumber;
  
  			Database(dbName[dbNumber-1],dbPath[dbNumber-1]);

  		}
                */

                void 

}
