#include "board.h"

#include <iostream>
#include <sstream>
#include <vector>
#include <queue>
#include <set>
#include <limits.h>
#include "math.h"

Board::Board(std::vector<std::string> boardData, int height, int width) {
  size_ = height * width;
  height_ = height;
  width_ = width;

  board_.resize(size_);
  reachable_.resize(size_);
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      int position = i * width_ + j;
      if (j < static_cast<int>(boardData[i].length())) {
        switch (boardData[i][j]) {
          case '#':
            board_[position] = WALL;
            break;
          case '@':
            board_[position] = FLOOR;
            playerPosition_ = position;
            playerPositionStart_ = position;
            break;
          case '+':
            board_[position] = GOAL;
            playerPosition_ = position;
            playerPositionStart_ = position;
            break;
          case '$':
            board_[position] = BOX;
            break;
          case '*':
            board_[position] = BOX_ON_GOAL;
            break;
          case '.':
            board_[position] = GOAL;
            break;
          case ' ':
          case '-':
          case '_':
            board_[position] = FLOOR;
            break;
          default:
            throw 20;
            break;
        }
      } else {
        board_[position] = OUT;
      }
    }
  }
  flood(playerPosition_);
}

Block Board::get(int position) {
  if (position < 0 || position >= size_) {
    return OUT;
  }
  return board_[position];
}

Block Board::get(int i, int j) {
  return get(toPosition(i, j));
}

bool Board::set(int position, Block block) {
  if (position < 0 || position >= size_) {
    return false;
  }
  board_[position] = block;
  return true;
}

bool Board::set(int i, int j, Block block) {
  return set(toPosition(i, j), block);
}

bool Board::positionIs(int position, std::vector<Block> blocks) {
  Block blockAtPosition = get(position);
  for (std::vector<Block>::iterator possibleBlock = blocks.begin(); possibleBlock != blocks.end(); ++possibleBlock) {
    if (blockAtPosition == *possibleBlock) {
      return true;
    }
  }
  return false;
}

int Board::size() {
  return size_;
}

int Board::neighbour(Direction direction, int position) {
  int offset[] = {-width_, width_, -1, 1};
  return position + offset[direction];
}

int Board::neighbour(Direction direction, int i, int j) {
  neighbour(direction, toPosition(i, j));
}

int Board::hash() {
  int prime = 41;
  int result = 1;
  bool setPlayer = false;

  for (int i = 0; i < size(); i++) {
    if (reachable_[i]) {
      switch (get(i)) {
        case FLOOR:
          if (!setPlayer) {
            setPlayer = true;
            result = prime * result + PLAYER;
          } else {
            result = prime * result + get(i);
          }
          break;
        case GOAL:
          if (!setPlayer) {
            setPlayer = true;
            result = prime * result + PLAYER_ON_GOAL;
          } else {
            result = prime * result + get(i);
          }
          break;
        case PLAYER_ON_GOAL:
          if (setPlayer) {
            result = prime * result + GOAL;
          } else {
            setPlayer = true;
            result = prime * result + get(i);
          }
          break;
        case PLAYER:
          if (setPlayer) {
            result = prime * result + FLOOR;
          } else {
            setPlayer = true;
            result = prime * result + get(i);
          }
          break;
        default:
          result = prime * result + get(i);
          break;
      }
    } else {
      result = prime * result + get(i);
    }
  }
  return result;
}

std::string Board::toString() {
  std::ostringstream output;
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      if (playerPosition_ == toPosition(i, j)) {
        if (get(i, j) == FLOOR) {
          output << blockSymbol[PLAYER];
        } else {
          output << blockSymbol[PLAYER_ON_GOAL];
        }
      } else {
        output << blockSymbol[get(i, j)];
      }
    }
    output << "\n";
  }
  return output.str();
}

std::string Board::toString(int position) {
  std::ostringstream output;
  for (int i = 0; i < height_; i++) {
    for (int j = 0; j < width_; j++) {
      if (toPosition(i, j) == position) {
        output << "O";
      } else {
        if (playerPosition_ == toPosition(i, j)) {
          if (get(i, j) == FLOOR) {
            output << blockSymbol[PLAYER];
          } else {
            output << blockSymbol[PLAYER_ON_GOAL];
          }
        } else {
          output << blockSymbol[get(i, j)];
        }
      }
    }
    output << "\n";
  }
  return output.str();
}

