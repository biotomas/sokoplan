#ifndef BLOCK_H_
#define BLOCK_H_

enum Block{
  OUT = 0,
  FLOOR,
  WALL,
  GOAL,
  BOX,
  BOX_ON_GOAL,
  PLAYER,
  PLAYER_ON_GOAL
};

static const char* blockName[] = {
  "Out",
  "Floor"
  "Wall",
  "Goal",
  "Box",
  "Box On Goal",
  "Player",
  "Player on Goal"
};

static const char* blockSymbol[] = {
  // "X",
  " ",
  " ",
  "#",
  ".",
  "$",
  "*",
  "@",
  "+"
};

#endif //BLOCK_H_
