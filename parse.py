#!/usr/bin/env python3

import sys
from subprocess import getstatusoutput as cmd

levelPath = sys.argv[1]
levelFile = open(levelPath)
plan = open(sys.argv[2])

level = []
for l in levelFile:
    level.append(l)
    if l[0] == ";":
        break

solution = ''
for action in plan:
    if "move_u" in action:
        solution += "u"
    elif "move_d" in action:
        solution += "d"
    elif "move_l" in action:
        solution += "l"
    elif "move_r" in action:
        solution += "r"
    elif "push_u" in action:
        solution += "U"
    elif "push_d" in action:
        solution += "D"
    elif "push_l" in action:
        solution += "L"
    elif "push_r" in action:
        solution += "R"
    elif "place_wall" in action:
        [y, x] = [int(i) for i in action.split()[1][1:].split("_")]
        row = ""
        for i, c in enumerate(level[y]):
            if i == x:
                if c == " ":
                    row += "#"
            else:
                row += c
        level[y] = row
    elif "place_goal" in action:
        [y, x] = [int(i) for i in action.split()[1][1:].split("_")]
        row = ""
        for i, c in enumerate(level[y]):
            if i == x:
                if c == " ":
                    row += "."
                elif c == "$":
                    row += "*"
                elif c == "@":
                    row += "+"
            else:
                row += c
        level[y] = row
    elif "place_player" in action:
        [y, x] = [int(i) for i in action.split()[1][1:-1].split("_")]
        row = ""
        for i, c in enumerate(level[y]):
            if i == x:
                if c == " ":
                    row += "@"
                elif c == ".":
                    row += "+"
            else:
                row += c
        level[y] = row
    elif "place_box" in action:
        [y, x] = [int(i) for i in action.split()[1][1:].split("_")]
        row = ""
        for i, c in enumerate(level[y]):
            if i == x:
                if c == " ":
                    row += "$"
                elif c == ".":
                    row += "*"
            else:
                row += c
        level[y] = row

output = "".join(level)
print(output)
print(solution)
levelPath = levelPath.split(".")[0] + ".soko"
with open(levelPath, "w") as f:
    f.write(output)
result = cmd("./SokobanChecker/SokobanChecker " + levelPath + " " + solution)
print(result[1])
