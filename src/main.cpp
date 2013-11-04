//#include "datastore/table.h"
//#include <chrono>
#include <fstream>
#include "datastore/dbhandler.h"

using namespace std;
using namespace datastore;

/*
double getFilesize(const std::string& aFilepath) {
  long begin_file, end_file;  
  std::ifstream file_size (aFilepath);
  begin_file = file_size.tellg();
  file_size.seekg (0, ios::end);
  end_file = file_size.tellg();
  file_size.close();
  return (end_file-begin_file)/1048576.00;
}


int main(const int argc, const char * argv[]) {

  std::string lDatabaseDefinitions{"../schemata/databases.txt"};

  // user defined own databaseDefinitions file
  if (argc == 2) {
    lDatabaseDefinitions = argv[1];
  }

  DatabaseHandler databaseHandler{lDatabaseDefinitions};
  return 0;
}


/*

  TPCH lTpch;
  Table lt(lTpch.getTableDef(string(argv[1])));

  string lFile(argv[2]);

  std::chrono::time_point<std::chrono::system_clock> startt, endt;
  startt = std::chrono::system_clock::now();

  lt.loadDataFromFile(lFile);

  endt = std::chrono::system_clock::now();
  int elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(endt-startt).count();

  std::cout << "elapsed ms: " << elapsed_time << std::endl;
  std::cout << "speed: " << getFilesize(lFile)/elapsed_time * 1000 << " MB/s" << std::endl;

  //lt.printDataToScreen();

  return 0;
}

*/

int main(const int argc, const char * argv[]) {

  if (argc != 2) {
    cout << "Wrong usage! Run as ./database FilePath" << endl;
    return 1;
  }

  //string lFile("/Users/florianpethig/Documents/UniMannheim/TP500/Files/database_files.txt");

  
  DBHandler ldb;
  ldb.openDatabase(argv[1]);
    
  return 0;
  }