bool Board::execute(Move move) {
  history_.push(move);
  int newPosition = neighbour(move.getDirection(), move.getStartPosition());
  switch (get(move.getStartPosition())) {
    case BOX:
      if (get(newPosition) == FLOOR) {
        set(move.getStartPosition(), FLOOR);
        set(newPosition, BOX);
      } else {
        set(move.getStartPosition(), FLOOR);
        set(newPosition, BOX_ON_GOAL);
      }
      break;
    case BOX_ON_GOAL:
      if (get(newPosition) == FLOOR) {
        set(move.getStartPosition(), GOAL);
        set(newPosition, BOX);
      } else {
        set(move.getStartPosition(), GOAL);
        set(newPosition, BOX_ON_GOAL);
      }
      break;
    default:
      return false;
      break;
  }
  playerPosition_ = move.getStartPosition();
  flood(playerPosition_);
  return true;
}

bool Board::isSolved() { //opt
  for (int i = 0; i < size(); i++) {
    if (board_[i] == BOX) {
      return false;
    }
  }
  return true;
}

bool Board::undoLastMove() {
  if (history_.empty()) {
    std::cout << "No Move to Undo"
              << "\n";
    return false;
  } else {
    Move move = history_.top();
    history_.pop();

    int box = neighbour(move.getDirection(), move.getStartPosition());
    if (get(box) == BOX) {
      set(box, FLOOR);
    } else {
      set(box, GOAL);
    }

    if (get(move.getStartPosition()) == FLOOR) {
      set(move.getStartPosition(), BOX);
    } else {
      set(move.getStartPosition(), BOX_ON_GOAL);
    }

    playerPosition_ = neighbour(inversDirection[move.getDirection()], move.getStartPosition());
    flood(playerPosition_);
  }
}

std::string Board::getMoveHistory() { //not to be used
  std::ostringstream output;
  std::vector<Move> invert;
  while (!history_.empty()) {
    invert.push_back(history_.top());
    history_.pop();
  }
  for (int i = invert.size() - 1; i > 0; i--) {
    output << (invert[i].getStartPosition()) << (directionPush[invert[i].getDirection()]) << " | ";
  }
  output << (invert[0].getStartPosition()) << (directionPush[invert[0].getDirection()]);
  return output.str();
}

std::string Board::getPlayerMoveHistory() {
  std::stack<std::string> solution;
  std::string push;
  std::string pathToNextPush;

  while (history_.size() > 1) {
    push = directionPush[history_.top().getDirection()];
    undoLastMove();
    pathToNextPush = getPlayerPath(history_.top().getStartPosition(), playerPosition_);
    pathToNextPush.append(push);
    solution.push(pathToNextPush);
  }

  push = directionPush[history_.top().getDirection()];
  undoLastMove();
  pathToNextPush = getPlayerPath(playerPositionStart_, playerPosition_);
  pathToNextPush.append(push);
  solution.push(pathToNextPush);

  std::ostringstream playerPath;
  while (!solution.empty()) {
    playerPath << solution.top();
    solution.pop();
  }
  return playerPath.str();
}

std::vector<bool> Board::getReachablePositions() {
  return reachable_;
}

//private:
void Board::flood(int startPosition) { //opt
  reachable_.clear();
  reachable_.resize(size());
  for (int i = 0; i < size(); i++) {
    reachable_.push_back(false);
  }
  reachable_[startPosition] = true;
  rFlood(startPosition);
}

void Board::rFlood(int startPosition) {
  for (int directionInt = U; directionInt <= R; directionInt++) {
    Direction direction = static_cast<Direction>(directionInt);
    int square = neighbour(direction, startPosition);
    if (square >= 0 && square < size() && !reachable_[square]) {
      reachable_[square] = true;
      if (board_[square] == FLOOR || board_[square] == GOAL) {
        rFlood(square);
      }
    }
  }
}

struct priorityPosition {
  int position;
  int f;
  priorityPosition(int position, int f) {
    this->position = position;
    this->f = f;
  }
};

struct HigherPositionPriority {
  bool operator()(const priorityPosition &lhs, const priorityPosition &rhs) const {
    return lhs.f > rhs.f;
  }
};

