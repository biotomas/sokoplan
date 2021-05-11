#ifndef MOVE_H_
#define MOVE_H_

#include "direction.cc"

class Move {
 public:
  Move(int startPosition, Direction direction);
  Direction getDirection();
  int getStartPosition();

 private:
  Direction direction_;
  int startPosition_;
};

#endif //MOVE_H_
