#include "table.cpp"
#include "../tools/measure.cpp"

using namespace std;
using namespace datastore;

int main(int argc, const char * argv[]) {
  string lFile("/Users/andreasanheuser/Documents/UniMannheim/MainMemoryDB/tpch-dbgen/generatedFiles/lineitem.tbl");

  TPCH lTpch;
  Table lt(lTpch.getTableDef("Lineitem"));

  Measure lm;
  double lStart = lm.startMeasure();

  lt.loadDataFromFile(lFile);

  double lEnd = lm.endMeasure();

  lm.printMeasures(lStart, lEnd);

  //t.printDataToScreen();

  return 0;
}
