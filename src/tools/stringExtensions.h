#ifndef STRINGEXTENSIONS_H
#define STRINGEXTENSIONS_H

#include <vector>
#include <string>

namespace tools {

  std::vector<std::string> tokenize(const std::string& aString, const char aDelim); 

  std::string trim(const std::string& aString, const std::string& aWhitespace = " \t");

}

#endif
