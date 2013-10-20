#ifndef INFRA_SIMPLE_CHAR_CONTAINER_HH
#define INFRA_SIMPLE_CHAR_CONTAINER_HH

#include <string.h>
#include <vector>

/*
 *   SimpleCharContainer
 *
 *   stores strings, can't update or delete them
 *   strings given by start and end (exclusive) pointers
 *   An additional char '\0' is always appended 
 *
 */

class SimpleCharContainer {
  public:
    typedef unsigned int uint;
    typedef std::vector<char*> chunk_vt;
  private:
    SimpleCharContainer(const SimpleCharContainer&);
    SimpleCharContainer& operator=(const SimpleCharContainer&);
  public:
    SimpleCharContainer(uint aChunkSize);
    ~SimpleCharContainer();
  public:
    const char* insert(const char* aBegin, const char* aEnd);
  public:
    inline const long unsigned int size() const { return ((long unsigned int) _chunks.size() * _chunkSize); }
  private:
    long unsigned int  _chunkSize;
    char* _currentBegin;
    char* _currentEnd;
    std::vector<char*> _chunks;
};


#endif
