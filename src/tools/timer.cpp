#include "timer.h"

#include <fstream>
#include <iostream>

namespace tools {

  double getFilesize(const std::string& aFilepath) 
  {
    long beginFile, endFile;  
    std::ifstream fileSize{aFilepath};
    beginFile = fileSize.tellg();
    fileSize.seekg (0, std::ios::end);
    endFile = fileSize.tellg();
    fileSize.close();
    return (endFile - beginFile)/1048576.00;
  }

  void Timer::start()
  {
    _start = std::chrono::system_clock::now();
  }

  void Timer::stop()
  {
    _end = std::chrono::system_clock::now();
  }

  void Timer::reset()
  {
    _start = std::chrono::system_clock::now();
    _end = _start;
  }

  int Timer::elapsedMilliseconds() const
  {
    return std::chrono::duration_cast<std::chrono::milliseconds>(_end - _start).count();
  }

  void Timer::printResults(const std::string& aFilepath) const
  {
    int elapsedTime{elapsedMilliseconds()};
    std::cout << "Elapsed ms: " << elapsedTime << std::endl;
    std::cout << "Speed: " << getFilesize(aFilepath)/elapsedTime * 1000 << " MB/s" << std::endl;
  }


}
