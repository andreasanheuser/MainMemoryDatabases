#include "Top.h"
#include "../datastore/table.h"
#include "../datastore/column.h"
#include "../datastore/tableSchema.h"

#include <string>
#include <vector>
#include <iostream>

namespace physAlgebra{
 
  datastore::table Top::scan(datastore::table & aTable){
   for(auto *c : aTable.get_columns()){//implement getter
     // for(ColumnBase b : aTable.get_columns()){
     //std::out << (*b)
     //}
     for(auto a : c->get_attrValues()){//implement getter
      //perform operation
     
     }
    }
  }

  datastore::table Top::scanSpecColumns(datastore::table & aTable, std::vector<std::string> aColumns){
    
   for(auto *c : aTable.get_columns()){//implement getter
     int i = 0;
     if(cColumns[i]->compare(c->get_columnName()) == 0){//implement getter
      for(auto a : c->get_attrValues()){//implement getter
        //perform operation
      }
     }
   }
  }

}
