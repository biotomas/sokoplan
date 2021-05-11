#include "move.h"

Move::Move(int startPosition, Direction direction){
  startPosition_ = startPosition;
  direction_ = direction;
}

int Move::getStartPosition(){
  return startPosition_;
}

Direction Move::getDirection(){
  return direction_;
}

