#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <algorithm>

#include <iostream>
#include "mmaphandle.h"

namespace datastore {

  MmapHandle::MmapHandle(const std::string& aFilepath)
  {
    _fd = open(aFilepath.c_str(), O_RDONLY);

    if (-1 == _fd) {
      throw FileOpeningException();
    }

    // find out buffer size
    struct stat buffer;
    fstat(_fd, &buffer);

    _size = buffer.st_size;

    _mmap = (char*)mmap(0, _size, PROT_READ, MAP_SHARED, _fd, 0);

    if (MAP_FAILED == _mmap) {
      close(_fd);
      throw MmapInitException();
    }
  }

  MmapHandle::~MmapHandle()
  {
    if (-1 == munmap(_mmap, _size)) 
    {
      // error during unmapping occured
      // handle how?
    }
    close(_fd);
  }

}
