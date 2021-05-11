#!/usr/bin/env python3

import sys
import enum
from enum import IntEnum

pddlStrings = [
    """(define (problem sokoban-1)
 (:domain sokoban)
 (:requirements :strips :typing)
 (:objects """,
    """ )
 (:init""",
    """ )
 (:goal (and \t""",
    """ ))
)""",
]

xM = 0
xY = 0

level = []
requiredCountWall = 0
opt_wall = []
requiredCountBox = 0
opt_box = []
requiredCountGoal = 0
opt_goal = []
opt_player = []

pddlGrid = []

class Block(IntEnum):
    FLOOR = 0
    WALL = 1
    GOAL = 2
    BOX = 3
    BOX_ON_GOAL = 4
    PLAYER = 5
    PLAYER_ON_GOAL = 6


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

def readOptional(f):
    opt = [[False for c in row] for row in level]
    for i, line in enumerate(f):
        if line[0] == ';':
            break
        for j, c in enumerate(line):
            if c == "?":
                opt[i][j] = True
    required = 0
    if len(line.split())  > 2:
        required = int(line.split()[2])
    return required, opt

def readLevelFromFile(pathToLevel):
    f = open(pathToLevel, "r")
    global yM
    global xM
    for line in f:
        if line[0] == ';':
            continue
        if len(line) - 1 > xM:
            xM = len(line) - 1
    f.seek(0)
    global level
    for line in f:
        if line[0] == ';':
            break
        # print(line,end='')
        row = []
        for c in line:
            if c == "#":
                row.append(Block.WALL)
            if c == "+":
                row.append(Block.PLAYER_ON_GOAL)
            if c == "@":
                row.append(Block.PLAYER)
            if c == "$":
                row.append(Block.BOX)
            if c == "*":
                row.append(Block.BOX_ON_GOAL)
            if c == ".":
                row.append(Block.GOAL)
            if c == "_" or c == " " or c == "-":
                row.append(Block.FLOOR)
        for i in range(xM - len(row)):
            row.append(Block.WALL)
        assert len(row) == xM
        level.append(row)
    yM = len(level)

    global requiredCountWall
    global opt_wall
    requiredCountWall, opt_wall = readOptional(f)
    global requiredCountBox
    global opt_box
    requiredCountBox, opt_box = readOptional(f)
    global requiredCountGoal
    global opt_goal
    requiredCountGoal, opt_goal = readOptional(f)
    global opt_player
    _, opt_player = readOptional(f)


def getPddlGrid(level):
    global pddlGrid
    pddlGrid = [["" for c in row] for row in level]
    for y in range(yM):
        for x in range(xM):
            if not isAcessible(level[y][x]):
                continue
            # if deadSquares[y][x]:
            #     squares[y][x] = "p" + str(y) + "_" + str(x)
            # else:
            #     squares[y][x] = "b" + str(y) + "_" + str(x)
            pddlGrid[y][x] = "s" + str(y) + "_" + str(x)


def printObjects(pddlGrid):
    pddlPlayer = "\t"
    pddlBox = "\t"
    for row in pddlGrid:
        for c in row:
            if c != "":
                if c[0] == "s":
                    pddlPlayer += c + " "
                # if c[0] == "p":
                #     pddlPlayer += c + " "
                # if c[0] == "b":
                #     pddlBox += c + " "
    pddlPlayer += "- square"
    # pddlPlayer += "- player"
    # pddlBox += "- box"
    print(pddlPlayer)
    # print(pddlBox)
    print("\t" + " ".join(["count_wall"  + str(i) for i in range(requiredCountWall + 1)]) + " - count_wall")
    print("\t" + " ".join(["count_box"  + str(i) for i in range(requiredCountBox + 1)]) + " - count_box")
    print("\t" + " ".join(["count_goal"  + str(i) for i in range(requiredCountGoal + 1)]) + " - count_goal")


def printAbove(pddlGrid):
    for x in range(xM):
        for y in range(yM - 1):
            if pddlGrid[y][x] != "" and pddlGrid[y + 1][x] != "":
                print("\t(above " + pddlGrid[y][x] + " " + pddlGrid[y + 1][x] + ")")


def printLeft(pddlGrid):
    for y in range(yM):
        for x in range(xM - 1):
            if pddlGrid[y][x] != "" and pddlGrid[y][x + 1] != "":
                print("\t(left " + pddlGrid[y][x] + " " + pddlGrid[y][x + 1] + ")")

def printOpt(pre, opt):
    for y in range(yM):
        for x in range(xM):
            if opt[y][x]:
                print("\t(" + pre + " " + pddlGrid[y][x] + ")")

def printCount(pre, required):
    print("\t(current_" + pre + " " + pre + "0)")
    for i in range(required):
        print("\t(next_" + pre + " " + pre + str(i) + " " + pre + str(i + 1) + ")")


def printInit(pddlGrid, level):
    printAbove(pddlGrid)
    printLeft(pddlGrid)
    printOpt("opt_wall", opt_wall)
    printOpt("opt_box", opt_box)
    printOpt("opt_goal", opt_goal)
    printOpt("opt_player", opt_player)
    printCount("count_wall", requiredCountWall)
    printCount("count_box", requiredCountBox)
    printCount("count_goal", requiredCountGoal)
    print("\t(construction)")
    for y in range(yM):
        for x in range(xM):
            if pddlGrid[y][x] == "":
                continue
            if level[y][x] == Block.PLAYER or level[y][x] == Block.PLAYER_ON_GOAL:
                print("\t(current_count_player)")
                print("\t(player " + pddlGrid[y][x] + ")")
            if level[y][x] == Block.BOX or level[y][x] == Block.BOX_ON_GOAL:
                print("\t(box " + pddlGrid[y][x] + ")")
            if (
                level[y][x] == Block.GOAL
                or level[y][x] == Block.BOX_ON_GOAL
                or level[y][x] == Block.PLAYER_ON_GOAL
            ):
                print("\t(goal " + pddlGrid[y][x] + ")")


def printGoal(pddlGrid, level):
    for y in range(yM):
        for x in range(xM):
            if (
                level[y][x] == Block.GOAL
                or level[y][x] == Block.BOX_ON_GOAL
                or level[y][x] == Block.PLAYER_ON_GOAL
            ):
                print("\t(box " + pddlGrid[y][x] + ")")
    print("\t(current_count_wall count_wall" + str(requiredCountWall) +")")
    print("\t(current_count_box count_box" + str(requiredCountBox) +")")
    print("\t(current_count_goal count_goal" + str(requiredCountGoal) +")")
    print("\t(current_count_player)")
    print("\t(final)")


def main():
    if len(sys.argv) < 2:
        print("Usage: ./" + sys.argv[0] + " levelConstraints.txt")
        exit(0)
    readLevelFromFile(sys.argv[1])
    getPddlGrid(level)

    # print PDDL
    print(pddlStrings[0])
    printObjects(pddlGrid)
    print(pddlStrings[1])
    printInit(pddlGrid, level)
    print(pddlStrings[2])
    printGoal(pddlGrid, level)
    print(pddlStrings[3])


if __name__ == "__main__":
    main()
