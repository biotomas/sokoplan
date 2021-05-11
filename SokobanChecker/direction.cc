#ifndef DIRECTION_H_
#define DIRECTION_H_

enum Direction {
  U,
  D,
  L,
  R
};

static const char *directionPush[] = {
    "U",
    "D",
    "L",
    "R"
};

static const char *directionMove[] = {
  "u",
  "d",
  "l",
  "r"
};

static const Direction inversDirection[] = {
  D,
  U,
  R,
  L
};

#endif //DIRECTION_H_
