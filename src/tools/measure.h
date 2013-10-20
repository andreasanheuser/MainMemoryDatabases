#ifndef MEASURE_H
#define MEASURE_H

#include <vector>
#include <string>
#include <sstream>
#include <exception>

#include <sys/time.h>
#include <sys/types.h>

#include <iostream>
#include <fstream>

namespace tools {

	class Measure {
	public:
	struct timeval tp;
	long sec;
	long usec;
	long startTime;
	long endTime;
	
	Measure();
	~Measure();
	
// Time stamp before the computations
	double startMeasure();

// Time stamp after the computations
   	double endMeasure();
   	
// Print results
	void printMeasures(double, double, const std::string&);
	};

}

#endif
