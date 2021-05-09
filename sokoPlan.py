#!/usr/bin/env python3

import sys

class Block(IntEnum):
    FLOOR = 0
    WALL = 1
    GOAL = 2
    BOX = 3
    BOX_ON_GOAL = 4
    PLAYER = 5
    PLAYER_ON_GOAL = 6
    OPT_WALL = 7
    OPT_GOAL = 8
    OPT_BOX = 9
    OPT_BOX_ON_GOAL = 10
    OPT_PLAYER = 11
    OPT_PLAYER_ON_GOAL = 12


def isAcessible(block):
    if block in {
            Block.FLOOR,
            Block.GOAL,
            Block.BOX,
            Block.BOX_ON_GOAL,
            Block.PLAYER,
            Block.PLAYER_ON_GOAL,
    }:
        return True
    return False


def readLevelFromFile(pathToLevel):
    f = open(pathToLevel, "r")
    global yM
    global xM
    for line in f:
        if len(line) - 1 > xM:
            xM = len(line) - 1
    f.seek(0)
    level = []
    for line in f:
        # print(line,end='')
        row = []
        for c in line:
            if c == '#':
                row.append(Block.WALL)
            if c == '+':
                row.append(Block.PLAYER_ON_GOAL)
            if c == '@':
                row.append(Block.PLAYER)
            if c == '$':
                row.append(Block.BOX)
            if c == '*':
                row.append(Block.BOX_ON_GOAL)
            if c == '.':
                row.append(Block.GOAL)
            if c == '_' or c == ' ' or c == '-':
                row.append(Block.FLOOR)
        for i in range(xM - len(row)):
            row.append(Block.WALL)
        assert (len(row) == xM)
        level.append(row)
    yM = len(level)
    return level

def main():
    if sys.argc < 2:
        print("Usage: ./" + sys.argv[0] + " levelConstraints.txt")
