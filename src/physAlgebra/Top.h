#ifndef TOP_H
#define TOP_H

#include "../datastore/table.h"

namespace physAlgebra{

  class Top{
    Top();
    ~Top();

    int count();
    datastore::table scan();
    datastore::table scanSpecColumns();
  
  }

}

#endif

