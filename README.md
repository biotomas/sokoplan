# SokoPlan

This is a tool to solve and generate solvable Sokoban levels using generic planning software.
Read our [paper](paper/sokoplan.pdf) or [slides](paper/slides/artsit-slides.pdf)

A partially specified sokoban level (the positions of some walls, boxes, and the player can be given as a list of possible locations).

### How to build
1. install the required dependencies: cmake g++ make python3 (for the planner) java (for the translator) by running (in Ubuntu) `sudo apt install make cmake g++ python java-default-jdk`
1. run `./setup.sh`

### How to run
1. run `./run.sh testInput.txt`
2. the result will be in `testInput.txt.solution`

Read the testInput.txt to see how input is defined.

