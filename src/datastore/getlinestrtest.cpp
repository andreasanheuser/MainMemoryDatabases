#include <string>
#include <vector>
#include <iostream>
#include <sstream>
#include <fstream>
#include <chrono>
#include "simplecharcontainer.cpp"

int main()
{
  SimpleCharContainer scc{4096};
  std::vector<const char*> tokens;

  std::chrono::time_point<std::chrono::system_clock> startt, endt;

  std::string aFd{"/Users/andreasanheuser/Documents/UniMannheim/MainMemoryDB/tpch-dbgen/generatedFiles/lineitem.tbl"};
  //std::string aFd{"/Users/andreasanheuser/Documents/UniMannheim/MainMemoryDB/tpch-dbgen/generatedFiles/region.tbl"};

  startt = std::chrono::system_clock::now();

  std::ifstream lIfs (aFd, std::ifstream::in);

  if (!lIfs.is_open()) 
    return false;

  std::string lCurrentLine;
  while (getline(lIfs, lCurrentLine)) {
    std::stringstream lss(lCurrentLine);
    std::string lItem;

    int i{0};
    while (std::getline(lss, lItem, '|')) {
      tokens.push_back(scc.insert(&(*lItem.begin()),&(*lItem.end())));
    }
  }

  lIfs.close();

  endt = std::chrono::system_clock::now();
  int elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(endt-startt).count();
  std::cout << "elapsed ms: " << elapsed_time << std::endl;
}
