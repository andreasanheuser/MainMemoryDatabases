#include <fstream>
#include <iostream>
#include "relation.h"
#include "../tools/stringExtensions.h"

Region::Region(int size) {
}

Region::~Region() {}

bool Region::loadDataFromFile(std::string fd) {
  std::ifstream ifs (fd, std::ifstream::in);

  if (!ifs.is_open()) 
    return false;

  std::string currentLine;
  
  while (getline(ifs, currentLine)) {
    std::vector<std::string> tokens = tools::tokenize(currentLine, '|');
    _r_regionkey.push_back(std::stoi(tokens[0]));
    _r_name.push_back(tokens[1]);
    _r_comment.push_back(tokens[2]);
  }

  ifs.close();

  return true;
}

void Region::printToScreen() {
  for (int i = 0; i < _r_regionkey.size(); ++i) {
    std::cout << _r_regionkey[i] << " | " << _r_name[i] << " | " << _r_comment[i] << std::endl;
  }
}

int main(int argc, const char * argv[]) {
  //std::string file("/Users/andreasanheuser/Documents/Uni Mannheim/tpch-dbgen/generatedFiles/region.tbl");

  std::string input;
  while (getline(std::cin, input)) {
    Region r(0);
    if (r.loadDataFromFile(input))
      r.printToScreen();
    else
      std::cout << "Bad filepath" << std::endl;
  }

}
