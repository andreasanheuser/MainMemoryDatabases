#ifndef DBHANDLER_H
#define DBHANDLER_H

#include <vector>
#include <string>


namespace datastore {
  
  // forward declaration
  class Database;

  class DBHandler {
	
    private:
      std::vector<Database*> _databases;

    public:
      DBHandler(const std::string& aDatabaseDefinitions);
      ~DBHandler();
	
      void createDatabase(const std::string& afilePath);
      
      std::vector<Database*> get_databases(){ return _databases; }

  }; 

}

#endif
