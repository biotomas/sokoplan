#ifndef CHECKER_H_
#define CHECKER_H_

#include <string>
#include "board.h"

class Checker{
public:
  bool isValidSolution(std::string solution);
  bool isSolutionForLevel(Board board, std::string solution);
private:
  bool positionIs(char c, std::vector<char> possible);
};

#endif //CHECKER_H_
