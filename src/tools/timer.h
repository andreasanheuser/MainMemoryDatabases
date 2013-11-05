#include <string>
#include <chrono>

namespace tools {

  class Timer {
    public:
      void start();
      void stop();
      void reset();

      int elapsedMilliseconds() const;
      void printResults(const std::string& aFilepath) const;

    private:
      std::chrono::time_point<std::chrono::system_clock> _start, _end;
  };

}
