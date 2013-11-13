#include "Top.h"
#include "../datastore/table.h"
#include "../datastore/column.h"
#include "../datastore/tableSchema.h"

#include <string>
#include <vector>
#include <iostream>

namespace physAlgebra{
 
  Top::Top(){}
    
  Top::~Top(){}
 
  void Top::scan(datastore::Table & aTable)
  {
   	// for(auto *c : aTable.get_columns())
	//    {   

   	//implement getter
     
     for(auto *c : aTable.get_columns())
     {
     std::cout << (*c);
     }
//      for(auto a : c->get_attrValues())
//      {
//      	std::cout << a << std::endl;	
     	//implement getter
      	//perform operation
     
     //}
    //}
  }



 //  datastore::table Top::scanSpecColumns(datastore::table & aTable, std::vector<std::string> aColumns){
//     
//    for(auto *c : aTable.get_columns()){//implement getter
//      int i = 0;
//      if(cColumns[i]->compare(c->get_columnName()) == 0){//implement getter
//       for(auto a : c->get_attrValues()){//implement getter
//         //perform operation
//       }
//      }
//    }
//   }

}