std::string Board::areNeighbours(int from, int to) {
  for (int directionInt = U; directionInt <= R; directionInt++) {
    Direction direction = static_cast<Direction>(directionInt);
    if (neighbour(direction, from) == to) {
      return directionMove[direction];
    }
  }
  return "NOT_NEIGHBOURS";
}

std::string Board::getPlayerPath(int startPosition, int goalPosition) {
  //BFS
  if (startPosition == goalPosition) {
    return "";
  }
  std::vector<int> pred(size(), -1);
  int current;
  int successor;
  std::queue<int> q;
  q.push(goalPosition);
  while (!q.empty()) {
    current = q.front();
    q.pop();
    for (int directionInt = U; directionInt <= R; directionInt++) {
      Direction direction = static_cast<Direction>(directionInt);
      successor = neighbour(direction, current);
      if (positionIs(successor, {FLOOR, GOAL}) && pred[successor] == -1) {
        pred[successor] = current;
        q.push(successor);
        if (successor == startPosition) {
          current = startPosition;
          std::string path = "";
          while (current != goalPosition) {
            path.append(areNeighbours(current, pred[current]));
            current = pred[current];
          }
          return path;
        }
      }
    }
  }

  return "NOPATH";

  //A*
  // std::string path = "";
  // // std::priority_queue<priorityPosition, std::vector<priorityPosition>, HigherPositionPriority> open;
  // std::vector<priorityPosition> open;
  // std::vector<int> pred(size(), -1);
  // std::vector<int> g(size(), INT_MAX);
  // std::set<int> closed;

  // int current;
  // int successor;

  // open.push_back(priorityPosition(startPosition, 0));

  // do {
  //   std::vector<priorityPosition>::iterator min;



  //   // for (std::vector<priorityPosition>::iterator position = open.begin(); position!= open.end(); ++position) {
  //   // if(position->f < min->f){
  //   // min = position;
  //   // }
  //   // }
  //   // open.erase(min);
  //   current = open.back().position;
  //   open.pop_back();

  //   if (current == goalPosition) {

  //     return "found";
  //     // return
  //   }
  //   closed.insert(current);

  //   //expand current
  //   for (int directionInt = U; directionInt <= R; directionInt++) {
  //     Direction direction = static_cast<Direction>(directionInt);
  //     successor = neighbour(direction, current);
  //     if (closed.find(successor) != closed.end()) {
  //       continue;
  //     }
  //     int tentative_g = g[current] + 1;

  //     for (int i = 0; i < open.size(); i++) {
  //       if (open[i].position == successor && tentative_g >= g[open[i].position]) {
  //         continue;
  //       }
  //     }

  //     pred[successor] = current;
  //     g[successor] = tentative_g;

  //     int iSucc = successor % width_;
  //     int jSucc = successor / width_;
  //     int iGoal = goalPosition % width_;
  //     int jGoal = goalPosition / width_;

  //     int h = static_cast<int>(ceil(sqrt(pow((iSucc - iGoal), 2) + pow((jSucc - jGoal), 2))));
  //     int f = tentative_g + h;

  //     std::vector<priorityPosition> updateOpen;
  //     updateOpen.empty();

  //     if (open.empty()) {
  //       updateOpen.push_back(priorityPosition(successor, f));
  //     } else {
  //       bool flag = false;
  //       for (int i = 0; i < open.size(); i++) {
  //         if (open[i].position == successor) {
  //           i++;
  //         }
  //         if (open[i].f < f) {
  //           updateOpen.push_back(priorityPosition(successor, f));
  //           flag = true;
  //         } else {
  //           if (!flag) {
  //             updateOpen.push_back(open[i]);
  //           }
  //         }
  //       }
  //     }
  //       open = updateOpen;
  //   }


  // } while (!open.empty());


  // return "xxx";
}

int Board::toPosition(int i, int j) {
  return i * width_ + j;
}

bool Board::move(Direction direction, bool isPush) {
  int newPlayerPosition = neighbour(direction, playerPosition_);
  if (isPush) {
    return execute(Move(newPlayerPosition, direction));
  } else {
    if (positionIs(newPlayerPosition, {FLOOR, GOAL})) {
      playerPosition_ = newPlayerPosition;
    } else {
      return false;
    }
  }
  return true;
}
