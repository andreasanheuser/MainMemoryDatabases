#include "measure.h"

#include <vector>
#include <string>
#include <sstream>
#include <exception>

#include <sys/time.h>
#include <sys/types.h>

#include <iostream>
#include <fstream>

using namespace std;
using namespace tools;

namespace tools {

	Measure::Measure(){}
	
	Measure::~Measure(){}

// Time stamp before the computations
	double Measure::startMeasure() {
		gettimeofday( &tp, 0 );
   		sec   = static_cast<long>( tp.tv_sec  );
		usec  = static_cast<long>( tp.tv_usec )/1E6;
   		return startTime = sec + usec;
   	}
   	
// Time stamp after the computations
   	double Measure::endMeasure() {
		gettimeofday( &tp, 0 );
   		sec  = static_cast<double>( tp.tv_sec  );
   		usec = static_cast<double>( tp.tv_usec )/1E6;
   		return endTime  = sec + usec;
   	}
   	
   	
// Print results
	void Measure::printMeasures(double startTime, double endTime){
		double totalTime = endTime - startTime;

  		long begin_file, end_file;
  		ifstream file_size ("/Users/andreasanheuser/Documents/UniMannheim/MainMemoryDB/tpch-dbgen/generatedFiles/lineitem.tbl");
  		begin_file = file_size.tellg();
  		file_size.seekg (0, ios::end);
  		end_file = file_size.tellg();
  		file_size.close();
 
	 	cout << "wall clock time: " << totalTime << " sec" << endl; 
  		cout << "size: " << ((end_file-begin_file)/1048576.00) << " MB" << endl;
  		cout << "speed: " << ((end_file-begin_file)/1048576.00)/totalTime << " MB/s" << endl;
  	}

}