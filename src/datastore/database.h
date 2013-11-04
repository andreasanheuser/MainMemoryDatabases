#ifndef DATABASE_H
#define DATABASE_H

#include <vector>
#include <string>

class Table;

namespace datastore {

  class Database {
    public:
//      Database(const DatabaseDef& aDatabaseDef);
      Database(const std::string& aDatabaseName);
      ~Database();

      void addTable(const TableDef& aTableDef);

    private:
      std::string _dbName;
      std::vector<Table*> _tables;
  };

	class Database {
	
	private:
	std::string _dbName;
	std::vector <Table*> _tables;
		
	public:
	Database(const TableDef& aTableDef);
	~Database();
	
	void addTable(const std::string&, const std::string&);
	
	bool loadDBFromFile(const std::string&, const std::string&);

	}; 

}

#endif
