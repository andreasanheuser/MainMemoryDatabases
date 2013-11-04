#include <cstdio>
#include <cstdlib>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <iostream>
#include <algorithm>
#include <vector>
#include "simplecharcontainer.cpp"
#include <chrono>


#define FILEPATH "/Users/andreasanheuser/Documents/UniMannheim/MainMemoryDB/tpch-dbgen/generatedFiles/lineitem.tbl"
#define NUMINTS  (100)
#define FILESIZE (NUMINTS * sizeof(char))

int main(int argc, char *argv[])
{
  std::chrono::time_point<std::chrono::system_clock> startt, endt;

  SimpleCharContainer scc{4096};
  std::vector<const char*> tokens;

  int i;
  int fd;
  char *map;  /* mmapped array of int's */
  struct stat buffer;
  int status;

  startt = std::chrono::system_clock::now();

  fd = open(FILEPATH, O_RDONLY);
  if (fd == -1) {
    perror("Error opening file for reading");
    exit(EXIT_FAILURE);
  }

  status = fstat(fd, &buffer);

  map = (char*)mmap(0, buffer.st_size, PROT_READ, MAP_SHARED, fd, 0);
  if (map == MAP_FAILED) {
    close(fd);
    perror("Error mmapping the file");
    exit(EXIT_FAILURE);
  }

  char* start = map;
  char* end;

  while (start < map + buffer.st_size)
  {
    end = std::find(start, map + buffer.st_size, '|');
    tokens.push_back(scc.insert(start, end));
    start = end + 1;
  }

  /* Read the file int-by-int from the mmap
   * *      
  for (i = 0; i < buffer.st_size -1; ++i) {
    printf("%d: %c\n", i, map[i]);
  }*/

  if (munmap(map, buffer.st_size) == -1) {
    perror("Error un-mmapping the file");
  }
  close(fd);

  endt = std::chrono::system_clock::now();
  int elapsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(endt-startt).count();
  std::cout << "elapsed ms: " << elapsed_time << std::endl;

  return 0;
}
