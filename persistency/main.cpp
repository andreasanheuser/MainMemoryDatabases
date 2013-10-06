#include "table.cpp"

using namespace std;
using namespace persistency;

int main(int argc, const char * argv[]) {
  string file("/Users/andreasanheuser/Documents/UniMannheim/MainMemoryDB/tpch-dbgen/generatedFiles/region.tbl");

  vector<pair<string, ColumnBase::ColumnType>> regionNameTypeLookup =
    {make_pair("R_REGIONKEY", ColumnBase::ColumnType::INTEGER),
    make_pair("R_NAME", ColumnBase::ColumnType::STRING),
    make_pair("R_COMMENT", ColumnBase::ColumnType::STRING)};

  Table t("Region", 3, regionNameTypeLookup);

  t.loadDataFromFile(file);
  t.printDataToScreen();

  return 0;
}
