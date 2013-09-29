#ifndef PERSISTENCY_H
#define PERSISTENCY_H

#include <vector>
#include <string>

class Relation {
  public:
    virtual bool loadDataFromFile(std::string fd) = 0;
    virtual void printToScreen() = 0;
};

class Region : public Relation {
  public:
    Region(int size);
    ~Region();

    bool loadDataFromFile(std::string fd);
    void printToScreen();

  private:
    std::vector<int> _r_regionkey;
    std::vector<std::string> _r_name;
    std::vector<std::string> _r_comment;
};


#endif
