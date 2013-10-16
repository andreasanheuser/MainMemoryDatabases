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

      ColumnDef(const std::string& aColumnName, const ColumnType& aColumnType);

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
      TableDef(const std::string& aTabName, const std::vector<ColumnDef>& aColumnDefs);
      ~TableDef();

      const std::string& getTableName() const { return _tabName; }
      const std::vector<ColumnDef>& getColumnDefs() const { return _columnDefs; }

    private:
      std::string _tabName;
      std::vector<ColumnDef> _columnDefs;
  };

  /*
   * Data structure for date datatypes
   */
  class Date {
    public:
      Date(const std::string& aDate);

    private:
      unsigned _year;
      unsigned _month;
      unsigned _day;
  };

  std::ostream& operator<< (std::ostream& aOutputStream, const Date& aDate);

  /*
   * This still needs some rework...
   */
  class TPCH {
    public:
      TPCH();
      const TableDef& getTableDef(const std::string& aTableName) const { return _tableDefs.find(aTableName)->second; }

    private:
      std::map<std::string, TableDef> _tableDefs;
  };

}

#endif
