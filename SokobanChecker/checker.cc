#include "checker.h"
#include "direction.cc"

bool Checker::isValidSolution(std::string solution) {
  for (int i = 0; i < solution.size(); i++) {
    if (!positionIs(solution[i], {'u', 'd', 'l', 'r', 'U', 'D', 'L', 'R'})) {
      return false;
    }
  }
  return true;
}

bool Checker::isSolutionForLevel(Board board, std::string solution) {
  for (int i = 0; i < solution.length(); i++) {
    switch (solution[i]) {
      case 'u':
        if(!board.move(U, false)){
          return false;
        }
        break;
      case 'd':
        if(!board.move(D, false)){
          return false;
        }
        break;
      case 'l':
        if(!board.move(L, false)){
          return false;
        }
        break;
      case 'r':
        if(!board.move(R, false)){
          return false;
        }
        break;
      case 'U':
        if(!board.move(U, true)){
          return false;
        }
        break;
      case 'D':
        if(!board.move(D, true)){
          return false;
        }
        break;
      case 'L':
        if(!board.move(L, true)){
          return false;
        }
        break;
      case 'R':
        if(!board.move(R, true)){
          return false;
        }
        break;
      default:
        return false;
        break;
    }
  }
  return board.isSolved();
}

bool Checker::positionIs(char c, std::vector<char> possible) {
  for (std::vector<char>::iterator possibleChar = possible.begin(); possibleChar != possible.end(); ++possibleChar) {
    if (c == *possibleChar) {
      return true;
    }
  }
  return false;
}
