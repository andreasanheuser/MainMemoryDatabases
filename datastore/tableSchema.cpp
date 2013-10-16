#include "tableSchema.h"
#include "../tools/stringExtensions.h"

namespace datastore {

  // ok to use using namespace in cpp file?
  using namespace std;

  ColumnDef::ColumnDef(const string& aColumnName, const ColumnType& aColumnType)
    : _columnName(aColumnName), _columnType(aColumnType)
  {
  }

  TableDef::TableDef(const string& aTabName, const std::vector<ColumnDef>& aColumnDefs)
    : _tabName(aTabName), _columnDefs(aColumnDefs)
  {
  }

  TableDef::~TableDef()
  {
  }

  Date::Date(const string& aDate)
  {
    vector<string> tokens = tools::tokenize(aDate, '-');
    _year = std::stoul(tokens[0]);
    _month = std::stoul(tokens[1]);
    _day = std::stoul(tokens[2]);
  }

  std::ostream& operator<< (std::ostream& aOutputStream, const Date& aDate)
  {
    return aOutputStream;
  }

  TPCH::TPCH()
  {

    vector<ColumnDef> lcd = {ColumnDef("R_REGIONKEY", ColumnDef::ColumnType::IDENTIFIER),
                            ColumnDef("R_NAME", ColumnDef::ColumnType::TEXT),
                            ColumnDef("R_COMMENT", ColumnDef::ColumnType::TEXT)};
    TableDef ltd{"Region", lcd};
    _tableDefs.insert(pair<string, TableDef>("Region", ltd));

    vector<ColumnDef> lcd2 = {ColumnDef("L_ORDERKEY", ColumnDef::ColumnType::IDENTIFIER),
                              ColumnDef("L_PARTKEY", ColumnDef::ColumnType::IDENTIFIER),
                              ColumnDef("L_SUPPKEY", ColumnDef::ColumnType::IDENTIFIER),
                              ColumnDef("L_LINENUMBER", ColumnDef::ColumnType::INTEGER),
                              ColumnDef("L_QUANTITY", ColumnDef::ColumnType::DECIMAL),
                              ColumnDef("L_EXTENDEDPRICE", ColumnDef::ColumnType::DECIMAL),
                              ColumnDef("L_DISCOUNT", ColumnDef::ColumnType::DECIMAL),
                              ColumnDef("L_TAX", ColumnDef::ColumnType::DECIMAL),
                              ColumnDef("L_RETURNFLAG", ColumnDef::ColumnType::FLAG),
                              ColumnDef("L_LINESTATUS", ColumnDef::ColumnType::FLAG),
                              ColumnDef("L_SHIPDATE", ColumnDef::ColumnType::DATE),
                              ColumnDef("L_COMMITDATE", ColumnDef::ColumnType::DATE),
                              ColumnDef("L_RECEIPTDATE", ColumnDef::ColumnType::DATE),
                              ColumnDef("L_SHIPINSTRUCT", ColumnDef::ColumnType::TEXT),
                              ColumnDef("L_SHIPMODE", ColumnDef::ColumnType::TEXT),
                              ColumnDef("L_COMMENT", ColumnDef::ColumnType::TEXT)};
    TableDef ltd2{"Lineitem", lcd2};
    _tableDefs.insert(pair<string, TableDef>("Lineitem", ltd2));

  }
}
