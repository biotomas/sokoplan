#include <iostream>
#include "level_reader.h"
#include "checker.h"

int main(int argc, char *argv[]) {
  if (argc != 3) {
    std::cout << "./SokobanChecker <level> <udlr>"
              << "\n";
    return 0;
  }

  Checker checker;
  LevelReader reader;
  std::string solution;
  if (!checker.isValidSolution(solution)) {
    std::cout << "Not a valid solution"
              << "\n";
    return 0;
  }

  Board board = reader.readLevel(argv[1]);
  solution = argv[2];

  if (checker.isSolutionForLevel(board, solution)) {
    std::cout << "Valid"
              << "\n";
  } else {
    std::cout << "Invalid"
              << "\n";
  }

  // return 0;
}
