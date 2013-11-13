#ifndef TOP_H
#define TOP_H

#include "../datastore/table.h"

namespace physAlgebra{

  class Top{
    Top();
    ~Top();

    //int count();
    void scan(datastore::Table & aTable);
    //datastore::Table scanSpecColumns();
  
  };

}

#endif

