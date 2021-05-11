#include "level_reader.h"
#include <fstream>

LevelReader::LevelReader() {
}

Board LevelReader::readLevel(std::string pathToFile) {
  std::ifstream fileStream(pathToFile);
  std::vector<std::string> boardData;
  std::string line;
  int height = 0;
  int width = 0;
  while (std::getline(fileStream, line)) {
    if (line.length() == 0) {
      continue;
    }
    if (line[0] == ';') {
      name_ = line.substr(2, line.length() - 2);
    } else {
      height++;
      boardData.push_back(line);
      if (width < line.length()) {
        width = line.length();
      }
    }
  }
  if(height == 0){
    throw 0;
  }
  return Board(boardData, height, width);
}
