#include <string>
#include <exception>

namespace datastore {
  
  class MmapHandle {
    public:
      explicit MmapHandle(const std::string& aFilepath);
      ~MmapHandle();

      char* getMmap() const { return _mmap; }
      unsigned long size() const { return _size; }

    private:
      int _fd;
      unsigned _size;
      char* _mmap;
  };

  class FileOpeningException : public std::exception {
    public:
      const char* what() const throw()
      {
        return "Opening file failed";
      }
  };

  class MmapInitException : public std::exception {
    public:
      const char* what() const throw()
      {
        return "Mmap initialization failed";
      }
  };

}
