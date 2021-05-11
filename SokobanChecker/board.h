#ifndef BOARD_H_
#define BOARD_H_

#include "block.cc"

#include <string>
#include <vector>
#include <stack>

#include "move.h"

class Board{
public:
  Board(std::vector<std::string> boardData, int hight, int width);
  Block get(int position);
  Block get(int i, int j);
  bool set(int position, Block block);
  bool set(int i, int j, Block block);
  bool positionIs(int position, std::vector<Block> blocks);
  int size();
  int neighbour(Direction direction, int position);
  int neighbour(Direction direction, int i, int j);
  int hash();
  std::string toString();
  std::string toString(int position);
  bool execute(Move move);
  bool isSolved();
  bool undoLastMove();
  std::string getMoveHistory();
  std::string getPlayerMoveHistory();
  std::vector<bool> getReachablePositions();
  bool move(Direction direction, bool isPush);

private:
  int width_;
  int height_;
  int size_;
  std::vector<Block> board_;
  int playerPosition_;
  int playerPositionStart_;
  std::vector<bool> reachable_;
  std::stack<Move> history_;

  void flood(int startPosition);
  void rFlood(int startPosition);
  std::string areNeighbours(int from, int to);
  std::string getPlayerPath(int startPosition, int goalPosition);
  int toPosition(int i, int j);
};

#endif //BOARD_H_
