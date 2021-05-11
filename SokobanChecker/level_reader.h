#include "board.h"
#include <string>

#ifndef LEVEL_READER_H_
#define LEVEL_READER_H_

class LevelReader{
public:
  LevelReader();
  Board readLevel(std::string pathToFile);
private:
  std::string name_;
};

#endif //LEVEL_READER_H_
