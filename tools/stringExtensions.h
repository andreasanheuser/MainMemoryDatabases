#ifndef STRINGEXTENSIONS_H
#define STRINGEXTENSIONS_H

#include <vector>
#include <string>
#include <sstream>
#include <utility>

namespace tools {

std::vector<std::string> tokenize(const std::string& aString, const char aDelim) {
  std::vector<std::string> lElems;
  std::stringstream lss(aString);
  std::string lItem;
  while (std::getline(lss, lItem, aDelim)) {
    lElems.push_back(std::move(lItem));
  }
  return lElems;
}

std::string trim(const std::string& aString, const std::string& aWhitespace = " \t")
{
  const auto lStrBegin = aString.find_first_not_of(aWhitespace);
  if (lStrBegin == std::string::npos)
    return ""; // no content

  const auto lStrEnd = aString.find_last_not_of(aWhitespace);
  const auto lStrRange = lStrEnd - lStrBegin + 1;

  return aString.substr(lStrBegin, lStrRange);
}

}

#endif
