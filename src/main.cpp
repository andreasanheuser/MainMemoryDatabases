//#include "datastore/table.h"
//#include <chrono>
#include <fstream>
#include "datastore/dbhandler.h"

using namespace std;
using namespace datastore;

int main(const int argc, const char * argv[]) {

  std::string lDatabaseDefinitions{"../schemata/databases.txt"};

  // user defined own databaseDefinitions file
  if (argc == 2) {
    lDatabaseDefinitions = argv[1];
  }

  DBHandler dbHandler{lDatabaseDefinitions};
  return 0;
  
  
  Database * database = dbhandler.get_databases();
  
  
  
  lt.scan
  
}
