#ifndef TABLESCHEMA_H
#define TABLESCHEMA_H

#include <string>
#include <vector>
#include <map>

namespace datastore {
  
  /*
   * Definition of a single column of a table
   */
  class ColumnDef {
    public:
      // Possible types for each column
      enum class ColumnType {IDENTIFIER, INTEGER, DECIMAL, FLAG, TEXT, DATE};

      explicit ColumnDef(const std::string& aColumnName, const ColumnType& aColumnType);

      const std::string& getColumnName() const { return _columnName; }
      const ColumnType& getColumnType() const { return _columnType; }

    private:
      std::string _columnName;
      ColumnType _columnType;

  };

  /*
   * Used to initialize new tables
   */
  class TableDef {
    public:
      explicit TableDef(const std::string& aTabName, const std::vector<ColumnDef>& aColumnDefs);
      explicit TableDef(const std::string& aTabName, const std::string& aFilepath);
      const std::string& getTableName() const { return _tabName; }
      const std::vector<ColumnDef>& getColumnDefs() const { return _columnDefs; }

    private:
      std::string _tabName;
      std::vector<ColumnDef> _columnDefs;
  };

  /*
   * Used to initialize new databases
   */
/*   class DatabaseDef {
   	public:
   		explicit DatabaseDef(const std::string& aDbName, const std::vector<TableDef>& aTableDefs);
   		
   		const std::string& getDbName() const { return _dbDefName; }
   		const std::vector<TableDef>& getTableDefs() const { return _tableDefs; }
   		
   	private:
   		std::string _dbDefName;
   		std::vector<TableDef> _tableDefs;
   	};
*/
  /*
   * This still needs some rework...
   */
  class TPCH {
    public:
      TPCH();
      const TableDef& getTableDef(const std::string& aTableName) const { return _tableDefs.find(aTableName)->second; }
//       const DatabaseDef& getDatabaseDef(const std::string& aDatabaseName) const { return _databaseDefs.find(aDatabaseName)->second; }

    private:
      std::map<std::string, TableDef> _tableDefs;
//       std::map<std::string, DatabaseDef> _databaseDefs;
  };

}

#endif
