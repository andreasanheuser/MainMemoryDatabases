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
                  std::ifstream ifs(aDatabaseDefinitions, std::ifstream::in);
                  std::string currentline;
                  while(std::getline(ifs, currentline)){
                    std::vector<std::string> tokens = tools::tokenize(currentline,';');
                    _databases.push_back(new Database(tokens[0]));
                    std::ifstream ifs2(tokens[1], std::ifstream::in);
                    while(std::getline(ifs2, currentline))
                    {
                      tokens = tools::tokenize(currentline, ';');
                      TableDef lTableDef{tokens[0], tokens[1]};
                      if(true == _databases.back()->addTable(lTableDef))
                      {
                      	_databases.back()->loadDataIntoTable(tokens[0], tokens[2]);
                      }
                      else
                      {
                      	std::cout << "unable to open: " << tokens[0] << std::endl;
                      }
                  	}	
                }
        }

		DBHandler::~DBHandler()
		{
            for(auto d : _databases){
                    delete d;
            }
        }

}
