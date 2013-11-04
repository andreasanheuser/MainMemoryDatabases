#include "database.h"
#include "table.h"
#include "../tools/measure.h"
#include "tableSchema.h"

#include <vector>
#include <string>
#include <sstream>
#include <exception>
#include <chrono>

#include <iostream>
#include <fstream>

using namespace std;
using namespace tools;

double getFilesize(const std::string& aFilepath) 
{
  long begin_file, end_file;  
  std::ifstream file_size (aFilepath);
  begin_file = file_size.tellg();
  file_size.seekg (0, ios::end);
  end_file = file_size.tellg();
  file_size.close();
  return (end_file-begin_file)/1048576.00;
}

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
			if (!_tables.empty())
			{
				return true;
			}
			else
			{
				return false;
			}
		}	

		void Database::loadDataIntoTable(const std::string& aTableName, const std::string& aTableContentPath)
		{
 			std::cout << "Table: " << aTableName << std::endl;
 			
 			std::chrono::time_point<std::chrono::system_clock> startt, endt;
  			startt = std::chrono::system_clock::now();
 			
 			_tables.back()->loadDataFromFile(aTableContentPath);
 			
 			endt = std::chrono::system_clock::now();
  			int elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(endt-startt).count();
  			
  			std::cout << "Elapsed ms: " << elapsed_time << std::endl;
  			std::cout << "Speed: " << getFilesize(aTableContentPath)/elapsed_time * 1000 << " MB/s" << std::endl;
 			
 			_tables.back()->printDataToScreen();
		}
}
