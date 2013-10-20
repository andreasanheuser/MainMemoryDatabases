#include "datastore/table.h"
#include "tools/measure.h"

using namespace std;
using namespace datastore;
using namespace tools;

int main(const int argc, const char * argv[]) {

  if (argc != 3) {
    cout << "Wrong usage! Run as ./database TableName FilePath" << endl;
    return 1;
  }

  //string lFile("/Users/andreasanheuser/Documents/UniMannheim/MainMemoryDB/tpch-dbgen/generatedFiles/lineitem.tbl");

  TPCH lTpch;
  Table lt(lTpch.getTableDef(string(argv[1])));

  string lFile(argv[2]);

  Measure lm;
  double lStart = lm.startMeasure();

  lt.loadDataFromFile(lFile);

  double lEnd = lm.endMeasure();

  lm.printMeasures(lStart, lEnd, lFile);

  //t.printDataToScreen();

  return 0;
}
